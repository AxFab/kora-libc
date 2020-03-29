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
#include <string.h>
#include <errno.h>

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
    void *args = ((size_t *)&cmd) + 1;
    return syscall(SYS_FCNTL, fd, cmd, args);
    // return -1;
}

// int fstat(int file, struct stat *st);
// int stat(const char *file, struct stat *st);
// int link(char *old, char *new);
// int unlink(char *name);

int window(int service, int width, int height, int flags)
{
    return syscall(SYS_WINDOW, service, width, height, flags);
}
