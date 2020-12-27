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
#include <bits/types.h>
// #include <kora/splock.h>
#include <kora/mcrs.h>
#include <sys/syscall.h>
// #include <syscalls.h>
#include <sys/mman.h>
#include <errno.h>
#include <bits/timespec.h>
#include <kora/atomic.h>

#define MMAP_HEAP 5

// int execve(char *name, char **argv, char **env);
// int getpid();
// int wait(int *status);
// int kill(int pid, int sig);


/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */

void *mmap(void *addr, size_t length, int prot, int flags, int fd, __off_t off)
{
    return (void *) - 1;
}

int munmap(void *addr, size_t length)
{
    return -1;
}

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */


int fcntl(int fd, int cmd, ...)
{
    return -1;
}

// int fstat(int file, struct stat *st);
// int stat(const char *file, struct stat *st);
// int link(char *old, char *new);
// int unlink(char *name);


/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */

// int gettimeofday(struct timeval *p, struct timezone *z);

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */

_Noreturn void exit(int res);
FILE *fvopen(int fd, int o);
void setup_allocator(void *, size_t);



FILE *stdin;
FILE *stdout;
FILE *stderr;

char **environ;

__thread int __errno;

int *__errno_location()
{
    return &__errno;
}

void __perror_fail(int err, const char *file, int line, const char *msg)
{
    exit(-1);
}

_Noreturn void __assert_fail(const char *expr, const char *file, int line)
{
    for (;;);
}

void __libc_init()
{
    void *heap = mmap(NULL, 16 * _Mib_, 06, MMAP_HEAP, -1, 0);
    if (heap == NULL || heap == (void *) - 1)
        __perror_fail(ENOMEM, __FILE__, __LINE__, "Unable to allocate first heap segment");
    setup_allocator(heap, 16 * _Mib_);

    stdin = fvopen(0, O_RDONLY);
    stdout = fvopen(1, O_WRONLY);
    stderr = fvopen(2, O_WRONLY);
}


/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */

#include <sys/syscall.h>
#include <sys/types.h>

#undef SYS_exit
#undef SYS_fork
#undef SYS_read
#undef SYS_write
#undef SYS_open
#undef SYS_close
#undef SYS_waitpid
#undef SYS_creat
#undef SYS_link
#undef SYS_unlink
#undef SYS_execve
#undef SYS_chdir
#undef SYS_time
#undef SYS_mknod
#undef SYS_chmod
#undef SYS_lchown16
#undef SYS_stat
#undef SYS_lseek
#undef SYS_getpid
#undef SYS_mount
#undef SYS_oldmount
#undef SYS_setuid16
#undef SYS_getuid16
#undef SYS_stime
#undef SYS_ptrace
#undef SYS_alarm
#undef SYS_fstat
#undef SYS_pause
#undef SYS_utime
#undef SYS_access
#undef SYS_nice
#undef SYS_sync
#undef SYS_kill
#undef SYS_rename
#undef SYS_mkdir
#undef SYS_rmdir
#undef SYS_dup
#undef SYS_pipe
#undef SYS_times

#undef SYS_futex

enum {
    SYS_exit = 1,
    SYS_fork,
    SYS_read,
    SYS_write,
    SYS_open,
    SYS_close,
    SYS_waitpid,
    SYS_creat,
    SYS_link,
    SYS_unlink,
    SYS_execve,
    SYS_chdir,
    SYS_time,
    SYS_mknod,
    SYS_chmod,
    SYS_lchown16 = 0x10,
    SYS_stat = 0x12,
    SYS_lseek,
    SYS_getpid = 0x14,
    SYS_mount,
    SYS_oldmount,
    SYS_setuid16,
    SYS_getuid16,
    SYS_stime,
    SYS_ptrace,
    SYS_alarm,
    SYS_fstat,
    SYS_pause,
    SYS_utime = 0x1e,
    SYS_access = 0x21,
    SYS_nice = 0x22,
    SYS_sync = 0x24,
    SYS_kill,
    SYS_rename,
    SYS_mkdir,
    SYS_rmdir,
    SYS_dup,
    SYS_pipe,
    SYS_times = 0x2b,

    SYS_futex = 0xf0,
};

_Noreturn void exit(int status)
{
    syscall(SYS_exit, status);
    for (;;);
}

pid_t fork()
{
    return syscall(SYS_fork, 0);
}


int read(int fd, void *buf, size_t len)
{
    return syscall(SYS_read, fd, buf, len);
}

int write(int fd, const void *buf, size_t len)
{
    return syscall(SYS_write, fd, buf, len);
}

