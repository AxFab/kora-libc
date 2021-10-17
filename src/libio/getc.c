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
#include <string.h>
#include <ctype.h>
#include <errno.h>

int fgetc_unlocked(FILE *fp)
{
    int c = 0;
    if (fread_unlocked((char *)&c, 1, 1, fp) == 0)
        return EOF;
    return c;
}

int fputc_unlocked(int c, FILE *fp)
{
    size_t ret = fwrite_unlocked(&c, 1, 1, fp);
    return ((int)ret == 1) ? (unsigned char)c : EOF;
}

char *fgets_unlocked(char *restrict str, int len, FILE *restrict fp)
{
    int c;
    unsigned char *ps = (unsigned char *)str;
    while (--len) {
        c = fgetc_unlocked(fp);
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
    return ((void *)str == (void *)ps) ? NULL : str;
}

int fputs_unlocked(const char *restrict str, FILE *restrict fp)
{
    int lg = strlen(str);
    size_t ret = fwrite_unlocked(str, lg, 1, fp);
    return ((int)ret == lg) ? lg : EOF;
}

char *gets(char *restrict s)
{
    FLOCK(stdin);
    int c, i = 0;
    while ((c = fgetc_unlocked(stdin)) != EOF && c != '\n')
        s[i++] = c;
    s[i] = 0;
    if (c != '\n' && (!feof(stdin) || !i))
        s = 0;
    FUNLOCK(stdin);
    return s;
}

/* Write a string, followed by a newline, to stdout. */
int puts(const char *s)
{
    FLOCK(stdout);
    int lg = strlen(s);
    size_t ret = fwrite_unlocked(s, lg, 1, stdout);
    if ((int)ret == lg) {
        ret = fwrite_unlocked("\n", 1, 1, stdout);
        FUNLOCK(stdout);
        return lg + 1;
    }
    FUNLOCK(stdout);
    return EOF;
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

int getc_unlocked(FILE *fp)
{
    return fgetc_unlocked(fp);
}

int getchar_unlocked(void)
{
    return fgetc_unlocked(stdin);
}

int putc_unlocked(int c, FILE *fp)
{
    return fputc_unlocked(c, fp);
}

int putchar_unlocked(int c)
{
    return fputc_unlocked(c, stdout);
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

int fgetc(FILE *fp)
{
    FLOCK(fp);
    int c = fgetc_unlocked(fp);
    FUNLOCK(fp);
    return c;
}

int getc(FILE *fp)
{
    return fgetc(fp);
}

int getchar(void)
{
    return fgetc(stdin);
}

int fputc(int c, FILE *fp)
{
    FLOCK(fp);
    c = fputc_unlocked(c, fp);
    FUNLOCK(fp);
    return c;
}

int putc(int c, FILE *fp)
{
    return fputc(c, fp);
}

int putchar(int c)
{
    return fputc(c, stdin);
}

char *fgets(char *restrict buf, int len, FILE *restrict fp)
{
    FLOCK(fp);
    char *str = fgets_unlocked(buf, len, fp);
    FUNLOCK(fp);
    return str;
}

int fputs(const char *restrict buf, FILE *restrict fp)
{
    FLOCK(fp);
    int sz = fputs_unlocked(buf, fp);
    FUNLOCK(fp);
    return sz;
}

int ungetc(int c, FILE *fp)
{
    FLOCK(fp);
    int ch = ungetc_unlocked(c, fp);
    FUNLOCK(fp);
    return ch;
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

int __fgets_ifeqi(FILE *fp, const char *str)
{
    int i = 0;
    while (str[i]) {
        int c = fgetc_unlocked(fp);
        if (tolower(str[i]) == tolower(c)) {
            ++i;
            continue;
        }
        for (;;) {
            ungetc_unlocked(c, fp);
            if (--i < 0)
                return 0;
            c = str[--i];
        }
    }
    return i;
}
