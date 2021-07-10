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
#include <float.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <errno.h>
#include <ctype.h>
#include <bits/libio.h>
#include <kora/mcrs.h>

#define _MANT_LG  16
#define _MANT_BITS  64
#define _MANT_MAX  0x8000000000000000

#define _MDEC_LG  19
#define _MDEC_DIG 9

long double __copysignl(long double x, long double y);
long double __scalbnl(long double x, int n);
long double __scaldcl(long double x, int n);

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// static
long double __scan_float_(FILE *fp, int base, int bits, int emin, int sign, int pok)
{
    int c = fgetc_unlocked(fp);
    while (c == '0')
        c = fgetc_unlocked(fp);

    bool hex = base == 16;
    bool got_radix = false;
    bool got_digit = false;
    bool got_tail = false;
    int radix = '.';
    uint64_t mantisse = 0;
    long exp = 0;
    int digits = 0;
    long double y = 0;
    long double sc = 1;

    // Read digits
    if (c == radix) {
        got_radix = true;
        for (; c == '0'; c = fgetc_unlocked(fp), exp--)
            got_digit = true;
    }

    for (; ((unsigned)(c - '0') < 10U) || ((unsigned)((c | 32) - 'a') < 6U && hex) || c == radix; c = fgetc_unlocked(fp)) {
        if (c == radix) {
            if (got_radix)
                break;
            exp = digits;
            got_radix = true;
            continue;
        }

        got_digit = true;
        int d = c > '9' ? ((c | 32) + 10 - 'a') : c - '0';
        if (digits < _MANT_LG)
            mantisse = mantisse * base + d;
        else if (digits < LDBL_MANT_DIG / 4 + 1) {
            sc /= base;
            y += d * sc;
        } else if (d && !got_tail) {
            y += 0.5 * sc;
            got_tail = true;
        }
        digits++;
    }

    // If no digits
    if (!got_digit) {
        // REWIND
        return sign * 0.0;
    }

    // Fix exponent
    if (!got_radix)
        exp = digits;
    while (digits < _MANT_LG) {
        mantisse *= 16;
        digits++;
    }
    exp *= 4;


    // if ((c|32)=='p') {
    //     e2 = scanexp(f, pok);
    //     if (e2 == LLONG_MIN) {
    //         if (pok) {
    //             shunget(f);
    //         } else {
    //             shlim(f, 0);
    //             return 0;
    //         }
    //         e2 = 0;
    //     }
    // } else {
    //     shunget(f);
    // }

    // Check 'P'
    ungetc_unlocked(c, fp);
    if (!mantisse)
        return sign * 0.0;

    // return __scalbnl(y, exp);
    return -1;
}

static long double __scan_hex_float(FILE *fp, int bits, int emin, int sign, int pok)
{
    int c = fgetc_unlocked(fp);
    while (c == '0')
        c = fgetc_unlocked(fp);

    bool got_radix = false;
    bool got_digit = false;
    bool got_tail = false;
    int radix = '.';
    uint64_t mantisse = 0;
    long exp = 0;
    int digits = 0;
    long double y = 0;
    long double sc = 1;
    long double bias = 0;

    // Read digits
    if (c == radix) {
        got_radix = true;
        for (c = fgetc_unlocked(fp); c == '0'; c = fgetc_unlocked(fp), exp -= 4)
            got_digit = true;
    }

    for (; ((unsigned)(c - '0') < 10U) || ((unsigned)((c | 32) - 'a') < 6U) || c == radix; c = fgetc_unlocked(fp)) {
        if (c == radix) {
            if (got_radix)
                break;
            exp = digits * 4;
            got_radix = true;
            continue;
        }

        got_digit = true;
        int d = c > '9' ? ((c | 32) + 10 - 'a') : c - '0';
        if (digits < _MANT_LG)
            mantisse = mantisse * 16 + d;
        else if (digits < LDBL_MANT_DIG / 4 + 1) {
            sc /= 16;
            y += d * sc;
        } else if (d && !got_tail) {
            y += 0.5 * sc;
            got_tail = true;
        }
        digits++;
    }

    // If no digits
    if (!got_digit) {
        // REWIND
        return sign * 0.0;
    }

    // Fix exponent
    if (!got_radix)
        exp = digits * 4;
    while (digits < _MANT_LG) {
        mantisse *= 16;
        digits++;
    }


    // if ((c|32)=='p') {
    //     e2 = scanexp(f, pok);
    //     if (e2 == LLONG_MIN) {
    //         if (pok) {
    //             shunget(f);
    //         } else {
    //             shlim(f, 0);
    //             return 0;
    //         }
    //         e2 = 0;
    //     }
    // } else {
    //     shunget(f);
    // }

    // Check 'P'
    ungetc_unlocked(c, fp);
    if (!mantisse)
        return sign * 0.0;


    // Setup exponent and check range
    exp -= _MANT_BITS;
    if (exp > -emin) {
        errno = ERANGE;
        return sign * LDBL_MAX * LDBL_MAX;
    }
    if (exp < emin - 2 * LDBL_MANT_DIG) {
        errno = ERANGE;
        return sign * LDBL_MIN * LDBL_MIN;
    }
    while (mantisse < _MANT_MAX) {
        if (y >= 0.5) {
            mantisse += mantisse + 1;
            y += y - 1;
        } else {
            mantisse += mantisse;
            y += y;
        }
        exp--;
    }
    if (bits > _MANT_BITS + exp - emin)
        bits = MAX(_MANT_BITS + exp - emin, 0);


    // Compute value
    if (bits < LDBL_MANT_DIG)
        bias = __copysignl(
                   __scalbnl(1, 32 + LDBL_MANT_DIG - bits - 1), sign);
    if (bits < 32 && y && !(mantisse & 1)) {
        mantisse++;
        y = 0;
    }
    y = bias + sign * (long double)mantisse + sign * y;
    y -= bias;

    if (!y)
        errno = ERANGE;
    return __scalbnl(y, exp);
}