int open(const char *path, int flags, ...)
{
    va_list ap;
    va_start(ap, flags);
    int mode = va_arg(ap, int);
    int fd = syscall(SYS_open, path, flags, mode);
    va_end(ap);
    return fd;
}

int close(int fd)
{
    return syscall(SYS_close, fd);
}

pid_t waitpid(pid_t pid, int *status, int options)
{
    return syscall(SYS_waitpid, pid, status, options);
}

int creat(const char *pathname, __mode_t mode)
{
    return syscall(SYS_creat, pathname, mode);
}

int link(const char *oldname, const char *newname)
{
    return syscall(SYS_link, oldname, newname);
}

int unlink(const char *pathname)
{
    return syscall(SYS_unlink, pathname);
}

int execve(const char *filename, char *const argv[], char *const envp[])
{
    return syscall(SYS_execve, filename, argv, envp);
}

int chdir(const char *path)
{
    return syscall(SYS_chdir, path);
}

__time_t time(__time_t *ptime)
{
    return syscall(SYS_time, ptime);
}

int mknod(const char *pathname, mode_t mode, dev_t dev)
{
    return syscall(SYS_mknod, pathname, mode, dev);
}

int chmod(const char *path, mode_t mode)
{
    return syscall(SYS_chmod, path, mode);
}

int lchown(const char *path, uid_t owner, gid_t group)
{
    return syscall(SYS_lchown16, path, owner, group);
}

int stat(const char *path, struct stat *buf)
{
    return syscall(SYS_stat, path, buf);
}

off_t lseek(int fd, off_t offset, int whence)
{
    return syscall(SYS_lseek, fd, offset, whence);
}


/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */

#define FUTEX_WAIT  1
#define FUTEX_WAKE  2
#define FUTEX_FD  3
#define FUTEX_REQUEUE  4
#define FUTEX_CMP_REQUEUE  5


// Five operations are currently defined:

// FUTEX_WAIT
//     This operation atomically verifies that the futex address uaddr still contains the value val, and sleeps awaiting FUTEX_WAKE on this futex address. If the timeout argument is non-NULL, its contents describe the minimum duration of the wait, which is infinite otherwise. The arguments uaddr2 and val3 are ignored.

//     For futex(7), this call is executed if decrementing the count gave a negative value (indicating contention), and will sleep until another process releases the futex and executes the FUTEX_WAKE operation.
// FUTEX_WAKE
//     This operation wakes at most val processes waiting on this futex address (i.e., inside FUTEX_WAIT). The arguments timeout, uaddr2 and val3 are ignored.

//     For futex(7), this is executed if incrementing the count showed that there were waiters, once the futex value has been set to 1 (indicating that it is available).
// FUTEX_FD (present up to and including Linux 2.6.25)
//     To support asynchronous wakeups, this operation associates a file descriptor with a futex. If another process executes a FUTEX_WAKE, the process will receive the signal number that was passed in val. The calling process must close the returned file descriptor after use. The arguments timeout, uaddr2 and val3 are ignored.

//     To prevent race conditions, the caller should test if the futex has been upped after FUTEX_FD returns.

//     Because it was inherently racy, FUTEX_FD has been removed from Linux 2.6.26 onward.
// FUTEX_REQUEUE (since Linux 2.5.70)
//     This operation was introduced in order to avoid a "thundering herd" effect when FUTEX_WAKE is used and all processes woken up need to acquire another futex. This call wakes up val processes, and requeues all other waiters on the futex at address uaddr2. The arguments timeout and val3 are ignored.
// FUTEX_CMP_REQUEUE (since Linux 2.6.7)
//     There was a race in the intended use of FUTEX_REQUEUE, so FUTEX_CMP_REQUEUE was introduced. This is similar to FUTEX_REQUEUE, but first checks whether the location uaddr still contains the value val3. If not, the operation fails with the error EAGAIN. The argument timeout is ignored.


int futex(int *uaddr, int op, int val, const  *timeout,
          int *uaddr2, int val3)
{
    return -1;
}

int futex_wait(int *addr, int val, long timeout, int flags)
{
    struct timespec timespec;
    // timespec.tv_sec = timeout;
    return syscall(SYS_futex, addr, FUTEX_WAIT, val, &timespec, NULL, 0);
}

int futex_requeue(int *addr, int val, int val2, int *addr2, int flags)
{
    return 0;// syscall(SYS_futex, addr, FUTEX_REQUEUE, val, NULL, addr2, val2);
}

int futex_wake(int *addr, int val)
{
    return syscall(SYS_futex, addr, FUTEX_WAIT, val, NULL, NULL, 0);
}


/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */

xtime_t xtime_read(xtime_name_t name)
{
    return time(NULL) * 1000000;
}

