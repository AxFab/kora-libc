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
// #include <kora/splock.h>
#include <kora/mcrs.h>
// #include <syscalls.h>
#include <sys/mman.h>
#include <errno.h>

#define MMAP_HEAP 5

_Noreturn void exit(int status)
{
    for (;;);
}

int fork()
{
    return -1;
}

// int execve(char *name, char **argv, char **env);
// int getpid();
// int wait(int *status);
// int kill(int pid, int sig);


/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */

void *mmap(void *addr, size_t length, int prot, int flags, int fd, __off_t off)
{
    return (void *)-1;
}

int munmap(void *addr, size_t length)
{
    return -1;
}

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */


int open(const char *path, int flags, ...)
{
    va_list ap;
    va_start(ap, flags);
    int mode = va_arg(ap, int);
    va_end(ap);
    return -1;
}

int close(int fd)
{
    return -1;
}

int read(int fd, void *buf, size_t lg)
{
    return -1;
}

int write(int fd, const void *buf, size_t lg)
{
    return -1;
}

int lseek(int fd, __off_t offset, unsigned int origin)
{
    return -1;
}

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

