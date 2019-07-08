#ifndef __CTYPE_H
#define __CTYPE_H 1


#include <_stdc/crt.h>
// #include <_stdc/crt.c>

#include <bits/types.h>
// #include <endian.h>

enum {
    _ISupper = 0x001,
    _ISlower = 0x002,
    _ISalpha = 0x004,
    _ISdigit = 0x008,
    _ISxdigit = 0x010,
    _ISspace = 0x020,
    _ISprint = 0x040,
    _ISgraph = 0x080,
    _ISblank = 0x100,
    _IScntrl = 0x200,
    _ISpunct = 0x400,
    _ISalnum = 0x800,
};

unsigned short int __ctype_b(int);
__int32_t __ctype_tolower(int);
__int32_t __ctype_toupper(int);


#define CTYPE(n)  int n(int c);
#include <_stdc/ctype.h>


#include <_stdc/ctype.h>

int tolower(int c);
int toupper(int c);

int isascii(int c);
int toascii(int c);


#define __CTYPE(c)  (__ctype_b((int)c))

#define isalnum(c)  (_ISalnum & __CTYPE(c))
#define isalpha(c)  (_ISalpha & __CTYPE(c))
#define iscntrl(c)  (_IScntrl & __CTYPE(c))
#define isdigit(c)  (_ISdigit & __CTYPE(c))
#define islower(c)  (_ISlower & __CTYPE(c))
#define isgraph(c)  (_ISgraph & __CTYPE(c))
#define isprint(c)  (_ISprint & __CTYPE(c))
#define ispunct(c)  (_ISpunct & __CTYPE(c))
#define isspace(c)  (_ISspace & __CTYPE(c))
#define isupper(c)  (_ISupper & __CTYPE(c))
#define isxdigit(c)  (_ISxdigit & __CTYPE(c))
#define isblank(c)  (_ISblank & __CTYPE(c))


// #include <xlocale.h>
// #define CTYPE(n)  int n ## _l(int c, __locale_t l);
// #include <_stdc/ctype.h>

// int tolower_l (int c, __locale_t l);
// int toupper_l (int c, __locale_t l);

#endif  /* __CTYPE_H */
