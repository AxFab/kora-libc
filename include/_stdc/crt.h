#ifndef __STDC_CRT_H
#define __STDC_CRT_H 1

#include <stddef.h>

void *malloc(size_t len);
void free(void* ptr);

int read(int fd, char *buf, size_t len);
int write(int fd, const char *buf, size_t len);
int lseek(int fd, size_t pos, int dir);
int close(int fd);

int open(const char *path, int flags, ...);
int fcntl(int fd, int cmd, ...);

#endif  /* __STDC_CRT_H */
