/*
 *      This file is part of the KoraOS project.
 *  Copyright (C) 2015-2021  <Fabien Bavent>
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
#include <string.h>
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

const char *__utoa_digits =
    "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ+=";
const char *__utoa_digitsX =
    "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+=";


__ulong __strtox(const char *str, char **endptr, int base, char *sign)
{
    int v;
    char *pst;
    __ulong value = 0;
    __ulong bkp = 0;

    if (endptr)
        (*endptr) = (char *)str;

    while (isspace(*str))
        str++;

    (*sign) = *str == '-' ?  '-' : '+';

    if (*str == '-' || *str == '+')
        str++;

    if (base == 0) {
        if (str[0] != '0')
            base = 10;


        else if ((str[1] | LOWER) == 'x') {
            base = 16;
            str += 2;

        } else {
            base = 8;
            str++;
        }
    }

    pst = strchr(__utoa_digits, *str);
    v = (pst == NULL) ? 65 : pst - __utoa_digits;
    if (v >= base) {
        errno = EINVAL;
        return 0;
    }

    for (;; str++) {

        pst = strchr(__utoa_digits, *str);
        v = (pst == NULL) ? 65 : pst - __utoa_digits;
        if (v >= base) {
            pst = strchr(__utoa_digits, *str | LOWER);
            v = (pst == NULL) ? 65 : pst - __utoa_digits;
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
        (*endptr) = (char *)str;

    return value;
}

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/* Convert ASCII string to long integer */
long strtol(const char *nptr, char **endptr, int base)
{
    char sign;
    __ulong value;

    errno = 0;
    if (base != 0 && (base < 2 || base > 36)) {
        errno = EINVAL;
        return 0;
    }

    value = __strtox(nptr, endptr, base, &sign);

    if (sign == 'o') {
        errno = EOVERFLOW;
        if (endptr)
            (*endptr) = (char *)nptr;
        return 0;
    }

    if (sign == '+') {
        if (value > LONG_MAX) {
            errno = EOVERFLOW;
            if (endptr)
                (*endptr) = (char *)nptr;
            return 0;
        }

        return (long) value;

    } else {

        if (value > (__ulong)(LONG_MIN)) {
            errno = EOVERFLOW;
            if (endptr)
                (*endptr) = (char *)nptr;
            return 0;
        }

        return (long)UNSIGNED_MINUS(value);
    }
}

/* Convert ASCII string to unsigned long integer */
unsigned long strtoul(const char *nptr, char **endptr, int base)
{
    char sign;
    __ulong value;

    errno = 0;
    if (base != 0 && (base < 2 || base > 36)) {
        errno = EINVAL;
        return 0;
    }

    // Handle '-' sign
    if (endptr)
        (*endptr) = (char *)nptr;
    while (isspace(*nptr))
        nptr++;
    if (*nptr == '-') {
        errno = EINVAL;
        return 0;
    }

    value = __strtox(nptr, endptr, base, &sign);

    if (sign == 'o') {
        errno = EOVERFLOW;
        if (endptr)
            (*endptr) = (char *)nptr;
        return 0;
    }

    if (value > ULONG_MAX) {
        errno = EOVERFLOW;
        if (endptr)
            (*endptr) = (char *)nptr;
        return 0;
    }

    return (unsigned long)value;
}

/* Convert a string to an integer */
int atoi(const char *nptr)
{
    char sign;
    __ulong value = __strtox(nptr, NULL, 10, &sign);
    return (int)(sign == '+') ? value : UNSIGNED_MINUS(value);
}

/* Convert a string to an integer */
long atol(const char *nptr)
{
    char sign;
    __ulong value = __strtox(nptr, NULL, 10, &sign);
    return (long)(sign == '+') ? value : UNSIGNED_MINUS(value);
}

#ifdef __USE_C99
/* Convert a string to an integer */
long long atoll(const char *nptr)
{
    char sign;
    __ulong value = __strtox(nptr, NULL, 10, &sign);
    return (long long)(sign == '+') ? value : -value;
}

/* Convert a string to an integer */
long long atoq(const char *nptr)
{
    char sign;
    __ulong value = __strtox(nptr, NULL, 10, &sign);
    return (long long)(sign == '+') ? value : -value;
}

long long strtoll(const char *nptr, char **endptr, int base)
{
    char sign;
    __ulong value;

    errno = 0;
    if (base != 0 && (base < 2 || base > 36)) {
        errno = EINVAL;
        return 0;
    }

    value = __strtox(nptr, endptr, base, &sign);

    if (sign == 'o') {
        errno = EOVERFLOW;

        if (endptr)
            (*endptr) = (char *)nptr;

        return 0;
    }

    if (sign == '+') {
        if (value > LLONG_MAX) {
            errno = EOVERFLOW;

            if (endptr)
                (*endptr) = (char *)nptr;

            return 0;
        }

        return (long long) value;

    } else {

        if (value > (-(__ulong)LLONG_MIN)) {
            errno = EOVERFLOW;

            if (endptr)
                (*endptr) = (char *)nptr;

            return 0;
        }

        return (long long) - value;
    }
}

unsigned long long strtoull(const char *nptr, char **endptr, int base)
{
    char sign;
    __ulong value;

    errno = 0;
    if (base != 0 && (base < 2 || base > 36)) {
        errno = EINVAL;
        return 0;
    }

    value = __strtox(nptr, endptr, base, &sign);

    if (sign == 'o') {
        errno = EOVERFLOW;

        if (endptr)
            (*endptr) = (char *)nptr;

        return 0;
    }

    if (value > ULLONG_MAX) {
        errno = EOVERFLOW;

        if (endptr)
            (*endptr) = (char *)nptr;

        return 0;
    }

    return (unsigned long long)(sign == '+' ? value : -value);
}

#endif


/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

char *_utoa(__ulong value, char *str, int base, const char *digits)
{
    __ulong quot, rem;
    int sp = 0, j = 0;
    char stack[sizeof(__ulong) * 8] = { 0 };

    if (value == 0) {
        str[0] = '0';
        str[1] = '\0';
        return 0;
    }

    while (value) {
        quot = value / base;
        rem = value % base;
        stack[sp++] = digits[rem];
        value = quot;
    }

    str [sp] = '\0';

    while (sp > 0) {
        --sp;
        str [j++] = stack[sp];
    }

    return str;
}

char *itoa(int value, char *str, int base)
{
    char *ptr = str;
    if (base < 2 || base > 36)
        return NULL;

    if (base == 10 && value < 0) {
        *(str++) = '-';
        value = -value;
    }

    _utoa(value, str, base, __utoa_digits);
    return ptr;
}
