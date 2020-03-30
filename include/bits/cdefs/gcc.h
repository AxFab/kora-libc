#define _Noreturn __attribute__((noreturn))
#define PACK(decl) decl __attribute__((packed))
#define thread_local __thread
#define unlikely(c)  c
#define likely(c)  c

#if WORDSIZE == 32
#    define __ILP32
#    define __ILPx
#else
#    define __LP64
#    define __LPx
#endif
