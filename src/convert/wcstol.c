/*
 *      This file is part of the KoraOS project.
 *  Copyright (C) 2015-2019  <Fabien Bavent>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *   - - - - - - - - - - - - - - -
 */
#include <stddef.h>
#include <wchar.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <kora/mcrs.h>

#if 1
typedef unsigned long long __ulong;
#else
typedef unsigned long __ulong;
#endif

#define LOWER 0x20
#define UNSIGNED_MINUS(v)  ((~(v))+1)

const wchar_t *__utoa_wdigits =
    L"0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ+=";
const wchar_t *__utoa_wdigitsX =
    L"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+=";


__ulong __wcstox(const wchar_t *wc, wchar_t **endptr, int base, wchar_t *sign)
{
    int v;
    wchar_t *pst;
    __ulong value = 0;
    __ulong bkp = 0;

    if (endptr)
        (*endptr) = (wchar_t *)wc;

    while (iswspace(*wc))
        wc++;

    (*sign) = *wc == '-' ?  '-' : '+';

    if (*wc == '-' || *wc == '+')
        wc++;

    if (base == 0) {
        if (wc[0] != '0')
            base = 10;


        else if ((wc[1] | LOWER) == 'x') {
            base = 16;
            wc += 2;

        } else {
            base = 8;
            wc++;
        }
    }

    pst = wcschr(__utoa_wdigits, *wc);
    v = (pst == NULL) ? 65 : pst - __utoa_wdigits;
    if (v >= base) {
        errno = EINVAL;
        return 0;
    }

    for (;; wc++) {

        pst = wcschr(__utoa_wdigits, *wc);
        v = (pst == NULL) ? 65 : pst - __utoa_wdigits;
        if (v >= base) {
            pst = wcschr(__utoa_wdigits, *wc | LOWER);
            v = (pst == NULL) ? 65 : pst - __utoa_wdigits;
        }

        if (v >= base)
            break;

        bkp = value * base;
        if (value != 0 && bkp / base != value) {
            (*sign) = 'o';
            return 0;
        }
        value *= base;
        value += v;
    }

    if (endptr)
        (*endptr) = (wchar_t *)wc;

    return value;
}

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/* Convert ASCII string to long integer */
long wcstol(const wchar_t *nptr, wchar_t **endptr, int base)
{
    wchar_t sign;
    __ulong value;

    errno = 0;
    if (base != 0 && (base < 2 || base > 36)) {
        errno = EINVAL;
        return 0;
    }

    value = __wcstox(nptr, endptr, base, &sign);

    if (sign == 'o') {
        errno = EOVERFLOW;
        if (endptr)
            (*endptr) = (wchar_t *)nptr;
        return 0;
    }

    if (sign == '+') {
        if (value > LONG_MAX) {
            errno = EOVERFLOW;
            if (endptr)
                (*endptr) = (wchar_t *)nptr;
            return 0;
        }

        return (long) value;

    } else {

        if (value > (__ulong)(LONG_MIN)) {
            errno = EOVERFLOW;
            if (endptr)
                (*endptr) = (wchar_t *)nptr;
            return 0;
        }

        return (long)UNSIGNED_MINUS(value);
    }
}

/* Convert ASCII string to unsigned long integer */
unsigned long wcstoul(const wchar_t *nptr, wchar_t **endptr, int base)
{
    wchar_t sign;
    __ulong value;

    errno = 0;
    if (base != 0 && (base < 2 || base > 36)) {
        errno = EINVAL;
        return 0;
    }

    // Handle '-' sign
    if (endptr)
        (*endptr) = (wchar_t *)nptr;
    while (iswspace(*nptr))
        nptr++;
    if (*nptr == '-') {
        errno = EINVAL;
        return 0;
    }

    value = __wcstox(nptr, endptr, base, &sign);

    if (sign == 'o') {
        errno = EOVERFLOW;
        if (endptr)
            (*endptr) = (wchar_t *)nptr;
        return 0;
    }

    if (value > ULONG_MAX) {
        errno = EOVERFLOW;
        if (endptr)
            (*endptr) = (wchar_t *)nptr;
        return 0;
    }

    return (unsigned long)value;
}


#ifdef __USE_C99

long long wcstoll(const wchar_t *nptr, wchar_t **endptr, int base)
{
    wchar_t sign;
    __ulong value;

    errno = 0;
    if (base != 0 && (base < 2 || base > 36)) {
        errno = EINVAL;
        return 0;
    }

    value = __wcstox(nptr, endptr, base, &sign);

    if (sign == 'o') {
        errno = EOVERFLOW;

        if (endptr)
            (*endptr) = (wchar_t *)nptr;

        return 0;
    }

    if (sign == '+') {
        if (value > LLONG_MAX) {
            errno = EOVERFLOW;

            if (endptr)
                (*endptr) = (wchar_t *)nptr;

            return 0;
        }

        return (long long) value;

    } else {

        if (value > (-(__ulong)LLONG_MIN)) {
            errno = EOVERFLOW;

            if (endptr)
                (*endptr) = (wchar_t *)nptr;

            return 0;
        }

        return (long long) - value;
    }
}

unsigned long long wcstoull(const wchar_t *nptr, wchar_t **endptr, int base)
{
    wchar_t sign;
    __ulong value;

    errno = 0;
    if (base != 0 && (base < 2 || base > 36)) {
        errno = EINVAL;
        return 0;
    }

    value = __wcstox(nptr, endptr, base, &sign);

    if (sign == 'o') {
        errno = EOVERFLOW;

        if (endptr)
            (*endptr) = (wchar_t *)nptr;

        return 0;
    }

    if (value > ULLONG_MAX) {
        errno = EOVERFLOW;

        if (endptr)
            (*endptr) = (wchar_t *)nptr;

        return 0;
    }

    return (unsigned long long)(sign == '+' ? value : -value);
}

#endif
