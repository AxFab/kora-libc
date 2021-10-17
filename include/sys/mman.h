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
#ifndef _SYS_MMAN_H
#define _SYS_MMAN_H 1

#include <bits/types.h>
#include <bits/mman.h>

__STDC_GUARD

void *mmap(void *addr, size_t length, int prot, int flags, int fd, __off_t off);
int munmap(void *addr, size_t length);

int mprotect(void *addr, size_t length, int prot);
int msync(void *addr, size_t length, int flags);

int mlock(const void *addr, size_t length);
int munlock(const void *addr, size_t length);
int mlockall(int);
int munlockall(void);

#if defined(__GNU) || defined(__BSD)
int madvise(void *, size_t, int);
int mincore(void *, size_t, unsigned char *);
#endif

int shm_open(const char *name, int oflag, __mode_t mode);
int shm_unlink(const char *name);


#ifdef __LARGEFILE64
# define mmap64 mmap
#endif

__STDC_END

#endif  /* _SYS_MMAN_H */
