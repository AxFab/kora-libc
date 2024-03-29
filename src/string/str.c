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
#include <stddef.h>
#include <ctype.h>
#include <malloc.h>
#include <locale.h>

/* Scans s1 for the first token not contained in s2. */
char *strtok_r(register char *s, const char *delim, char **lasts)
{
    int skip_leading_delim = 1;
    register char *spanp;
    register int c, sc;
    char *tok;

    if (s == NULL && (s = *lasts) == NULL)
        return NULL;

    /*
     * Skip (span) leading delimiters (s += strspn(s, delim), sort of).
     */
cont:
    c = *s++;

    for (spanp = (char *) delim; (sc = *spanp++) != 0;) {
        if (c == sc) {
            if (skip_leading_delim)
                goto cont;

            else {
                *lasts = s;
                s[-1] = 0;
                return (s - 1);
            }
        }
    }

    if (c == 0) {        /* no non-delimiter characters */
        *lasts = NULL;
        return NULL;
    }

    tok = s - 1;

    /*
     * Scan token (scan for delimiters: s += strcspn(s, delim), sort of).
     * Note that delim must have one NUL; we stop if we see that, too.
     */
    for (;;) {
        c = *s++;
        spanp = (char *) delim;

        do {
            if ((sc = *spanp++) == c) {
                if (c == 0)
                    s = NULL;

                else
                    s[-1] = 0;

                *lasts = s;
                return (tok);
            }
        } while (sc != 0);
    }
}

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */


/* Searches the first len bytes of array str for character c. */
void *memchr(const void *str, int c, size_t len)
{
    register const char *ptr0 = (const char *)str;

    while (len > 0 && (*ptr0 != (char)c)) {
        ++ptr0;
        --len;
    }

    return (void *)(len ? ptr0 : 0);
}

/* Searches the first len bytes of array str for character c. */
void *memrchr(const void *str, int c, size_t len)
{
    register const char *ptr0 = ((const char *)str) + len;

    while (len > 0 && (*ptr0 != (char)c)) {
        --ptr0;
        --len;
    }

    return (void *)(len ? ptr0 : 0);
}

/* Compares two blocks of signed chars. */
int memcmp(const void *s1, const void *s2, size_t len)
{
    register const char *ptr1 = (const char *) s1;
    register const char *ptr2 = (const char *) s2;

    while (--len && *ptr1 == *ptr2) {
        ++ptr1;
        ++ptr2;
    }

    return *ptr1 - *ptr2;
}

/* Copies a block of len bytes from src to dest. */
void *memcpy(void *dest, const void *src, size_t len)
{
    register char *ptr1 = (char *)dest;
    register const char *ptr2 = (const char *)src;

    while (len-- > 0)
        *ptr1++ = *ptr2++;

    return dest;
}

/* Copies a block of len bytes from src to dest, with possibility of overlaping of source and destination block. */
void *memmove(void *dest, const void *src, size_t len)
{
    register char *ptr1 = (char *)dest;
    register const char *ptr2 = (const char *)src;

    if (ptr1 >= ptr2 || ptr1 >= ptr2 + len) {
        while (len--)
            *ptr1++ = *ptr2++;
    } else {
        ptr1 += len - 1;
        ptr2 += len - 1;

        while (len-- > 0)
            *ptr1-- = *ptr2--;
    }

    return dest;
}

/* Sets num bytes of buffer to byte c. */
void *memset(void *buffer, int c, size_t num)
{
    register char *org = (char *)buffer;
    while (num--)
        *org++ = (char)c;

    return buffer;
}


/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/* Appends src to dest. */
char *strcat(char *dest, const char *src)
{
    register char *ptr1 = (char *)dest;
    register const char *ptr2 = (const char *)src;

    while (*ptr1)
        ++ptr1;

    while ((*ptr1++ = *ptr2++));
    return dest;
}

/* Finds c in str. */
char *strchr(const char *str, int c)
{
    while (*str) {
        if (*str == (char)c)
            return (char *)str;

        str++;
    }

    return NULL;
}

/* Compares one string to another. */
int strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2)) {
        ++s1;
        ++s2;
    }

    return *s1 - *s2;
}

/* Copies string src to dest. */
char *strcpy(char *dest, const char *src)
{
    register char *ptr1 = (char *)dest;
    register const char *ptr2 = (const char *)src;

    while ((*ptr1++ = *ptr2++));
    return dest;
}

/* Performs case-insensitive string comparison. */
int stricmp(const char *s1, const char *s2)
{
    while (*s1 && (tolower(*s1) == tolower(*s2))) {
        ++s1;
        ++s2;
    }

    return *s1 - *s2;
}

/* Calculates length of a string. */
size_t strlen(const char *str)
{
    register const char *end = str;
    while (*end)
        ++end;

    return end - str;
}

