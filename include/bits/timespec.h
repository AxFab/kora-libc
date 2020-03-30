#ifndef _BITS_TIMESPEC_H
#define _BITS_TIMESPEC_H 1



#include <bits/types.h>


struct timespec {
    __time_t tv_sec;
    __syscall_slong_t tv_nsec;
};




#endif /* _BITS_TIMESPEC_H */
