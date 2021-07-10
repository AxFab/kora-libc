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
#include <assert.h>
#include <string.h>
#include <errno.h>
#include <bits/libio.h>
#include "stdc.h"
#include <kora/mcrs.h>

#ifndef __NO_SCALL
FILE __stdio[3];
FILE *stdin = &__stdio[0];
FILE *stdout = &__stdio[1];
FILE *stderr = &__stdio[2];
#endif

static int _fread(FILE *fp, char *buf, size_t len)
{
    /* If unbuffered */
    if (fp->oflags_ & _IONBF)
        return read(fp->fd_, buf, len);

    if (fp->rbf_.base_ == NULL) {
        fp->rbf_.base_ = malloc(512); // TODO BUFSZ
        fp->rbf_.pos_ = fp->rbf_.base_;
        fp->rbf_.end_ = fp->rbf_.pos_;
    }

    int bytes = 0;
    while (len > 0) {
        if (fp->rbf_.end_ == fp->rbf_.pos_) {
            int rd = read(fp->fd_, fp->rbf_.base_, 512);
            if (rd <= 0) {
                free(fp->rbf_.base_);
                fp->rbf_.base_ = NULL;
                return bytes == 0 ? rd : bytes;
            }
            fp->rbf_.end_ = fp->rbf_.pos_ + rd;
        }
        int cap = MIN(len, (size_t)(fp->rbf_.end_ - fp->rbf_.pos_));
        if (cap != 0)
            memcpy(buf, fp->rbf_.pos_, cap);
        buf += cap;
        len -= cap;
        bytes += cap;
        fp->rbf_.pos_ += cap;
    }

    return bytes;
}

static int _fwrite(FILE *fp, const char *buf, size_t len)
{
    /* If unbuffered */
    if (fp->oflags_ & _IONBF)
        return write(fp->fd_, buf, len);
    /* TODO */
    return write(fp->fd_, buf, len);
}

static int _fseek(FILE *fp, long pos, int dir)
{
    return lseek(fp->fd_, pos, dir);
}

static void __fvopen(FILE *fp, int fd, int oflags)
{
    memset(fp, 0, sizeof(*fp));
    fp->fd_ = fd;
    fp->oflags_ = oflags | _IOLBF;
    fp->read = _fread;
    fp->write = _fwrite;
    fp->seek = _fseek;
}

void __stdio_init()
{
    __fvopen(stdin, 0, O_RDONLY);
    __fvopen(stdout, 1, O_WRONLY);
    __fvopen(stderr, 2, O_WRONLY);
}

void __stdio_fini()
{
}

/* Parse the character base mode for opening file and return binary mode
 * The mode parameter must start by on of this sequence:
 *   r  Open the file for reading. The fp is positioned at the
 *        beginning of the file.
 *   r+ Open the file for reading and writing. The fp is positioned at
 *        the beginning of the file.
 *   w  Truncate file to zero length or create a new file for writing. The
 *        fp is positioned at the beginning of the file.
 *   w+ Open the file for reading and writing. The file is created if
 *        needed, or truncated. The fp is positioned at the beginning
 *        of the file.
 *   a  Open for appending (writing at the end). The file is created if it
 *        doesn't exist. The fp is positioned at the end of file.
 *   a+  Open for reading and appending (writing at the ent). The initial
 *        file position is at the beginning, but output is always append
 *        to the end.
 *
 * The mode can be completed by this extensions:
 *   b   (mingw32) Try to optimize for binary file
 *   x   (glibc) Open the file exclusively (like O_EXEC)
 *   e   (glibc) Close the file on exec
 *   m   (glibc) Try to use mmap
 *   F   (uClibc) Open a a large file
 *
 * Note: on this implementation repeated or unknown extensions don't cause any
 *       errors and '+' is consider as and extensions rather than a mode suffix.
 */
int oflags(const char *mode)
{
    int oflags = 0;
    if (*mode == 'r')
        oflags |= O_RDONLY;
    else if (*mode == 'w')
        oflags |= O_WRONLY | O_CREAT | O_TRUNC;
    else if (*mode == 'a')
        oflags |= O_WRONLY | O_CREAT | O_APPEND;
    else {
        errno = EINVAL;
        return -1;
    }

    ++mode;
    while (*mode != '\0' && *mode != ',') {
        switch (*mode) {
        case 'r':
        case 'w':
        case 'a':
            errno = EINVAL;
            return -1;

        case '+':
            oflags &= ~(O_RDONLY | O_WRONLY);
            oflags |= O_RDWR;
            break;

        case 'x':
            oflags |= O_EXCL;
            break;
            /*
            case 'b': oflags |= O_BINARY; break;
            case 'e': oflags |= O_CLOEXEC; break;
            case 'm': oflags |= O_MEMORYMAP; break;
            case 'F': oflags |= O_LARGEFILE; break; */
        }
        ++mode;
    }

    errno = 0;
    return oflags;
}


