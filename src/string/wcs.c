#include <wchar.h>
#include <malloc.h>

wchar_t *wmemchr(const wchar_t *s, wchar_t c, size_t n)
{
    for (; n && *s != c; n--, s++);
    return n ? (wchar_t *)s : 0;
}

int wmemcmp(const wchar_t *l, const wchar_t *r, size_t n)
{
    for (; n && *l == *r; n--, l++, r++);
    return n ? *l - *r : 0;
}

wchar_t *wmemcpy(wchar_t *restrict d, const wchar_t *restrict s, size_t n)
{
    wchar_t *a = d;
    while (n--)
        *d++ = *s++;
    return a;
}

wchar_t *wmemmove(wchar_t *d, const wchar_t *s, size_t n)
{
    wchar_t *d0 = d;
    if (d == s)
        return d;
    if ((unsigned)((char *)d - (char *)s) < n * sizeof(wchar_t))
        while (n--)
            d[n] = s[n];
    else
        while (n--)
            *d++ = *s++;
    return d0;
}

wchar_t *wmemset(wchar_t *d, wchar_t c, size_t n)
{
    wchar_t *ret = d;
    while (n--)
        *d++ = c;
    return ret;
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

wchar_t *wcscat(wchar_t *restrict dest, const wchar_t *restrict src)
{
    wcscpy(dest + wcslen(dest), src);
    return dest;
}

wchar_t *wcschr(const wchar_t *s, wchar_t c)
{
    if (!c)
        return (wchar_t *)s + wcslen(s);
    for (; *s && *s != c; s++);
    return *s ? (wchar_t *)s : 0;
}

int wcscmp(const wchar_t *l, const wchar_t *r)
{
    for (; *l == *r && *l && *r; l++, r++);
    return *l - *r;
}

wchar_t *wcscpy(wchar_t *restrict d, const wchar_t *restrict s)
{
    wchar_t *a = d;
    while ((*d++ = *s++));
    return a;
}

size_t wcscspn(const wchar_t *s, const wchar_t *c)
{
    const wchar_t *a;
    if (!c[0])
        return wcslen(s);
    if (!c[1]) {
        a = s;
        s = wcschr(a, *c);
        if (s)
            return s - a;
        return wcslen(a);
    }
    for (a = s; *s && !wcschr(c, *s); s++);
    return s - a;
}

int wcsicmp(const wchar_t *l, const wchar_t *r)
{
    for (; towlower(*l) == towlower(*r) && *l && *r; l++, r++);
    return *l - *r;
}

size_t wcslen(const wchar_t *s)
{
    const wchar_t *a;
    for (a  = s; *s; s++);
    return s - a;
}

size_t wcsnlen(const wchar_t *s, size_t n)
{
    const wchar_t *z = wmemchr(s, 0, n);
    if (z)
        n = z - s;
    return n;
}

wchar_t *wcsncat(wchar_t *restrict d, const wchar_t *restrict s, size_t n)
{
    wchar_t *a = d;
    d += wcslen(d);
    while (n && *s) {
        n--;
        *d++ = *s++;
    }
    if (n > 0)
        *d++ = 0;
    return a;
}

int wcsncmp(const wchar_t *l, const wchar_t *r, size_t n)
{
    for (; n && *l == *r && *l && *r; n--, l++, r++);
    return n ? *l - *r : 0;
}

wchar_t *wcsncpy(wchar_t *restrict d, const wchar_t *restrict s, size_t n)
{
    wchar_t *a = d;
    while (n && *s) {
        n--;
        *d++ = *s++;
    }
    if (n > 0)
        *d++ = 0;
    return a;
}

wchar_t *wcspbrk(const wchar_t *s, const wchar_t *b)
{
    s += wcscspn(s, b);
    return *s ? (wchar_t *)s : NULL;
}

wchar_t *wcsrchr(const wchar_t *s, wchar_t c)
{
    const wchar_t *p;
    for (p = s + wcslen(s); p >= s && *p != c; p--);
    return p >= s ? (wchar_t *)p : 0;
}

size_t wcsspn(const wchar_t *s, const wchar_t *c)
{
    const wchar_t *a;
    for (a = s; *s && wcschr(c, *s); s++);
    return s - a;
}

// wchar_t *wcsstr(const wchar_t *restrict h, const wchar_t *restrict n)
// {
// }

// wchar_t *wcstok(wchar_t *restrict s, const wchar_t *restrict sep, wchar_t **restrict p)
// {
// }

wchar_t *wcsdup(const wchar_t *s)
{
    size_t l = wcslen(s);
    wchar_t *d = malloc((l + 1) * sizeof(wchar_t));
    if (!d)
        return NULL;
    return wmemcpy(d, s, l + 1);
}


wchar_t *wcslwr(wchar_t *s)
{
    wchar_t *a;
    for (a = s; *s; s++)
        *s = towlower(*s);
    return a;
}

wchar_t *wcsupr(wchar_t *s)
{
    wchar_t *a;
    for (a = s; *s; s++)
        *s = towupper(*s);
    return a;
}

