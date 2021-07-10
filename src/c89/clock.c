#include <bits/xtime.h>
#include <bits/types.h>

__clock_t clock()
{
    return xtime_read(XTIME_CPUTIME);
}

double difftime(__time_t t1, __time_t t0)
{
    return t1 - t0;
}


