#ifndef __SYS_STAT_H
#define __SYS_STAT_H 1

#include <bits/types.h>
#include <bits/stat.h>
#include <time.h>


int stat(const char *__restrict file, struct stat *__restrict buf);
int fstat(int fd, struct stat *buf);
int fstatat(int fd, const char *__restrict file, struct stat *__restrict buf, int flag);
int lstat(const char *__restrict file, struct stat *__restrict buf);
int chmod(const char *file, __mode_t mode);
int lchmod(const char *file, __mode_t mode);
int fchmod(int fd, __mode_t mode);
int fchmodat(int fd, const char *file, __mode_t mode, int flag);
__mode_t umask (__mode_t mask);
int mkdir (const char *path, __mode_t mode);
int mkdirat (int fd, const char *path, __mode_t mode);
int mknod (const char *path, __mode_t mode, __dev_t dev);
int mknodat (int fd, const char *path, __mode_t mode, __dev_t dev);
int mkfifo (const char *path, __mode_t mode);
int mkfifoat (int fd, const char *path, __mode_t mode);
int utimensat (int fd, const char *path, const struct timespec times[2], int flags);

int futimens (int fd, const struct timespec times[2]);

int __fxstat (int ver, int fildes, struct stat *stat_buf);
int __xstat (int ver, const char *filename, struct stat *stat_buf);
int __lxstat (int ver, const char *filename, struct stat *stat_buf);
int __fxstatat (int ver, int fildes, const char *filename, struct stat *stat_buf, int flag);
int __xmknod (int ver, const char *path, __mode_t mode, __dev_t *dev);
int __xmknodat (int ver, int fd, const char *path, __mode_t mode, __dev_t *dev);

#endif  /* __SYS_STAT_H */
