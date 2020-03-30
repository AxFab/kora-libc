#ifndef _SYS_MMAN_H
#define _SYS_MMAN_H 1

#include <bits/types.h>

void *mmap(void *addr, size_t length, int prot, int flags, int fd, __off_t off);
int munmap(void *addr, size_t length);




#endif  /* _SYS_MMAN_H */
