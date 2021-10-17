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


/* All of those methods are bind over vfscanf
  which is implemented in another file. */
int vfscanf(FILE *f, const char *format, va_list ap);

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/* Read and parse standard input */
int scanf(const char *format, ...)
{
    int ret;
    va_list ap;
    va_start(ap, format);
    ret = vfscanf(stdin, format, ap);
    va_end(ap);
    return ret;
}


/* Read and parse standard input */
int vscanf(const char *format, va_list ap)
{
    return vfscanf(stdin, format, ap);
}


/* Read and parse an open file */
int fscanf(FILE *f, const char *format, ...)
{
    int ret;
    va_list ap;
    va_start(ap, format);
    ret = vfscanf(f, format, ap);
    va_end(ap);
    return ret;
}

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/* Read and parse a string */
int sscanf(const char *str, const char *format, ...)
{
    int ret;
    va_list ap;
    FILE fp;
    __fstr_open_ro(&fp, str, strlen(str));
    va_start(ap, format);
    ret = vfscanf(&fp, format, ap);
    va_end(ap);
    return ret;
}


/* Read and parse a string */
int vsscanf(const char *str, const char *format, va_list ap)
{
    FILE fp;
    __fstr_open_ro(&fp, str, strlen(str));
    return vfscanf(&fp, format, ap);
}
