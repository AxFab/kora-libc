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
#include <bits/crt.h>
#include <kora/mcrs.h>

/* Parse the character base mode for opening file and return binary mode
 * The mode parameter must start by on of this sequence:
 *   r  Open the file for reading. The stream is positioned at the
 *        beginning of the file.
 *   r+ Open the file for reading and writing. The stream is positioned at
 *        the beginning of the file.
 *   w  Truncate file to zero length or create a new file for writing. The
 *        stream is positioned at the beginning of the file.
 *   w+ Open the file for reading and writing. The file is created if
 *        needed, or truncated. The stream is positioned at the beginning
 *        of the file.
 *   a  Open for appending (writing at the end). The file is created if it
 *        doesn't exist. The stream is positioned at the end of file.
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

/* Flush a stream, ignoring lock */
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
    // stream->rbf_.pos_ = NULL;
    // stream->rbf_.base_ = NULL;
    // stream->rbf_.end_ = NULL;
    // stream->wbf_.pos_ = NULL;
    // stream->wbf_.base_ = NULL;
    // stream->wbf_.end_ = NULL;
    return 0;
}


/* Flush a stream */
int fflush(FILE *stream)
{
    int ret;

    if (stream) {
        FLOCK(stream);
        ret = fflush_unlocked(stream);
        FUNLOCK(stream);
        return ret;
    }

    /* TODO for each on the list, */
    errno = ENOSYS;
    return -1;
}

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

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
        int cap = MIN(len, fp->rbf_.end_ - fp->rbf_.pos_);
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


/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/* Stream close functions */
int fclose(FILE *stream)
{
    int ret;
    int perm;

    if (stream == NULL)
        return 0;

    assert(stream->write == _fwrite && stream->read == _fread);

    FLOCK(stream);
    perm = stream->flags_ & F_PERM;
    if (!perm) {
        /* TODO struct _IO_FILE_ are linked, remove fom the list! */
    }

    ret = fflush_unlocked(stream);
    ret |= close(stream->fd_);

    if (stream->rbf_.base_)
        free(stream->rbf_.base_);
    if (stream->wbf_.base_)
        free(stream->wbf_.base_);
    if (!perm) {
        FRMLOCK(stream);
        free(stream);
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

    memset(fp, 0, sizeof(*fp));
    fp->fd_ = fd;
    fp->oflags_ = oflags | _IOLBF;
    fp->read = _fread;
    fp->write = _fwrite;
    fp->seek = _fseek;
    return fp;
}


/* Stream open functions */
FILE *fopen(const char *path, const char *mode)
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


/* Create a stream for a opened file */
FILE *fdopen(int fd, const char *mode)
{
    int ofs;

    /* Get openning flags */
    ofs = oflags(mode);
    if (!ofs)
        return NULL;

    return fvopen(fd, ofs);
}


/* Stream open functions */
FILE *freopen(const char *path, const char *mode, FILE *stream)
{
    FILE *newstm;
    // int oflg = oflags(mode);
    FLOCK(stream);
    fflush_unlocked(stream);

    // if (!path) {
    //     if (oflg & O_CLOEXEC)
    //         fcntl(stream->fd_, F_SETFD, FD_CLOEXEC);
    //     oflg &= ~(O_CREAT | O_EXCL | O_CLOEXEC);
    //     if (fcntl(stream->fd_, F_SETFL, oflg) < 0) {
    //         fclose(stream);
    //         return NULL;
    //     }
    //     FUNLOCK(stream);
    //     return stream;
    // }

    newstm = fopen(path, mode);
    if (!newstm) {
        fclose(stream);
        return NULL;
    }
    if (newstm->fd_ == stream->fd_)
        newstm->fd_ = -1; /* avoid closing in fclose */
    // else if (__dup3(f2->fd, f->fd, oflg & O_CLOEXEC) < 0) {
    //   fclose(newstm);
    //   fclose(stream);
    //   return NULL;
    // }

    stream->flags_ = (stream->flags_ & F_PERM) | newstm->flags_;
    stream->read = newstm->read;
    stream->write = newstm->write;
    stream->seek = newstm->seek;
    // stream->close = newstm->close;
    fclose(newstm);
    FUNLOCK(stream);
    return stream;
}


/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/* Binary stream input */
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    size_t items = 0;
    FLOCK(stream);
    for (items = 0; items < nmemb; ++items) {
        if (stream->read(stream, ptr, size) == EOF)
            break;
        ptr = ((char *)ptr) + size;
    }

    FUNLOCK(stream);
    return items;
}


/* Binary stream output */
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    size_t items = 0;
    FLOCK(stream);
    for (items = 0; items < nmemb; ++items) {
        if (stream->write(stream, ptr, size) == EOF)
            break;
        ptr = ((char *)ptr) + size;
    }

    FUNLOCK(stream);
    return items;
}


