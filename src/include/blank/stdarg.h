#ifndef __STDARG_H
#define __STDARG_H 1


#include <bits/cdefs.h>

__STDC_GUARD

#if __GNUC__ >= 3

typedef __builtin_va_list va_list;

#define va_start(v,l)   __builtin_va_start(v,l)
#define va_end(v)       __builtin_va_end(v)
#define va_arg(v,l)     __builtin_va_arg(v,l)
#define va_copy(d,s)    __builtin_va_copy(d,s)

#else

# error "Issue with __STDARG_H"

#endif


__STDC_END

#endif  /* __STDARG_H */
