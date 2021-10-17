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

#define BITOP(a,b,op) \
 ((a)[(size_t)(b)/(8*sizeof *(a))] op (size_t)1<<((size_t)(b)%(8*sizeof *(a))))



/* Scans one string for the first occurrence of any character that's in a second string. */
char *strpbrk(const char *s, const char *b)
{
    s += strcspn(s, b);
    return *s ? (char *)s : 0;
}

/* Scans a string for a segment that is a subset of a set of characters. */
size_t strspn(const char *s, const char *c)
{
    const char *a = s;
    size_t byteset[32 / sizeof(size_t)] = { 0 };

    if (!c[0])
        return 0;
    if (!c[1]) {
        for (; *s == *c; s++);
        return s - a;
    }

    for (; *c && BITOP(byteset, *(unsigned char *)c, |=); c++);
    for (; *s && BITOP(byteset, *(unsigned char *)s, &); s++);
    return s - a;
}

/* Scans a string. */
size_t strcspn(const char *s, const char *c)
{
    const char *a = s;
    size_t byteset[32 / sizeof(size_t)];

    if (!c[0] || !c[1])
        return strchrnul(s, *c) - a;

    memset(byteset, 0, sizeof byteset);
    for (; *c && BITOP(byteset, *(unsigned char *)c, |=); c++);
    for (; *s && !BITOP(byteset, *(unsigned char *)s, &); s++);
    return s - a;
}


/* Finds the first occurrence of a substring in another string. */
char *strstr(const char *haystack, const char *needle)
{
    // Based on Boyer–Moore–Horspool algorithm
    int len = strlen(needle);
    int haystack_len = strlen(haystack);
    if (len == 0)
        return (char *)haystack;
    if (len > haystack_len)
        return NULL;

    // Prepare character table
    int table[129];
    for (int i = 0; i < 129; ++i)
        table[i] = len;
    for (int i = 0; i < len - 1; ++i)
        table[needle[i] >= 0 ? needle[i] : 128] = len - 1 - i;

    // Look for needle
    int skip = 0;
    while (haystack_len - skip >= len) {
        const char *str = &haystack[skip];
        if (memcmp(str, needle, len) == 0)
            return (char *)&haystack[skip];
        char c = haystack[skip + len - 1];
        skip = skip + table[c >= 0 ? c : 128];
    }
    return NULL;
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

char *strchrnul(const char *s, int c)
{
    c = (unsigned char)c;
    if (!c)
        return (char *)s + strlen(s);
    for (; *s && *(unsigned char *)s != c; s++);
    return (char *)s;
}
