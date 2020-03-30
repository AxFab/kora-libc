#ifndef __BITS_CRT_H
#define __BITS_CRT_H 1

#include <stddef.h>

void *malloc(size_t len);
void free(void *ptr);

int open(const char *path, int flags, ...);
int close(int fd);
int read(int fd, char *buf, size_t len);
int write(int fd, const char *buf, size_t len);
int lseek(int fd, int off, int whence);


#endif  /* __BITS_CRT_H */
