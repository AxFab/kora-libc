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
#include <math.h>
#include <float.h>
#include <ctype.h>
#include <string.h>


static long double _strtofdx(const char *s, char **p, int sign, int bits, int emin)
{
    /* Ignore leading zeros */
    while (*s == '0')
        ++s;

    return 0.0;
}

static long double _strtofhx(const char *s, char **p, int sign, int bits, int emin)
{
    return 0.0;
}

static long double _strtofx(const char *s, char **p, int bits, int emin)
{
    int sign = 1;
    while (isspace(*s))
        ++s;

    if (*s == '+')
        ++s;
    else if (*s == '-') {
        sign = -1;
        ++s;
    }

    if (strnicmp(s, "infinity", 8) == 0) {
        if (p)
            *p = (char*)(s + 8);
        return sign * INFINITY;
    } else if (strnicmp(s, "inf", 3) == 0) {
        if (p)
            *p = (char *)(s + 3);
        return sign * INFINITY;
    } else if (strnicmp(s, "nan", 3) == 0) {
        if (p)
            *p = (char *)(s + 3);
        return NAN;
    }

    if (strnicmp(s, "0x", 2) == 0)
        return _strtofhx(s + 2, p, sign, bits, emin);
    return _strtofdx(s + 2, p, sign, bits, emin);
}

float strtof(const char *restrict s, char **restrict p)
{
    return _strtofx(s, p, FLT_MANT_DIG, FLT_MIN_EXP - FLT_MANT_DIG);
}

double strtod(const char *restrict s, char **restrict p)
{
    return _strtofx(s, p, DBL_MANT_DIG, DBL_MIN_EXP - DBL_MANT_DIG);
}

long double strtold(const char *restrict s, char **restrict p)
{
    return _strtofx(s, p, LDBL_MANT_DIG, LDBL_MIN_EXP - LDBL_MANT_DIG);
}

