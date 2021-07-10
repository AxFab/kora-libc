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
#include <string.h>
#include <errno.h>
#include <stdarg.h>
#include <kora/mcrs.h>
#include <bits/libio.h>
#include <malloc.h>
#include <limits.h>
#include <stdint.h>

int fputws(const wchar_t *restrict buf, FILE *restrict fp);
int vfwprintf(FILE *restrict f, const wchar_t *restrict fmt, va_list ap);
int vswprintf(wchar_t *restrict s, size_t n, const wchar_t *restrict fmt, va_list ap);


/* Read from a string streaming */
// static size_t _swwrite(FILE *fp, unsigned char *buf, size_t len)
// {
//     return -1;
// }

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

int wprintf(const wchar_t *restrict fmt, ...)
{
    int ret;
    va_list ap;
    va_start(ap, fmt);
    ret = vfwprintf(stdout, fmt, ap);
    va_end(ap);
    return ret;
}

int vwprintf(const wchar_t *restrict fmt, va_list ap)
{
    return vfwprintf(stdout, fmt, ap);
}

int fwprintf(FILE *restrict f, const wchar_t *restrict fmt, ...)
{
    int ret;
    va_list ap;
    va_start(ap, fmt);
    ret = vfwprintf(f, fmt, ap);
    va_end(ap);
    return ret;
}

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

int swprintf(wchar_t *restrict ws, size_t wn, const wchar_t *restrict fmt, ...)
{
    int ret;
    va_list ap;
    FILE fp;
    __fstr_open_rw(&fp, ws, wn);
    va_start(ap, fmt);
    ret = vswprintf(ws, wn, fmt, ap);
    fputws(L'\0', &fp);
    va_end(ap);
    return ret;
}

int vswprintf(wchar_t *restrict ws, size_t wn, const wchar_t *restrict fmt, va_list ap)
{
    int ret;
    FILE fp;

    if (!wn)
        return -1;
    else if (wn > INT_MAX) {
        errno = EOVERFLOW;
        return -1;
    }
    __fstr_open_rw(&fp, ws, wn);
    ret = vswprintf(ws, wn, fmt, ap);
    fputws(L'\0', &fp);
    return ret;
}