/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/* Flush a fp, ignoring lock */
int fflush_unlocked(FILE *fp)
{
    /* If reading, sync position */
    if (fp->rbf_.pos_ < fp->rbf_.end_)
        fp->seek(fp, fp->rbf_.pos_ - fp->rbf_.end_, SEEK_CUR);

    /* If writing, flush output */
    if (fp->wbf_.pos_ > fp->wbf_.base_) {
        if (fp->write(fp, 0, 0) < 0)
            return EOF;
    }

    /* Clear read and write modes */
    // fp->rbf_.pos_ = NULL;
    // fp->rbf_.base_ = NULL;
    // fp->rbf_.end_ = NULL;
    // fp->wbf_.pos_ = NULL;
    // fp->wbf_.base_ = NULL;
    // fp->wbf_.end_ = NULL;
    return 0;
}


/* Flush a fp */
int _PRT(fflush)(FILE *fp)
{
    int ret;

    if (fp) {
        FLOCK(fp);
        ret = fflush_unlocked(fp);
        FUNLOCK(fp);
        return ret;
    }

    /* TODO for each on the list, */
    errno = ENOSYS;
    return -1;
}

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/* Stream close functions */
int _PRT(fclose)(FILE *fp)
{
    int ret;
    int perm;

    if (fp == NULL)
        return 0;

    assert(fp->write == _fwrite && fp->read == _fread);

    FLOCK(fp);
    perm = fp->flags_ & F_PERM;
    if (!perm) {
        /* TODO struct _IO_FILE_ are linked, remove fom the list! */
    }

    ret = fflush_unlocked(fp);
    ret |= close(fp->fd_);

    if (fp->rbf_.base_)
        free(fp->rbf_.base_);
    if (fp->wbf_.base_)
        free(fp->wbf_.base_);
    if (!perm) {
        FRMLOCK(fp);
        free(fp);
    }

    return ret;
}

/* Allocate a new FILE structure form an open file descriptor. */
FILE *fvopen(int fd, int oflags)
{
    FILE *fp;
    if (fd < 0) {
        errno = EBADF;
        return NULL;
    }

    if (oflags < 0) {
        errno = EINVAL;
        return NULL;
    }

    fp = (FILE *)malloc(sizeof(*fp));
    if (!fp)
        return NULL;

    __fvopen(fp, fd, oflags | _IOLBF);
    return fp;
}


/* Stream open functions */
FILE *_PRT(fopen)(const char *path, const char *mode)
{
    int md;
    int fd;
    FILE *fp;

    md = oflags(mode);
    if (md < 0 || path == NULL)
        return NULL;

    fd = open(path, md);
    if (fd < 0)
        return NULL;

    fp = fvopen(fd, md);
    if (fp == NULL) {
        close(fd);
        fp = NULL;
    }

    return fp;
}


/* Create a fp for a opened file */
FILE *_PRT(fdopen)(int fd, const char *mode)
{
    int ofs;

    /* Get openning flags */
    ofs = oflags(mode);
    if (!ofs)
        return NULL;

    return fvopen(fd, ofs);
}


/* Stream open functions */
FILE *freopen(const char *path, const char *mode, FILE *fp)
{
    FILE *newstm;
    // int oflg = oflags(mode);
    FLOCK(fp);
    fflush_unlocked(fp);

    // if (!path) {
    //     if (oflg & O_CLOEXEC)
    //         fcntl(fp->fd_, F_SETFD, FD_CLOEXEC);
    //     oflg &= ~(O_CREAT | O_EXCL | O_CLOEXEC);
    //     if (fcntl(fp->fd_, F_SETFL, oflg) < 0) {
    //         fclose(fp);
    //         return NULL;
    //     }
    //     FUNLOCK(fp);
    //     return fp;
    // }

    newstm = fopen(path, mode);
    if (!newstm) {
        fclose(fp);
        return NULL;
    }
    if (newstm->fd_ == fp->fd_)
        newstm->fd_ = -1; /* avoid closing in fclose */
    // else if (__dup3(f2->fd, f->fd, oflg & O_CLOEXEC) < 0) {
    //   fclose(newstm);
    //   fclose(fp);
    //   return NULL;
    // }

    fp->flags_ = (fp->flags_ & F_PERM) | newstm->flags_;
    fp->read = newstm->read;
    fp->write = newstm->write;
    fp->seek = newstm->seek;
    // fp->close = newstm->close;
    fclose(newstm);
    FUNLOCK(fp);
    return fp;
}


/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

