/*
 *      This file is part of the KoraOS project.
 *  Copyright (C) 2015-2021  <Fabien Bavent>
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
#ifndef _BITS_SYSCALLS_H
#define _BITS_SYSCALLS_H 1

#include <bits/types.h>
#include <bits/xtime.h>
#include <stdint.h>

enum syscall_no {
    SYS_EXIT = 0,
    SYS_SLEEP,

    SYS_FUTEX_WAIT,
    SYS_FUTEX_REQUEUE,
    SYS_FUTEX_WAKE,

    SYS_SPAWN,
    SYS_THREAD,

    SYS_MMAP,
    SYS_MUNMAP,
    SYS_MPROTECT,

    SYS_GINFO, // 10
    SYS_SINFO,

    SYS_OPEN,
    SYS_CREATE,
    SYS_CLOSE,
    SYS_OPENDIR,
    SYS_READDIR,
    SYS_SEEK,
    SYS_READ, // 16
    SYS_WRITE,
    SYS_ACCESS,
    SYS_FCNTL, // 19

    SYS_PIPE,
    SYS_WINDOW,
    SYS_FSTAT,

    SYS_XTIME,
};

enum sys_vars {
    SNFO_NONE = 0,
    SNFO_ARCH,
    SNFO_SNAME,
    SNFO_OSNAME,
    SNFO_PWD,
    // SNFO_ARCH
    // SNFO_GITH
    // SNFO_SNAME
    // SNFO_VERSION
    // SNFO_RELEASE
    // SNFO_OSNAME
    // SNFO_HOSTNAME
    // SNFO_DOMAIN
    // SNFO_USER
    // SNFO_USERNAME
    // SNFO_USERMAIL
    // SNFO_PWD
};

struct dirent {
    int d_ino;
    int d_off;
    unsigned short int d_reclen;
    unsigned char d_type;
    char d_name[256];
};

struct filemeta {
    int ino;
    int dev;
    int block;
    int ftype;

    int64_t size;
    int64_t rsize;

    uint64_t ctime;
    uint64_t mtime;
    uint64_t atime;
    uint64_t btime;
};

#endif  /* _BITS_SYSCALLS_H */
