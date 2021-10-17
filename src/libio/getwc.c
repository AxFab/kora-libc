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
#include <wchar.h>
#include <errno.h>

wint_t fgetwc_unlocked(FILE *fp)
{
    wchar_t wc;
    // TODO -- Optimization if we use the buffer

    mbstate_t st = { 0 };
    int c;
    size_t ln = (size_t) -2;
    while (ln == (size_t) -2) {
        unsigned char by = c = fgetc_unlocked(fp);
        ln = c < 0 ? (size_t) -1 : mbrtowc(&wc, (void *)&by, 1, &st);
        if (ln == (size_t) -1) {
            fp->flags_ |= F_ERR;
            // ungetc(b, f);
            return WEOF;
        }
    }
    return wc;
}

wint_t fputwc_unlocked(wint_t wc, FILE *fp)
{
    char buf[8];
    size_t ln = wcrtomb(buf, wc, NULL);
    if (ln == (size_t) -1)
        wc = WEOF;
    else if (fwrite_unlocked(buf, ln, 1, fp) < ln)
        wc = WEOF;
    if (wc == WEOF)
        fp->flags_ |= F_ERR;
    return wc;
}

wchar_t *fgetws_unlocked(wchar_t *restrict buf, int len, FILE *restrict fp)
{
    wchar_t *ws = buf;
    if (len == 0)
        return buf;
    errno = EAGAIN;
    for (; len; --len) {
        wint_t wc = fgetwc_unlocked(fp);
        if (wc == WEOF)
            break;
        *ws++ = wc;
        if (wc == L'\n')
            break;
    }
    *ws = L'\0';
    if (ferror(fp) || errno == EILSEQ)
        ws = buf;
    return ws == buf ? NULL : buf;
}

int fputws_unlocked(const wchar_t *restrict ws, FILE *restrict fp)
{
    char buf[8];
    size_t ln = 0;
    const wchar_t *ps = ws;
    if (buf == NULL)
        return 0;
    while (ps) {
        ln = wcsrtombs(buf, &ps, 8, NULL);
        if (ln < 1)
            return -1;
        fwrite_unlocked(buf, ln, 1, fp);
    }
    return 0;
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

wint_t getwc_unlocked(FILE *fp)
{
    return fgetwc_unlocked(fp);
}

wint_t getwchar_unlocked(void)
{
    return fgetwc_unlocked(stdin);
}

wint_t putwc_unlocked(wint_t wc, FILE *fp)
{
    return fputwc_unlocked(wc, fp);
}

wint_t putwchar_unlocked(wint_t wc)
{
    return fputwc_unlocked(wc, stdout);
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

wint_t fgetwc(FILE *fp)
{
    FLOCK(fp);
    wint_t wc = fgetwc_unlocked(fp);
    FUNLOCK(fp);
    return wc;
}

wint_t getwc(FILE *fp)
{
    return fgetwc(fp);
}

wint_t getwchar(void)
{
    return fgetwc(stdin);
}

wint_t fputwc(wint_t wc, FILE *fp)
{
    FLOCK(fp);
    wc = fputwc_unlocked(wc, fp);
    FUNLOCK(fp);
    return wc;
}

wint_t putwc(wint_t wc, FILE *fp)
{
    return fputwc(wc, fp);
}

wint_t putwchar(wint_t wc)
{
    return fputwc(wc, stdin);
}

wchar_t *fgetws(wchar_t *restrict buf, int len, FILE *restrict fp)
{
    FLOCK(fp);
    wchar_t *ws = fgetws_unlocked(buf, len, fp);
    FUNLOCK(fp);
    return ws;
}

int fputws(const wchar_t *restrict buf, FILE *restrict fp)
{
    FLOCK(fp);
    int sz = fputws_unlocked(buf, fp);
    FUNLOCK(fp);
    return sz;
}
