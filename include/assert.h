#ifndef __ASSERT_H
#define __ASSERT_H 1

#include <bits/cdefs.h>
// features.h

#if defined __FUNC__
#define assert(n) do { \
    if (!(n)) \
        __assert_fail(#n, __FILE__, __LINE__,__FUNC__); \
    } while(0)
#else
#define assert(n) do { \
    if (!(n)) \
        __assert(#n, __FILE__, __LINE__); \
    } while(0)
#endif

_Noreturn void __assert_fail(const char *assertion, const char *file, unsigned int line, const char *function);
_Noreturn void __assert_perror_fail(int errnum, const char *file, unsigned int line, const char *function);
_Noreturn void __assert(const char *assertion, const char *file, int line);


#endif  /* __ASSERT_H */
