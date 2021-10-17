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
#include <sys/mman.h>
#include <sys/syscall.h>
#include <errno.h>
#include "syscallno.h"

struct mmap {
    unsigned long addr;
    unsigned long len;
    unsigned long prot;
    unsigned long flags;
    unsigned long fd;
    unsigned long offset;

    // void *addr;
    // size_t length;
    // int protection;
    // int flags;
    // int fd;
    // __off_t off;
};

void *mmap(void *addr, size_t length, int prot, int flags, int fd, __off_t off)
{
    long ret;
    // if (off & OFF_MASK) {
    //     errno = EINVAL;
    //     return MAP_FAILED;
    // }
    // if (len >= PTRDIFF_MAX) {
    //     errno = ENOMEM;
    //     return MAP_FAILED;
    // }

    struct mmap args;
    args.addr = (size_t)addr;
    args.len = length;
    args.prot = prot;
    args.flags = flags;
    args.fd = fd;
    args.offset = off;

    ret = syscall(SYS_old_mmap, &args);
    // #ifdef SYS_mmap2
    //     ret = syscall(SYS_mmap, addr, length, prot, flags, fd, (__size_t)off);
    // #else
    //     ret = syscall(SYS_mmap, addr, length, prot, flags, fd, (__size_t)off);
    // #endif
    /* Fixup incorrect EPERM from kernel. */
    // if (ret == -EPERM && !start && (flags&MAP_ANON) && !(flags&MAP_FIXED))
    // ret = -ENOMEM;

    return (void *)ret;
}

int munmap(void *addr, size_t length)
{
    return syscall(SYS_munmap, addr, length);
}

// int mprotect(void *addr, size_t length, int prot)
// int msync(void *addr, size_t length, int flags);

// int mlock(const void *addr, size_t length);
// int munlock(const void *addr, size_t length);
// int mlockall(int);
// int munlockall(void);
