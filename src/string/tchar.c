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
#include <errno.h>
#include <bits/wint.h>

static void UTF8_START(unsigned char ch, mbstate_t *ps)
{
    if (ch >= 0xFC) {
        ps->len = 6;
        ps->val = ch & 0x1;
    } else if (ch >= 0xF8) {
        ps->len = 5;
        ps->val = ch & 0x3;
    } else if (ch >= 0xF0) {
        ps->len = 4;
        ps->val = ch & 0x7;
    } else if (ch >= 0xE0) {
        ps->len = 3;
        ps->val = ch & 0xF;
    } else if (ch >= 0xC0) {
        ps->len = 2;
        ps->val = ch & 0x1F;
    } else if (ch < 0x80) {
        ps->len = 1;
        ps->val = ch & 0x7F;
    } else
        ps->len = ps->val = 0;
}

static int UTF8_NEXT(unsigned char ch, mbstate_t *ps)
{
    if ((ch & 0xc0) != 0x80)
        return -1;
    ps->val = (ps->val << 6) | (ch & 0x3f);
    ps->len--;
    return 0;
}

static int UTF8_LEN(wchar_t wc)
{
    if ((unsigned)wc < 0x80)
        return 1;
    else if ((unsigned)wc < 0x800)
        return 2;
    else if ((unsigned)wc < 0x10000)
        return 3;
    else if ((unsigned)wc < 0x200000)
        return 4;
    else if ((unsigned)wc < 0x4000000)
        return 5;
    else if ((unsigned)wc < 0x80000000)
        return 6;
    return -1;
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

size_t mbrtowc(wchar_t *restrict wc, const char *restrict src, size_t n, mbstate_t *restrict ps)
{
    mbstate_t st;
    st.ll = ps ? ps->ll : 0;
    if (src == NULL) {
        if (st.len) {
            errno = EILSEQ;
            return (size_t) -1;
        }
        return 0;
    }

    if (n == 0)
        return (size_t) -2;

    size_t in = n;
    const unsigned char *mbstr  = (const void *)src;
    while (n-- > 0) {
        if (st.len == 0) {
            UTF8_START(*mbstr, &st);
            if (st.len == 0) {
                errno = EILSEQ;
                return (size_t) -1;
            }
            st.len--;
        } else if (UTF8_NEXT(*mbstr, &st) != 0) {
            errno = EILSEQ;
            return (size_t) -1;
        }

        if (st.len == 0) {
            if (wc)
                *wc = st.val;
            return in - n;
        }
    }

    if (ps)
        *ps = st;
    return (size_t) -2;
}

size_t mbsrtowcs(wchar_t *restrict ws, const char **restrict src, size_t wn, mbstate_t *restrict ps)
{
    size_t wr = 0;
    mbstate_t st;
    st.ll = ps ? ps->ll : 0;
    while (wn-- > 0) {
        int val = mbrtowc(ws, *src, MB_CUR_MAX, &st);
        if (val == -1) {
            if (ps)
                *ps = st;
            return -1;
        } else if (val == -2) {
            if (ps)
                *ps = st;
            errno = EILSEQ;
            return -1;
        }
        *src += val;
        if (*ws == 0)
            break;
        ws++;
        wr++;
    }
    if (ps)
        *ps = st;
    return wr;
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

size_t wcrtomb(char *restrict str, wchar_t wc, mbstate_t *restrict ps)
{
    if (ps)
        ps->len = ps->val = 0;
    if (str == NULL)
        return 1;
    if ((unsigned)wc < 0x80) {
        *str = wc;
        return 1;
    } else if ((unsigned)wc < 0x800) {
        *str++ = 0xc0 | (wc >> 6);
        *str = 0x80 | (wc & 0x3F);
        return 2;
    } else if ((unsigned)wc < 0x10000) {
        *str++ = 0xe0 | (wc >> 12);
        *str++ = 0x80 | ((wc >> 6) & 0x3F);
        *str = 0x80 | (wc & 0x3F);
        return 3;
    } else if ((unsigned)wc < 0x200000) {
        *str++ = 0xf0 | (wc >> 18);
        *str++ = 0x80 | ((wc >> 12) & 0x3F);
        *str++ = 0x80 | ((wc >> 6) & 0x3F);
        *str = 0x80 | wc;
        return 4;
    } else if ((unsigned)wc < 0x4000000) {
        *str++ = 0xf8 | (wc >> 24);
        *str++ = 0x80 | ((wc >> 18) & 0x3F);
        *str++ = 0x80 | ((wc >> 12) & 0x3F);
        *str++ = 0x80 | ((wc >> 6) & 0x3F);
        *str = 0x80 | wc;
        return 5;
    } else if ((unsigned)wc < 0x80000000) {
        *str++ = 0xf8 | (wc >> 30);
        *str++ = 0x80 | ((wc >> 24) & 0x3F);
        *str++ = 0x80 | ((wc >> 18) & 0x3F);
        *str++ = 0x80 | ((wc >> 12) & 0x3F);
        *str++ = 0x80 | ((wc >> 6) & 0x3F);
        *str = 0x80 | wc;
        return 6;
    }

    errno = EILSEQ;
    return -1;
}

size_t wcsrtombs(char *restrict str, const wchar_t **restrict ws, size_t n, mbstate_t *restrict ps)
{
    size_t wr = 0;
    while (**ws) {
        wchar_t wc = **ws;
        int l = UTF8_LEN(wc);
        if (l < 0) {
            errno = EILSEQ;
            return (size_t) -1;
        } else if (n < (unsigned)l) {
            ps->len = l;
            ps->val = wc;
            errno = EILSEQ;
            return (size_t) -1;
        }
        wr += wcrtomb(str, wc, NULL);
        (*ws)++;
        str += l;
        n -= l;
    }
    if (ps)
        ps->ll = 0;
    return wr;
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

size_t mbstowcs(wchar_t *restrict ws, const char *restrict str, size_t wlen)
{
    return mbsrtowcs(ws, (void *)&str, wlen, NULL);
}

int mbtowc(wchar_t *restrict wc, const char *restrict src, size_t n)
{
    return mbrtowc(wc, src, n, NULL);
}

size_t wcstombs(char *restrict str, const wchar_t *restrict ws, size_t len)
{
    return wcsrtombs(str, &(const wchar_t *) {
        ws
    }, len, NULL);
}

int wctomb(char *str, wchar_t wc)
{
    if (str == NULL)
        return 0;
    return wcrtomb(str, wc, NULL);
}

int mblen(const char *str, size_t len)
{
    return mbrtowc(NULL, str, len, NULL);
}

size_t mbrlen(const char *restrict str, size_t len, mbstate_t *restrict st)
{
    return mbrtowc(NULL, str, len, st);
}

int mbsinit(const mbstate_t *ps)
{
    return ps == NULL || ps->ll == 0;
}
