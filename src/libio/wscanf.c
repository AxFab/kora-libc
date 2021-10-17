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
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <kora/mcrs.h>
#include <bits/libio.h>
#include <wchar.h>

int vfwscanf(FILE *restrict fp, const wchar_t *restrict fmt, va_list ap);
int vswscanf(const wchar_t *restrict ws, const wchar_t *restrict fmt, va_list ap);

/* Read from a string streaming */
// static size_t _swread(FILE *fp, unsigned char *buf, size_t len);
// {
//     return -1;
// }

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

int wscanf(const wchar_t *restrict fmt, ...)
{
    int ret;
    va_list ap;
    va_start(ap, fmt);
    ret = vfwscanf(stdin, fmt, ap);
    va_end(ap);
    return ret;
}

int vwscanf(const wchar_t *restrict fmt, va_list ap)
{
    return vfwscanf(stdin, fmt, ap);
}

int fwscanf(FILE *restrict fp, const wchar_t *restrict fmt, ...)
{
    int ret;
    va_list ap;
    va_start(ap, fmt);
    ret = vfwscanf(fp, fmt, ap);
    va_end(ap);
    return ret;
}

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

int swscanf(const wchar_t *restrict ws, const wchar_t *restrict fmt, ...)
{
    int ret;
    va_list ap;
    va_start(ap, fmt);
    FILE fp;
    __fstr_open_ro(&fp, ws, wcslen(ws));
    ret = vfwscanf(&fp, fmt, ap);
    va_end(ap);
    return ret;
}

int vswscanf(const wchar_t *restrict ws, const wchar_t *restrict fmt, va_list ap)
{
    FILE fp;
    __fstr_open_ro(&fp, ws, wcslen(ws));
    return vfwscanf(&fp, fmt, ap);
}
