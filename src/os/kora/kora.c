/*
 *      This file is part of the KoraOS project.
 *  Copyright (C) 2015-2019  <Fabien Bavent>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *   - - - - - - - - - - - - - - -
 */
#include <bits/types.h>
#include <bits/libio.h>
#include <kora/splock.h>
#include <kora/mcrs.h>
#include <kora/syscalls.h>
#include <sys/mman.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <sys/stat.h>

_Noreturn void exit(int res);
FILE *fvopen(int fd, int o);
void setup_allocator(void *, size_t);
int snprintf(char *buf, size_t len, const char *msg, ...);
int write(int fd, char *buf, size_t len);


int futex_wait(int *addr, int val, long timeout, int flags)
{
    xtime_t time = timeout;
    return syscall(SYS_FUTEX_WAIT, addr, val, &time, flags);
}

int futex_requeue(int *addr, int val, int val2, int *addr2, int flags)
{
    return syscall(SYS_FUTEX_REQUEUE, addr, val, val2, addr2, flags);
}

int futex_wake(int *addr, int val)
{
    return syscall(SYS_FUTEX_REQUEUE, addr, val, 0, NULL, 0);
}



int chdir(const char *path)
{
    int len = strlen(path) + 1;
    return syscall(SYS_SINFO, SNFO_PWD, path, len);
}

char *getcwd(char *buf, size_t len)
{
    int ret = syscall(SYS_GINFO, SNFO_PWD, buf, len);
    return ret == 0 ? buf : NULL;
}

// int execve(char *name, char **argv, char **env);
// int getpid();
// int wait(int *status);
// int kill(int pid, int sig);


/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */

void *mmap(void *addr, size_t length, int prot, int flags, int fd, __off_t off)
{
    return (void *)syscall(SYS_MMAP, addr, length, prot | flags, fd, off);
}

int munmap(void *addr, size_t length)
{
    return syscall(SYS_MUNMAP, addr, length);
}


/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */

// int gettimeofday(struct timeval *p, struct timezone *z);

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */


FILE *stdin;
FILE *stdout;
FILE *stderr;

char **environ;

// __thread
int __errno;

int *__errno_location()
{
    return &__errno;
}

void __perror_fail(int err, const char *file, int line, const char *msg)
{
    char buf[4096];
    int lg = snprintf(buf, 4096, "Proc error %d at %s:%d : %s\n", err, file, line, msg);
    write(2, buf, lg);
    exit(-1);
}

_Noreturn void __assert_fail(const char *expr, const char *file, int line, const char *func)
{
    char buf[4096];
    int lg = snprintf(buf, 4096, "Assertion %s at %s:%d in %s\n", expr, file, line, func);
    write(2, buf, lg);
    exit(-1);
}

_Noreturn void __assert(const char *expr, const char *file, int line)
{
    char buf[4096];
    int lg = snprintf(buf, 4096, "Assertion %s at %s:%d\n", expr, file, line);
    write(2, buf, lg);
    exit(-1);
}

void __libc_init()
{
    void *heap = mmap(NULL, 16 * _Mib_, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_HEAP, -1, 0);
    if (heap == NULL || heap == (void *) - 1)
        __perror_fail(ENOMEM, __FILE__, __LINE__, "Unable to allocate first heap segment");
    setup_allocator(heap, 16 * _Mib_);

    stdin = fvopen(0, O_RDONLY);
    stdout = fvopen(1, O_WRONLY);
    stderr = fvopen(2, O_WRONLY);
}

void __libc_fini()
{
    fclose(stdin);
    fclose(stdout);
    fclose(stderr);
}


int file_stat_mode[] = { -1,
                         S_IFREG, S_IFBLK, S_IFIFO, S_IFCHR,
                         S_IFCHR, S_IFSOCK, S_IFLNK, S_IFREG,
                         S_IFDIR,
                       };


typedef struct filemeta filemeta_t;
int stat_(const char *path, int dir, struct stat *stat, int flags)
{
    filemeta_t meta;
    int ret = syscall(SYS_FSTAT, dir, path, &meta, flags);
    if (ret < 0)
        return -1;

    // dev_t     st_dev;     /* ID of device containing file */
    stat->st_ino = meta.ino;
    // nlink_t   st_nlink;   /* number of hard links */
    // uid_t     st_uid;     /* user ID of owner */
    // gid_t     st_gid;     /* group ID of owner */
    // dev_t     st_rdev;    /* device ID (if special file) */

    // off_t     st_size;    /* total size, in bytes */
    // blksize_t st_blksize; /* blocksize for file system I/O */
    // blkcnt_t  st_blocks;  /* number of 512B blocks allocated */
    stat->st_size = meta.size;
    stat->st_blksize = meta.block;
    stat->st_blocks = ALIGN_UP(meta.rsize, 512) / 512;

    // time_t    st_atime;   /* time of last access */
    // time_t    st_mtime;   /* time of last modification */
    // time_t    st_ctime;   /* time of last status change */
    stat->st_ctime = USEC_TO_SEC(meta.ctime);
    stat->st_ctimensec = NSEC_OF_USEC(meta.ctime);
    stat->st_mtime = USEC_TO_SEC(meta.mtime);
    stat->st_mtimensec = NSEC_OF_USEC(meta.mtime);
    stat->st_atime = USEC_TO_SEC(meta.atime);
    stat->st_atimensec = NSEC_OF_USEC(meta.atime);

    // mode_t    st_mode;    /* protection */
    stat->st_mode = file_stat_mode[meta.ftype];
    return 0;
}


int stat(const char *path, struct stat *stat)
{
    return stat_(path, -1, stat, 1);
}

int lstat(const char *path, struct stat *stat)
{
    return stat_(path, -1, stat, 0);
}

int fstat(int fd, struct stat *stat)
{
    return stat_(NULL, fd, stat, 1);
}


void readlink()
{
}


time_t time(time_t *ptr)
{
    xtime_t now = xtime_read(XTIME_CLOCK);
    return now / _PwMicro_;
}

clock_t clock()
{
    return 0;
}

void gethostname(char *buf, int len)
{

}

char *getenv(const char *name)
{
    return NULL;
}


_Noreturn void abort(void)
{
    // raise(SIGABRT);
    exit(127);
}

xtime_t xtime_read(xtime_name_t name)
{
    xtime_t value = 0;
    syscall(SYS_XTIME, name, &value);
    return value;
}

