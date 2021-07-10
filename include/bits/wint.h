#ifndef __BITS_WINT_H
#define __BITS_WINT_H 1

#include <stddef.h>

#define MB_CUR_MAX 6
#define WEOF 0xffffffffU

typedef union __mbstate_t mbstate_t;
union __mbstate_t {
    unsigned long long ll;
    struct {
        unsigned int len, val;
    };
};


typedef unsigned int wint_t;


#endif  /* __BITS_WINT_H */
