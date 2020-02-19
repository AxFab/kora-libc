#ifndef __BITS_ALLOC_H
#define __BITS_ALLOC_H 1


#include <stddef.h>

void *malloc(size_t size);
void *calloc(size_t nmemb, size_t size);

void *realloc(void *ptr, size_t size);

void free(void *ptr);
void cfree(void *ptr);



void *valloc(size_t size);

int posix_memalign(void **memptr, size_t alignment, size_t size);
void *aligned_alloc(size_t alignment, size_t size);


#endif  /* __BITS_ALLOC_H */
