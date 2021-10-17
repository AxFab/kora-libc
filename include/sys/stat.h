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
#ifndef __SYS_STAT_H
#define __SYS_STAT_H 1

#include <bits/cdefs.h>
#include <bits/types.h>
#include <bits/stat.h>
#include <time.h>

__STDC_GUARD

int stat(const char *__restrict file, struct stat *__restrict buf);
int fstat(int fd, struct stat *buf);
int fstatat(int fd, const char *__restrict file, struct stat *__restrict buf, int flag);
int lstat(const char *__restrict file, struct stat *__restrict buf);
int chmod(const char *file, __mode_t mode);
int lchmod(const char *file, __mode_t mode);
int fchmod(int fd, __mode_t mode);
int fchmodat(int fd, const char *file, __mode_t mode, int flag);
__mode_t umask(__mode_t mask);
int mkdir(const char *path, __mode_t mode);
int mkdirat(int fd, const char *path, __mode_t mode);
int futimens(int fd, const struct timespec times[2]);
int utimensat(int fd, const char *path, const struct timespec times[2], int flags);

#if defined(__UNIX) || defined(__GNU) || defined(__BSD)
int mknod(const char *path, __mode_t mode, __dev_t dev);
int mknodat(int fd, const char *path, __mode_t mode, __dev_t dev);
int mkfifo(const char *path, __mode_t mode);
int mkfifoat(int fd, const char *path, __mode_t mode);
#endif


// int __fxstat(int ver, int fildes, struct stat *stat_buf);
// int __xstat(int ver, const char *filename, struct stat *stat_buf);
// int __lxstat(int ver, const char *filename, struct stat *stat_buf);
// int __fxstatat(int ver, int fildes, const char *filename, struct stat *stat_buf, int flag);
// int __xmknod(int ver, const char *path, __mode_t mode, __dev_t *dev);
// int __xmknodat(int ver, int fd, const char *path, __mode_t mode, __dev_t *dev);


#ifdef __LARGEFILE64
#define stat64 stat
#define fstat64 fstat
#define lstat64 lstat
#define fstatat64 fstatat
#define blkcnt64_t __blkcnt_t
#define fsblkcnt64_t __fsblkcnt_t
#define fsfilcnt64_t __fsfilcnt_t
typedef __fpos64_t fpos64_t;
typedef __off64_t off64_t;
#endif

__STDC_END

#endif  /* __SYS_STAT_H */
