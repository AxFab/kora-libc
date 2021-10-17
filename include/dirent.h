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
#ifndef __DIRENT_H
#define __DIRENT_H 1

#include <bits/cdefs.h>
#if !defined __UNIX && !defined __POSIX
#error "The header <dirent.h> requires unix or posix support."
#endif


/* We require __ssize_t, __ino_t and __off_t */
#include <bits/types.h>
// #include <bits/posix1_lim.h>
#include <stddef.h>
#include <kora/syscalls.h>

// struct dirent {
//     __ino_t d_ino;
//     __off_t d_off;

//     unsigned short int d_reclen;
//     unsigned char d_type;
//     char d_name[256];
// };


enum {
    DT_UNKNOWN = 0,
    DT_FIFO = 1,
    DT_CHR = 2,
    DT_DIR = 4,
    DT_BLK = 6,
    DT_REG = 8,
    DT_LNK = 10,
    DT_SOCK = 12,
    DT_WHT = 14
};

typedef struct __dirstream DIR;


DIR *opendir(const char *name);
int closedir(DIR *dirp);

DIR *fdopendir(int fd);
int dirfd(DIR *dirp);

struct dirent *readdir(DIR *dirp);
int readdir_r(DIR *restrict dirp, struct dirent *restrict entry,
              struct dirent **restrict result);


void rewinddir(DIR *dirp);
void seekdir(DIR *dirp, long int pos);
long int telldir(DIR *dirp);


int scandir(const char *restrict dir, struct dirent ***restrict namelist,
            int (*selector)(const struct dirent *),
            int (*cmp)(const struct dirent **, const struct dirent **));
int alphasort(const struct dirent **e1, const struct dirent **e2);
__ssize_t getdirentries(int fd, char *restrict buf, size_t nbytes,
                        __off_t *restrict basep);

#endif  /* __DIRENT_H */