/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/* Reposition a stream */
int fseek(FILE *stream, long offset, int whence)
{
    int ret;
    FLOCK(stream);

    /* Flush write buffer, and report error on failure. */

    ret = stream->seek(stream, offset, whence);
    if (ret >= 0) {
        stream->fpos_ = ret;
        if (stream->rbf_.base_)
            free(stream->rbf_.base_);
        if (stream->wbf_.base_)
            free(stream->wbf_.base_);
    }
    FUNLOCK(stream);
    return ret;
}

/* Reposition a stream */
long ftell(FILE *stream)
{
    size_t pos = stream->fpos_;

    /* Adjust for data in buffer. */
    if (stream->rbf_.base_)
        pos += stream->rbf_.end_ -stream->rbf_.pos_;
    if (stream->wbf_.base_)
        pos += stream->wbf_.end_ -stream->wbf_.pos_;

    // if (pos > LONG_MAX) {
    //     errno = EOVERFLOW;
    //     return -1;
    // }
    return (long)pos;
}

/* Reposition a stream */
void rewind(FILE *stream)
{
    fflush(stream);
    fseek(stream, 0, SEEK_SET);
}

/* Reposition a stream */
int fgetpos(FILE *stream, fpos_t *pos)
{
    *pos = (fpos_t)stream->fpos_;
    return 0;
}

/* Reposition a stream */
int fsetpos(FILE *stream, fpos_t *pos)
{
    if (fseek(stream, (long)*pos, SEEK_SET) >= 0)
        return 0;
    return -1;
}


/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/* Check and reset stream status */
void clearerr(FILE *stream)
{
    stream->flags_ &= !(FF_EOF | FF_ERR);
}

/* Check and reset stream status */
int feof(FILE *stream)
{
    return stream->flags_ & FF_EOF;
}

/* Check and reset stream status */
int ferror(FILE *stream)
{
    return stream->flags_ & FF_ERR;
}

/* Check and reset stream status */
int fileno(FILE *stream)
{
    return stream->fd_;
}



/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/* Stream buffering operations */
void setbuf(FILE *stream, char *buf)
{

}

/* Stream buffering operations */
int setvbuf(FILE *stream, char *buf, int mode, size_t size)
{
    return -1;
}


/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */


int fgetc_unlocked(FILE *stream)
{
    int c = 0;
    if (stream->read(stream, (char *)&c, 1) == EOF)
        return EOF;

    return c;
}

char *fgets_unlocked(char *s, int size, FILE *stream)
{
    int c;
    unsigned char *ps = (unsigned char *)s;

    while (--size) {
        c = fgetc_unlocked(stream);
        if (c == EOF) {
            if (errno)
                return NULL;
            break;
        }

        *ps = (unsigned char)c;
        if (c == '\n') {
            ++ps;
            break;
        }

        ++ps;
    }

    *ps = '\0';
    return ((void *)s == (void *)ps) ? NULL : s;
}

/* Read a character from STREAM. */
int fgetc(FILE *stream)
{
    int c;
    FLOCK(stream);
    c = fgetc_unlocked(stream);
    FUNLOCK(stream);
    return c;
}

/* Read a character from STREAM. */
int getc(FILE *stream)
{
    return fgetc(stream);
}

/* Get a newline-terminated string from stdin, removing the newline.
   DO NOT USE THIS FUNCTION!!  There is no limit on how much it will read. */
char *gets(char *s);


/* Get a newline-terminated string of finite length from STREAM. */
char *fgets(char *s, int n, FILE *stream)
{
    FLOCK(stream);
    char *r = fgets_unlocked(s, n, stream);
    FUNLOCK(stream);
    return r;
}

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/* Write a character to STREAM. */
int fputc(int c, FILE *stream)
{
    size_t ret = fwrite(&c, 1, 1, stream);
    return ((int)ret == 1) ? (unsigned char)c : EOF;
}

/* Write a character to STREAM. */
int putc(int c, FILE *stream)
{
    return fputc(c, stream);
}

/* Write a string, followed by a newline, to stdout. */
int puts(const char *s)
{
    int lg = strlen(s);
    size_t ret = fwrite(s, lg, 1, stdout);
    if ((int)ret == lg) {
        ret = fwrite("\n", 1, 1, stdout);
        return lg + 1;
    }
    return EOF;
}


/* Write a string to STREAM. */
int fputs(const char *s, FILE *stream)
{
    int lg = strlen(s);
    size_t ret = fwrite(s, lg, 1, stream);
    return ((int)ret == lg) ? lg : EOF;
}

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/* Read a character from stdin. */
int getchar(void)
{
    return fgetc(stdin);
}

/* Write a character to stdout. */
int putchar(int c)
{
    return fputc(c, stdout);
}

/* Push a character back onto the input buffer of STREAM. */
int ungetc(int c, FILE *stream);