size_t fread_unlocked(void *ptr, size_t size, size_t nmemb, FILE *fp)
{
    size_t items = 0;
    for (items = 0; items < nmemb; ++items) {
        if (fp->read(fp, ptr, size) == EOF)
            break;
        ptr = ((char *)ptr) + size;
    }

    return items;
}

size_t fwrite_unlocked(const void *ptr, size_t size, size_t nmemb, FILE *fp)
{
    size_t items = 0;
    for (items = 0; items < nmemb; ++items) {
        if (fp->write(fp, ptr, size) == EOF)
            break;
        ptr = ((char *)ptr) + size;
    }
    return items;
}

int ungetc_unlocked(int c, FILE *fp)
{
    if (fp->rbf_.base_ && fp->rbf_.pos_ > fp->rbf_.base_) {
        if (fp->rbf_.pos_[-1] == c) {
            fp->rbf_.pos_--;
            return c;
        }
    }
    return -1;
}

/* Binary fp input */
size_t _PRT(fread)(void *ptr, size_t size, size_t nmemb, FILE *fp)
{
    FLOCK(fp);
    size_t items = fread_unlocked(ptr, size, nmemb, fp);
    FUNLOCK(fp);
    return items;
}


/* Binary fp output */
size_t _PRT(fwrite)(const void *ptr, size_t size, size_t nmemb, FILE *fp)
{
    FLOCK(fp);
    size_t items = fwrite_unlocked(ptr, size, nmemb, fp);
    FUNLOCK(fp);
    return items;
}

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/* Reposition a fp */
int _PRT(fseek)(FILE *fp, long offset, int whence)
{
    int ret;
    FLOCK(fp);

    /* Flush write buffer, and report error on failure. */

    ret = fp->seek(fp, offset, whence);
    if (ret >= 0) {
        fp->fpos_ = ret;
        if (fp->rbf_.base_)
            free(fp->rbf_.base_);
        if (fp->wbf_.base_)
            free(fp->wbf_.base_);
    }
    FUNLOCK(fp);
    return ret;
}

/* Reposition a fp */
long _PRT(ftell)(FILE *fp)
{
    size_t pos = fp->fpos_;

    /* Adjust for data in buffer. */
    if (fp->rbf_.base_)
        pos += fp->rbf_.end_ - fp->rbf_.pos_;
    if (fp->wbf_.base_)
        pos += fp->wbf_.end_ - fp->wbf_.pos_;

    // if (pos > LONG_MAX) {
    //     errno = EOVERFLOW;
    //     return -1;
    // }
    return (long)pos;
}

/* Reposition a fp */
void rewind(FILE *fp)
{
    fflush(fp);
    fseek(fp, 0, SEEK_SET);
}

/* Reposition a fp */
int fgetpos(FILE *fp, fpos_t *pos)
{
    *pos = (fpos_t)fp->fpos_;
    return 0;
}

/* Reposition a fp */
int fsetpos(FILE *fp, fpos_t *pos)
{
    if (fseek(fp, (long)*pos, SEEK_SET) >= 0)
        return 0;
    return -1;
}


/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/* Check and reset fp status */
void clearerr(FILE *fp)
{
    fp->flags_ &= !(F_EOF | F_ERR);
}

/* Check and reset fp status */
int feof(FILE *fp)
{
    return fp->flags_ & F_EOF;
}

/* Check and reset fp status */
int ferror(FILE *fp)
{
    return fp->flags_ & F_ERR;
}

/* Check and reset fp status */
int fileno(FILE *fp)
{
    return fp->fd_;
}

int fwide(FILE *fp, int mode)
{
    if (fp->mode == 0)
        fp->mode = mode;
    return fp->mode;
}

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */


/* Stream buffering operations */
int _PRT(setvbuf)(FILE *fp, char *buf, int mode, size_t size)
{
    fp->lbuf_ = EOF;
    if (mode == _IONBF) {
        fp->rbf_.base_ = NULL;
        fp->rbf_.pos_ = NULL;
        fp->rbf_.end_ = NULL;
    } else if (mode == _IOFBF || mode == _IOLBF) {
        fp->rbf_.base_ = buf;
        fp->rbf_.pos_ = fp->rbf_.base_;
        fp->rbf_.end_ = fp->rbf_.base_ + size;
        if (mode == _IOLBF)
            fp->lbuf_ = '\n';
    } else
        return -1;
    return 0;
}

/* Stream buffering operations */
void _PRT(setbuf)(FILE *restrict fp, char *restrict buf)
{
    setvbuf(fp, buf, buf ? _IOFBF : _IONBF, BUFSIZ);
}

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/* Push a character back onto the input buffer of STREAM. */
int ungetc(int c, FILE *fp);

