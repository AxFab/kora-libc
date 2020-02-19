#ifndef __BITS_TIMESPEC_H
#define __BITS_TIMESPEC_H 1

#include <bits/types.h>

struct timespec {
    __time_t tv_sec;
    __syscall_slong_t tv_nsec;
};

#endif  /* __BITS_TIMESPEC_H */
