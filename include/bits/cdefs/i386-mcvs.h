
#define _Noreturn __declspec(noreturn)
#define PACK(decl) __pragma(pack(push,1)) decl __pragma(pack(pop))
#define __thread __declspec(thread)
#define unlikely(c) c
#define likely(c) c

#define PAGE_SIZE  4096
#define WORDSIZE 32
#define __ARCH  "i386"
#define __ILP32
#define __ILPx

