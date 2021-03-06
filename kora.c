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
// #include <sys/mman.h>
#include <string.h>
#include <errno.h>

#define MMAP_HEAP 0x100

FILE *fvopen(int fd, int o);
void setup_allocator(void *, size_t);

_Noreturn void exit(int status)
{
    for (;;)
        syscall(SYS_EXIT, status);
}

int fork()
{
    return -1;
}

long long clock_read(int no)
{
    return -1;
}

int futex_wait(int *addr, int val, long timeout, int flags)
{
    return syscall(SYS_FUTEX_WAKE, addr, val, timeout, flags);
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
    return syscall(SYS_SINFO, 12/*SNFO_PWD*/, path, len);
}

char *getcwd(char *buf, size_t len)
{
    int ret = syscall(SYS_GINFO, 12/*SNFO_PWD*/, buf, len);
    return ret == 0 ? buf : NULL;
}

void thrd_create()
{
}

int __exec(char *name, int argc, char **argv, int fds[3])
{
    int i;
    char cmdline[4096];

    strncpy(cmdline, name, 4096);
    for (i = 0; i < argc; ++i) {
        strncat(cmdline, " ", 4096);
        strncat(cmdline, argv[i], 4096);
    }

    int pid = fork();
    if (pid != 0)
        return pid;

    exit(-1);
}

int window(int service, int width, int height, int flags)
{
    return syscall(SYS_WINDOW, service, width, height, flags);
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


int open(const char *path, int flags, ...)
{
    va_list ap;
    va_start(ap, flags);
    int mode = va_arg(ap, int);
    va_end(ap);
    return syscall(SYS_OPEN, -1, path, flags, mode);
}

int close(int fd)
{
    return syscall(SYS_CLOSE, fd);
}

int read(int fd, void *buf, size_t lg)
{
    return syscall(SYS_READ, fd, buf, lg);
}

int write(int fd, const void *buf, size_t lg)
{
    return syscall(SYS_WRITE, fd, buf, lg);
}

int lseek(int fd, __off_t offset, unsigned int origin)
{
    return -1;
}

int fcntl(int fd, int cmd, ...)
{
    void *args = ((size_t*)&cmd) + 1;
    return syscall(SYS_FCNTL, fd, cmd, args);
    // return -1;
}

// int fstat(int file, struct stat *st);
// int stat(const char *file, struct stat *st);
// int link(char *old, char *new);
// int unlink(char *name);


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
    void *heap = mmap(NULL, 16 * _Mib_, 06, MMAP_HEAP, -1, 0);
    if (heap == NULL || heap == (void *) - 1)
        __perror_fail(ENOMEM, __FILE__, __LINE__, "Unable to allocate first heap segment");
    setup_allocator(heap, 16 * _Mib_);

    stdin = fvopen(0, O_RDONLY);
    stdout = fvopen(1, O_WRONLY);
    stderr = fvopen(2, O_WRONLY);
}

void opendir() {
}
void readdir() {
}
void closedir() {
}

void stat() {
}
void lstat() {
}
void readlink() {
}
void localtime_r() {
}
void strftime() {
}

