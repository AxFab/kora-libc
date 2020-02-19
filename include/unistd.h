#ifndef __UNISTD_H
#define __UNISTD_H 1

#include <stddef.h>
#include <bits/types.h>

// int open(const char*, int flags, ...);
int close(int fd);

int read(int fd, void *buf, size_t len);
int write(int fd, const void *buf, size_t len);

int lseek(int fd, __off_t off, int whence);

#endif  /* __UNISTD_H */
