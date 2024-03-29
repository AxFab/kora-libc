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
#include <bits/libio.h>
#include <kora/mcrs.h>
#include <string.h>

/* Read from a string streaming */
static int __fstr_read(FILE *fp, char *buf, size_t length)
{
    size_t lg = MIN(length, (size_t)(fp->rbf_.end_ - fp->rbf_.pos_));
    memcpy(buf, fp->rbf_.pos_, lg);
    fp->rbf_.pos_ += lg;
    return (length > lg) ? EOF : (int)lg;
}

/* Write on a string streaming */
static int __fstr_write(FILE *fp, const char *buf, size_t length)
{
    size_t lg = MIN(length, (size_t)(fp->wbf_.end_ - fp->wbf_.pos_));
    if (lg == 0)
        return EOF;
    memcpy(fp->wbf_.pos_, buf, lg);
    fp->wbf_.pos_ += lg;
    fp->count_ += lg;
    return (int)lg;
}

/* Initialize a file structure from a string */
void __fstr_open_rw(FILE *fp, void *buf, int len)
{
    memset(fp, 0, sizeof(*fp));
    fp->lbuf_ = EOF;
    fp->write = __fstr_write;
    fp->read = __fstr_read;
    fp->lock_ = -1;
    fp->wbf_.base_ = (char *)buf;
    fp->wbf_.pos_ = (char *)buf;
    fp->wbf_.end_ = (char *)buf + len;
    fp->rbf_.base_ = (char *)buf;
    fp->rbf_.pos_ = (char *)buf;
    fp->rbf_.end_ = (char *)buf + len;
}

/* Initialize a file structure from a string */
void __fstr_open_ro(FILE *fp, const void *buf, int len)
{
    memset(fp, 0, sizeof(*fp));
    fp->lbuf_ = EOF;
    fp->write = NULL;
    fp->read = __fstr_read;
    fp->lock_ = -1;
    fp->rbf_.base_ = (char *)buf;
    fp->rbf_.pos_ = (char *)buf;
    fp->rbf_.end_ = (char *)buf + len;
}
