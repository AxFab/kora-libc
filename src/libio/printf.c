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
#include <stdarg.h>
#include <kora/mcrs.h>
#include <bits/libio.h>
#include <malloc.h>
#include <limits.h>
#include <stdint.h>

int fputc(int c, FILE *stream);

/* All of those methods are bind over vfprintf
 * which is implemented in another file.
 */
int vfprintf(FILE *fp, const char *str, va_list ap);
int _PRT(vfprintf)(FILE *fp, const char *str, va_list ap);
int write(int, const char *, size_t);

/* Write on a string streaming */
static int _dwrite(FILE *fp, const char *buf, size_t length)
{
    length = write(fp->fd_, buf, length);
    fp->count_ += length;
    return length;
}


/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/* Write formated string on standard output */
int printf(const char *format, ...)
{
    int ret;
    va_list ap;
    va_start(ap, format);
    ret = vfprintf(stdout, format, ap);
    va_end(ap);
    return ret;
}

/* Write formated string on standard output */
int vprintf(const char *format, va_list ap)
{
    return vfprintf(stdout, format, ap);
}

/* Write formated string on an opened file */
int fprintf(FILE *fp, const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    int ret = vfprintf(fp, format, ap);
    va_end(ap);
    return ret;
}


/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/* Write formated string from a file descriptor */
int vdprintf(int fd, const char *format, va_list ap)
{
    FILE fp;

    fp.fd_ = fd;
    fp.lbuf_ = EOF;
    fp.write = _dwrite;
    fp.lock_ = -1;

    return _PRT(vfprintf)(&fp, format, ap);
}

/* Write formated string from a file descriptor */
int dprintf(int fd, const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    int ret = vdprintf(fd, format, ap);
    va_end(ap);
    return ret;
}

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/* Write formated string from a string */
int vsnprintf(char *str, size_t lg, const char *format, va_list ap)
{
    char b;
    int res;
    FILE fp;
    __fstr_open_rw(&fp, str, lg);

    if (lg - 1 > INT_MAX - 1) {
        errno = EOVERFLOW;
        return -1;
    } else if (!lg) {
        fp.wbf_.pos_ = &b;
        fp.wbf_.end_ = fp.wbf_.pos_++;
    } else if (fp.wbf_.end_ < fp.wbf_.pos_)
        fp.wbf_.end_ = (char *)SIZE_MAX;

    res = _PRT(vfprintf)(&fp, format, ap);
    fputc('\0', &fp);
    return res;
}

/* Write formated string from a string */
int sprintf(char *str, const char *format, ...)
{
    int res;
    va_list ap;
    va_start(ap, format);
    res = vsnprintf(str, INT_MAX, format, ap);
    va_end(ap);
    return res;
}

/* Write formated string from a string */
int snprintf(char *str, size_t lg, const char *format, ...)
{
    int ret;
    va_list ap;
    va_start(ap, format);
    ret = vsnprintf(str, lg, format, ap);
    va_end(ap);
    return ret;
}

/* Write formated string from a string */
int vsprintf(char *str, const char *format, va_list ap)
{
    return vsnprintf(str, INT_MAX, format, ap);
}

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/* Write formated string from an allocated string */
int vasprintf(char **s, const char *format, va_list ap)
{
    int l;
    va_list ap2;
    va_copy(ap2, ap);
    l = vfprintf(NULL, format, ap);
    va_end(ap2);

    if (l < 0 || !(*s = malloc(l + 1)))
        return -1;

    return vsnprintf(*s, l + 1, format, ap);
}

/* Write formated string from an allocated string */
int asprintf(char **str, const char *format, ...)
{
    int ret;
    va_list ap;
    va_start(ap, format);
    ret = vasprintf(NULL, format, ap);
    va_end(ap);
    return ret;
}