static long double __scan_dec_float(FILE *fp, int bits, int emin, int sign, int pok)
{
    int c = fgetc_unlocked(fp);
    while (c == '0')
        c = fgetc_unlocked(fp);

    bool got_radix = false;
    bool got_digit = false;
    bool got_tail = false;
    int radix = '.';
    uint64_t mantisse = 0;
    long exp = 0;
    int digits = 0;
    long double y = 0;
    long double sc = 1;
    long double bias = 0;

    // Read digits
    if (c == radix) {
        got_radix = true;
        for (c = fgetc_unlocked(fp); c == '0'; c = fgetc_unlocked(fp), exp--)
            got_digit = true;
    }

    for (; ((unsigned)(c - '0') < 10U) || c == radix; c = fgetc_unlocked(fp)) {
        if (c == radix) {
            if (got_radix)
                break;
            exp = digits;
            got_radix = true;
            continue;
        }

        got_digit = true;
        int d = c - '0';
        if (digits < _MDEC_LG)
            mantisse = mantisse * 10 + d;
        else if (digits < _MDEC_DIG / 4 + 1) {
            sc /= 10;
            y += d * sc;
        }
        digits++;
    }

    // If no digits
    if (!got_digit) {
        // REWIND
        return sign * 0.0;
    }

    if (!got_radix)
        exp = digits;
    while (digits < _MDEC_LG) {
        mantisse *= 10;
        digits++;
    }

    // if ((c|32)=='e') {
    //     e2 = scanexp(f, pok);
    //     if (e2 == LLONG_MIN) {
    //         if (pok) {
    //             shunget(f);
    //         } else {
    //             shlim(f, 0);
    //             return 0;
    //         }
    //         e2 = 0;
    //     }
    // } else {
    //     shunget(f);
    // }

    // Check 'e'
    ungetc_unlocked(c, fp);
    if (!mantisse)
        return sign * 0.0;



    return __scaldcl(mantisse, exp - digits);
}

long double __scan_float(FILE *fp, int bits, int emin, int pok)
{
    int sign = 1;
    int c = fgetc_unlocked(fp);
    while (isspace(c))
        c = fgetc_unlocked(fp);

    if (c == '+' || c == '-') {
        sign = c == '-' ? -1 : 1;
        c = fgetc_unlocked(fp);
    }

    if ((c | 32) == 'i') {
        if (__fgets_ifeqi(fp, "infinity") || __fgets_ifeqi(fp, "inf"))
            return sign *  INFINITY;
    } else if ((c | 32) == 'n') {
        if (__fgets_ifeqi(fp, "nan"))
            // TODO -- Can be followed by '('[0-9A-Za-z_]*')'
            return sign *  INFINITY;
    } else if ((unsigned)(c - '0') < 10U) {
        if (c == '0') {
            c = fgetc_unlocked(fp);
            if ((c | 32) == 'x')
                return __scan_hex_float(fp, bits, emin, sign, pok);
            ungetc_unlocked(c, fp);
            c = '0';
        }
        ungetc_unlocked(c, fp);
        return __scan_dec_float(fp, bits, emin, sign, pok);
    }
    errno = EINVAL;
    return 0;
}



static long double __strtofx(const char *str, char **ptr, int bits, int emin)
{
    FILE fp;
    __fstr_open_ro(&fp, str, strlen(str));

    long double y = __scan_float(&fp, bits, emin, 0);

    if (ptr) {
        *ptr = (char *)fp.rbf_.pos_;
    }
    return y;
}

float strtof(const char *restrict str, char **restrict ptr)
{
    return __strtofx(str, ptr, FLT_MANT_DIG, FLT_MIN_EXP - FLT_MANT_DIG);
}

double strtod(const char *restrict str, char **restrict ptr)
{
    return __strtofx(str, ptr, DBL_MANT_DIG, DBL_MIN_EXP - DBL_MANT_DIG);
}

long double strtold(const char *restrict str, char **restrict ptr)
{
    return __strtofx(str, ptr, LDBL_MANT_DIG, LDBL_MIN_EXP - LDBL_MANT_DIG);
}

double atof(const char *str)
{
    return __strtofx(str, NULL, DBL_MANT_DIG, DBL_MIN_EXP - DBL_MANT_DIG);
}

