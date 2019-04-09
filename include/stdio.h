#ifndef __STDIO_H
#define __STDIO_H 1

#include <bits/cdefs.h>
#include <stddef.h>
#include <bits/types.h>
#include <bits/libio.h>


typedef __off_t off_t;
typedef __ssize_t ssize_t;
// typedef _G_fpos_t fpos_t;
typedef long fpos_t;


int remove (const char *filename);
int rename (const char *old, const char *new);
int renameat (int oldfd, const char *old, int newfd, const char *new);

FILE *tmpfile (void);
char *tmpnam (char *s);


char *tmpnam_r (char *s);
char *tempnam (const char *dir, const char *pfx);

int fclose (FILE *stream);
int fflush (FILE *stream);
int fflush_unlocked (FILE *stream);
FILE *fopen (const char *restrict filename, const char *restrict modes);


FILE *freopen (const char *restrict filename,
 const char *restrict modes,
 FILE *restrict stream) ;

FILE *fdopen (int fd, const char *modes)  ;
FILE *fmemopen (void *s, size_t len, const char *modes)  ;




FILE *open_memstream (char **bufloc, size_t *sizeloc) ;






void setbuf (FILE *restrict stream, char *restrict buf) ;



int setvbuf (FILE *restrict stream, char *restrict buf, int modes, size_t n)  ;



void setbuffer (FILE *restrict stream, char *restrict buf, size_t size) ;


void setlinebuf (FILE *stream);








int fprintf (FILE *restrict stream,  const char *restrict format, ...);




int printf (const char *restrict format, ...);

int sprintf (char *restrict s, const char *restrict format, ...);





int vfprintf (FILE *restrict s, const char *restrict format,va_list arg);


int vprintf (const char *restrict format, va_list arg);

int vsprintf (char *restrict s, const char *restrict format,


  va_list

 arg);





int snprintf (char *restrict s, size_t maxlen, const char *restrict format, ...);

int vsnprintf (char *restrict s, size_t maxlen,  const char *restrict format,  va_list arg);


int vdprintf (int fd, const char *restrict fmt, va_list arg);
int dprintf (int fd, const char *restrict fmt, ...);



int fscanf (FILE *restrict stream, const char *restrict format, ...) ;




int scanf (const char *restrict format, ...) ;

int sscanf (const char *restrict s,
 const char *restrict format, ...);

int fscanf (FILE *restrict stream, const char *restrict format, ...);
int scanf (const char *restrict format, ...);
int sscanf (const char *restrict s, const char *restrict format, ...);

int vfscanf (FILE *restrict s, const char *restrict format, va_list  arg);





int vscanf (const char *restrict format, va_list arg);


int vsscanf (const char *restrict s, const char *restrict format, va_list arg);



int fgetc (FILE *stream);
int getc (FILE *stream);


int getchar (void);


int getc_unlocked (FILE *stream);
int getchar_unlocked (void);

int fgetc_unlocked (FILE *stream);




int fputc (int c, FILE *stream);
int putc (int c, FILE *stream);


int putchar (int c);

int fputc_unlocked (int c, FILE *stream);


int putc_unlocked (int c, FILE *stream);
int putchar_unlocked (int c);

int getw (FILE *stream);
int putw (int w, FILE *stream);
char *fgets (char *restrict s, int n, FILE *restrict stream) ;


__ssize_t getdelim (char **restrict lineptr, size_t *restrict n, int delimiter,  FILE *restrict stream) ;
__ssize_t  getline (char **restrict lineptr, size_t *restrict n, FILE *restrict stream) ;


int fputs (const char *restrict s, FILE *restrict stream);

int puts (const char *s);
int ungetc (int c, FILE *stream);

size_t fread (void *restrict ptr, size_t size, size_t n, FILE *restrict stream) ;


size_t fwrite (const void *restrict ptr, size_t size,  size_t n, FILE *restrict s);
size_t fread_unlocked (void *restrict ptr, size_t size, size_t n, FILE *restrict stream) ;
size_t fwrite_unlocked (const void *restrict ptr, size_t size,  size_t n, FILE *restrict stream);


int fseek (FILE *stream, long int off, int whence);
long int ftell (FILE *stream);
void rewind (FILE *stream);
int fseeko (FILE *stream, __off_t off, int whence);
__off_t ftello (FILE *stream) ;

int fgetpos (FILE *restrict stream, fpos_t *restrict pos);
int fsetpos (FILE *stream, const fpos_t *pos);


void clearerr (FILE *stream) ;
int feof (FILE *stream);
int ferror (FILE *stream) ;


void clearerr_unlocked (FILE *stream);
int feof_unlocked (FILE *stream);
int ferror_unlocked (FILE *stream);


void perror (const char *s);



// extern int sys_nerr;
// extern const char *const sys_errlist[];



int fileno (FILE *stream)  ;

int fileno_unlocked (FILE *stream)  ;

FILE *popen (const char *command, const char *modes) ;
int pclose (FILE *stream);
char *ctermid (char *s)  ;
void flockfile (FILE *stream) ;
int ftrylockfile (FILE *stream)  ;
void funlockfile (FILE *stream)  ;

#define PATH_MAX 4096
#define EOF (-1)
#define X_OK 1
#define W_OK 2
#define R_OK 4

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

#endif  /* __STDIO_H */
