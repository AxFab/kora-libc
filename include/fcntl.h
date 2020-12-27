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
#ifndef __FCNTL_H
#define __FCNTL_H 1

#include <bits/cdefs.h>
#if !defined __UNIX && !defined __POSIX
#error "The header <fcntl.h> requires unix or posix support."
#endif


#include <bits/stat.h>
#include <bits/fcntl.h>
#include <bits/libio.h>
#include <bits/timespec.h>
#include <bits/types.h>

struct flock {
    short int l_type;
    short int l_whence;
    __off_t l_start;
    __off_t l_len;
    __pid_t l_pid;
};


int fcntl(int fd, int cmd, ...);
int open(const char *file, int oflag, ...);
int openat(int fd, const char *file, int oflag, ...);
int creat(const char *file, __mode_t mode);
int lockf(int fd, int cmd, __off_t len);
int posix_fadvise(int fd, __off_t offset, __off_t len, int advise);
int posix_fallocate(int fd, __off_t offset, __off_t len);

#endif  /* __FCNTL_H */
