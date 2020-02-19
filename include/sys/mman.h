#ifndef __SYS_MMAN_H
#define __SYS_MMAN_H 1


void *mmap(void *addr, size_t len, int flags, int prot, int fd, off_t off);
void munmap(void *addr, size_t len);


#endif  /* __SYS_MMAN_H */
