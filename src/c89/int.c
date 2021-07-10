#include <stdlib.h>
#include <inttypes.h>

int abs(int value)
{
    return (value >= 0) ? value : -value;
}

long labs(long value)
{
    return (value >= 0) ? value : -value;
}

long long llabs(long long value)
{
    return (value >= 0) ? value : -value;
}

div_t div(int numer, int denom)
{
    div_t rc;
    rc.quot = numer / denom;
    rc.rem  = numer % denom;
    return rc;
}

ldiv_t ldiv(long numer, long denom)
{
    ldiv_t rc;
    rc.quot = numer / denom;
    rc.rem  = numer % denom;
    return rc;
}

lldiv_t lldiv(long long numer, long long denom)
{
    lldiv_t rc;
    rc.quot = numer / denom;
    rc.rem  = numer % denom;
    return rc;
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

intmax_t imaxabs(intmax_t value)
{
    return (value >= 0) ? value : -value;
}

imaxdiv_t imaxdiv(intmax_t numer, intmax_t denom)
{
    imaxdiv_t rc;
    rc.quot = numer / denom;
    rc.rem  = numer % denom;
    return rc;
}

