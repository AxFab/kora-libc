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
#include <float.h>
#include <wchar.h>
#include <bits/libio.h>


long double __scan_float(FILE *fp, int bits, int emin, int pok);

static long double __wcstox(const wchar_t *ws, wchar_t **ptr, int bits, int emin)
{
    FILE fp;
    __fstr_open_ro(&fp, ws, wcslen(ws));

    wint_t wc = fgetwc_unlocked(&fp);
    while (iswspace(wc))
        wc = fgetwc_unlocked(&fp);

    long double y = __scan_float(&fp, bits, emin, 1);
    if (ptr) {
        size_t cnt = 0; // frcount_unlocked(&f);
        *ptr = (wchar_t *)ws + cnt;
    }
    return y;
}

float wcstof(const wchar_t *restrict ws, wchar_t **restrict ptr)
{
    return __wcstox(ws, ptr, FLT_MANT_DIG, FLT_MIN_EXP - FLT_MANT_DIG);
}

double wcstod(const wchar_t *restrict ws, wchar_t **restrict ptr)
{
    return __wcstox(ws, ptr, DBL_MANT_DIG, DBL_MIN_EXP - DBL_MANT_DIG);
}

long double wcstold(const wchar_t *restrict ws, wchar_t **restrict ptr)
{
    return __wcstox(ws, ptr, LDBL_MANT_DIG, LDBL_MIN_EXP - LDBL_MANT_DIG);
}