/* Calculates length of a string. */
size_t strnlen(const char *str, size_t maxlen)
{
    register const char *end = str;
    while (*end && --maxlen)
        ++end;

    return end - str;
}

/* Appends at most maxlen characters of src to dest. */
char *strncat(char *dest, const char *src, size_t maxlen)
{
    register char *ptr1 = (char *)dest;
    register const char *ptr2 = (const char *)src;

    while (*ptr1)
        ++ptr1;

    while (maxlen-- > 0 && (*ptr1++ = *ptr2++));
    return dest;
}

/* Compares at most maxlen characters of one string to another. */
int strncmp(const char *s1, const char *s2, size_t maxlen)
{
    while (--maxlen && *s1 && *s1 == *s2) {
        ++s1;
        ++s2;
    }

    return *s1 - *s2;
}

/* Copies at most maxlen characters of src to dest. */
char *strncpy(char *dest, const char *src, size_t maxlen)
{
    register char *ptr1 = (char *)dest;
    register const char *ptr2 = (const char *)src;

    while (maxlen-- > 0 && (*ptr1++ = *ptr2++));
    return dest;
}

/* Finds the last occurrence of c in str. */
char *strrchr(const char *str, int c)
{
    int lg = strlen(str) - 1;
    for (; lg >= 0; --lg) {
        if (str[lg] == (char)c)
            return (char *)&str[lg];
    }

    return NULL;
}

/* Scans s1 for the first token not contained in s2. */
char *strtok(char *s1, const char *s2)
{
    static char *_reent = 0;
    return strtok_r(s1, s2, &_reent);
}

/* duplicate a string  */
char *strdup(const char *str)
{
    size_t lg = strlen(str);
    char *ptr = (char *)malloc(lg + 1);
    memcpy(ptr, str, lg);
    ptr[lg] = '\0';
    return ptr;
}

/* duplicate a string at most maxlen characters */
char *strndup(const char *str, size_t maxlen)
{
    size_t lg = strnlen(str, maxlen);
    char *ptr = (char *)malloc(lg + 1);
    memcpy(ptr, str, lg);
    ptr[lg] = '\0';
    return ptr;
}

/* Convert a string to lowercase. */
char *strlwr(char *str)
{
    for (char *ptr = str; *ptr; ptr++)
        *ptr = tolower(*ptr);
    return str;
}

/* Convert a string to uppercase. */
char *strupr(char *str)
{
    for (char *ptr = str; *ptr; ptr++)
        *ptr = toupper(*ptr);
    return str;
}


/* Compare characters of two strings without regard to case. */
int strnicmp(const char *s1, const char *s2, size_t maxlen)
{
    while (--maxlen && *s1 && tolower(*s1) == tolower(*s2)) {
        ++s1;
        ++s2;
    }

    return *s1 - *s2;
}

/* Set characters of a string to a character. */
char *strset(char *str, int c)
{
    char *svg = str;
    while (*str)
        *str++ = c;
    return svg;
}

/* Initialize characters of a string to a given format. */
char *strnset(char *str, int c, size_t maxlen)
{
    char *svg = str;
    while (*str && maxlen-- > 0)
        *str++ = c;
    return svg;
}


/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/* Compare strings using locale-specific information. */
int strcoll_l(const char *s1, const char *s2, locale_t loc)
{
    return strcmp(s1, s2);
}

/* Compare strings using locale-specific information. */
int stricoll_l(const char *s1, const char *s2, locale_t loc)
{
    return stricmp(s1, s2);
}

/* Compare strings using locale-specific information. */
int strncoll_l(const char *s1, const char *s2, size_t maxlen, locale_t loc)
{
    return strncmp(s1, s2, maxlen);
}

/* Compare strings using locale-specific information. */
int strnicoll_l(const char *s1, const char *s2, size_t maxlen, locale_t loc)
{
    return strnicmp(s1, s2, maxlen);
}

/* String transformation */
size_t strxfrm_l(char *dest, const char *src, size_t n, locale_t loc)
{
    size_t len = strlen(src);
    if (n > len)
        strcpy(dest, src);
    return len;
}


/* Compare strings using locale-specific information. */
int strcoll(const char *s1, const char *s2)
{
    return strcoll_l(s1, s2, __current_locale());
}

/* Compare strings using locale-specific information. */
int stricoll(const char *s1, const char *s2)
{
    return stricoll_l(s1, s2, __current_locale());
}

/* Compare strings using locale-specific information. */
int strncoll(const char *s1, const char *s2, size_t maxlen)
{
    return strncoll_l(s1, s2, maxlen, __current_locale());
}

/* Compare strings using locale-specific information. */
int strnicoll(const char *s1, const char *s2, size_t maxlen)
{
    return strnicoll_l(s1, s2, maxlen, __current_locale());
}

/* String transformation */
size_t strxfrm(char *dest, const char *src, size_t n)
{
    return strxfrm_l(dest, src, n, __current_locale());
}
