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
#ifndef __STDIO_H
#define __STDIO_H 1

#include <bits/cdefs.h>

#include <stddef.h>
#include <bits/types.h>
#include <bits/libio.h>

__STDC_GUARD

typedef __off_t off_t;
typedef __ssize_t ssize_t;
// typedef _G_fpos_t fpos_t;
typedef long fpos_t;


#define X_OK 1
#define W_OK 2
#define R_OK 4


#define FILENAME_MAX 4096
#define FOPEN_MAX 1000
#define TMP_MAX 10000
#define L_tmpnam 20

#define _IO_stdin_ stdin
#define _IO_stdout_ stdout
#define _IO_stderr_ stderr


FILE *fopen(const char *restrict filename, const char *restrict modes);
FILE *freopen(const char *restrict filename, const char *restrict modes, FILE *restrict stream);
int fclose(FILE *stream);

int remove(const char *filename);
int rename(const char *oldpath, const char *newpath);



int feof(FILE *stream);
int ferror(FILE *stream);
int fflush(FILE *stream);
void clearerr(FILE *stream);

int fseek(FILE *stream, long int off, int whence);
long int ftell(FILE *stream);
void rewind(FILE *stream);

int fgetpos(FILE *restrict stream, fpos_t *restrict pos);
int fsetpos(FILE *stream, const fpos_t *pos);


size_t fread(void *restrict ptr, size_t size, size_t n, FILE *restrict stream);
size_t fwrite(const void *restrict ptr, size_t size,  size_t n, FILE *restrict s);


int fgetc(FILE *stream);
int getc(FILE *stream);
int getchar(void);
int ungetc(int c, FILE *stream);


int fputc(int c, FILE *stream);
int putc(int c, FILE *stream);
int putchar(int c);

char *gets(char *restrict s);
char *fgets(char *restrict s, int n, FILE *restrict stream);
int fputs(const char *restrict s, FILE *restrict stream);
int puts(const char *s);


int printf(const char *restrict format, ...);
int fprintf(FILE *restrict stream,  const char *restrict format, ...);
int sprintf(char *restrict s, const char *restrict format, ...);
int snprintf(char *restrict s, size_t maxlen, const char *restrict format, ...);

int vprintf(const char *restrict format, va_list arg);
int vfprintf(FILE *restrict s, const char *restrict format, va_list arg);
int vsprintf(char *restrict s, const char *restrict format, va_list arg);
int vsnprintf(char *restrict s, size_t maxlen,  const char *restrict format,  va_list arg);

int scanf(const char *restrict format, ...);
int fscanf(FILE *restrict stream, const char *restrict format, ...);
int sscanf(const char *restrict s, const char *restrict format, ...);

int vscanf(const char *restrict format, va_list arg);
int vfscanf(FILE *restrict s, const char *restrict format, va_list  arg);
int vsscanf(const char *restrict s, const char *restrict format, va_list arg);



void perror(const char *s);



int setvbuf(FILE *restrict stream, char *restrict buf, int modes, size_t n);
void setbuf(FILE *restrict stream, char *restrict buf);

char *tmpnam(char *s);
FILE *tmpfile(void);



// 000000000000000000000000000000000000000000000000000000000000000000000000000

#if defined __POSIX || defined __UNIX

FILE *fmemopen(void *s, size_t len, const char *modes);
FILE *open_memstream(char **bufloc, size_t *sizeloc);
FILE *fdopen(int fd, const char *modes);

FILE *popen(const char *command, const char *modes);
int pclose(FILE *stream);

int fileno(FILE *stream);

int fseeko(FILE *stream, __off_t off, int whence);
__off_t ftello(FILE *stream);

int dprintf(int fd, const char *restrict fmt, ...);
int vdprintf(int fd, const char *restrict fmt, va_list arg);

void flockfile(FILE *stream);
int ftrylockfile(FILE *stream);
void funlockfile(FILE *stream);

int getc_unlocked(FILE *stream);
int getchar_unlocked(void);
int putc_unlocked(int c, FILE *stream);
int putchar_unlocked(int c);

__ssize_t getdelim(char **restrict lineptr, size_t *restrict n, int delimiter,  FILE *restrict stream);
__ssize_t  getline(char **restrict lineptr, size_t *restrict n, FILE *restrict stream);
int renameat(int oldfd, const char *oldpath, int newfd, const char *newpath);
char *ctermid(char *s);

#define L_ctermid 20

#endif



#if defined __UNIX

#define P_tmpdir "/tmp"
char *tempnam(const char *dir, const char *pfx);

#endif


#if defined __BSD || defined __GNU

#define L_cuserid 20
char *cuserid(char *s);

void setlinebuf(FILE *stream);
void setbuffer(FILE *restrict stream, char *restrict buf, size_t size);

#endif



#if defined __GNU

char *fgets_unlocked(char *str, int, FILE *stream);
int fputs_unlocked(const char *str, FILE *stream);

#endif



#if defined __LARGEFILE64 || defined __GNU
# define tmpfile64 tmpfile
# define fopen64 fopen
# define freopen64 freopen
# define fseeko64 fseeko
# define ftello64 ftello
# define fgetpos64 fgetpos
# define fsetpos64 fsetpos
typedef __fpos64_t fpos64_t;
typedef __off64_t off64_t;
#endif


char *tmpnam_r(char *s);

int getw(FILE *stream);
int putw(int w, FILE *stream);

__STDC_END

#endif  /* __STDIO_H */
