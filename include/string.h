#ifndef __STRING_H
#define __STRING_H 1

#include <stddef.h>


#define _TVOID void
#define _TCHAR char
#define _SFM(n)  mem ## n
#define _SFX(n)  str ## n
#include <_stdc/string.h>
#undef _TVOID
#undef _TCHAR
#undef _SFM
#undef _SFX


/* Gives an error message string. */
char *strerror_r(int errnum, char *buf, int len);
/* Gives an error message string. */
char *strerror(int errnum);

#endif  /* __STRING_H */
