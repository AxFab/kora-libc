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
#ifndef __WCHAR_H
#define __WCHAR_H 1

#include <stddef.h>
#include <bits/cdefs.h>
#include <bits/wint.h>
#include <bits/libio.h>
#include <stdarg.h>

#undef WEOF
#define WEOF 0xffffffffU

#define _TVOID wchar_t
#define _TCHAR wchar_t
#define _SFM(n)  wmem ## n
#define _SFX(n)  wcs ## n
#include <string.h>

__STDC_GUARD

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

long wcstol(const wchar_t *nptr, wchar_t **endptr, int base);
unsigned long wcstoul(const wchar_t *nptr, wchar_t **endptr, int base);
long long wcstoll(const wchar_t *nptr, wchar_t **endptr, int base);
unsigned long long wcstoull(const wchar_t *nptr, wchar_t **endptr, int base);

float wcstof(const wchar_t *restrict ws, wchar_t **restrict ptr);
double wcstod(const wchar_t *restrict ws, wchar_t **restrict ptr);
long double wcstold(const wchar_t *restrict ws, wchar_t **restrict ptr);


wint_t btowc(int by);
int wctob(wint_t wc);

size_t mbrtowc(wchar_t *restrict wc, const char *restrict src, size_t n, mbstate_t *restrict ps);
size_t mbsrtowcs(wchar_t *restrict ws, const char **restrict src, size_t wn, mbstate_t *restrict ps);
size_t wcrtomb(char *restrict str, wchar_t wc, mbstate_t *restrict ps);
size_t wcsrtombs(char *restrict str, const wchar_t **restrict ws, size_t n, mbstate_t *restrict ps);
size_t mbstowcs(wchar_t *restrict ws, const char *restrict str, size_t wlen);
int mbtowc(wchar_t *restrict wc, const char *restrict src, size_t n);
size_t wcstombs(char *restrict str, const wchar_t *restrict ws, size_t len);
int wctomb(char *str, wchar_t wc);
int mblen(const char *str, size_t len);
size_t mbrlen(const char *restrict str, size_t len, mbstate_t *restrict st);
int mbsinit(const mbstate_t *ps);

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

int fwide(FILE *fp, int mode);

wint_t fgetwc(FILE *fp);
wint_t getwc(FILE *fp);
wint_t getwchar(void);

wint_t fputwc(wint_t wc, FILE *fp);
wint_t putwc(wint_t wc, FILE *fp);
wint_t putwchar(wint_t wc);

wchar_t *fgetws(wchar_t *restrict buf, int len, FILE *restrict fp);
int fputws(const wchar_t *restrict buf, FILE *restrict fp);
wint_t ungetwc(wint_t wc, FILE *fp);


int vfwprintf(FILE *restrict f, const wchar_t *restrict fmt, va_list ap);
int wprintf(const wchar_t *restrict fmt, ...);
int vwprintf(const wchar_t *restrict fmt, va_list ap);
int fwprintf(FILE *restrict f, const wchar_t *restrict fmt, ...);
int swprintf(wchar_t *restrict s, size_t n, const wchar_t *restrict fmt, ...);
int vswprintf(wchar_t *restrict s, size_t n, const wchar_t *restrict fmt, va_list ap);

int vfwscanf(FILE *restrict fp, const wchar_t *restrict fmt, va_list ap);
int wscanf(const wchar_t *restrict fmt, ...);
int vwscanf(const wchar_t *restrict fmt, va_list ap);
int fwscanf(FILE *restrict fp, const wchar_t *restrict fmt, ...);
int swscanf(const wchar_t *restrict ws, const wchar_t *restrict fmt, ...);
int vswscanf(const wchar_t *restrict ws, const wchar_t *restrict fmt, va_list ap);

#if defined(__GNU)
wint_t fgetwc_unlocked(FILE *fp);
wint_t getwc_unlocked(FILE *fp);
wint_t getwchar_unlocked(void);

wint_t fputwc_unlocked(wint_t wc, FILE *fp);
wint_t putwc_unlocked(wint_t wc, FILE *fp);
wint_t putwchar_unlocked(wint_t wc);

wchar_t *fgetws_unlocked(wchar_t *restrict buf, int len, FILE *restrict fp);
int fputws_unlocked(const wchar_t *restrict buf, FILE *restrict fp);
#endif

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

int iswalnum(wint_t wc);
int iswalpha(wint_t wc);
int iswcntrl(wint_t wc);
int iswdigit(wint_t wc);
int iswlower(wint_t wc);
int iswgraph(wint_t wc);
int iswprint(wint_t wc);
int iswpunct(wint_t wc);
int iswspace(wint_t wc);
int iswupper(wint_t wc);
int iswblank(wint_t wc);
int iswxdigit(wint_t wc);

wint_t towlower(wint_t wc);
wint_t towupper(wint_t wc);

#if __LOCALE

#include <bits/locale.h>

int iswalnum_l(wint_t wc, __locale_t l);
int iswalpha_l(wint_t wc, __locale_t l);
int iswcntrl_l(wint_t wc, __locale_t l);
int iswdigit_l(wint_t wc, __locale_t l);
int iswlower_l(wint_t wc, __locale_t l);
int iswgraph_l(wint_t wc, __locale_t l);
int iswprint_l(wint_t wc, __locale_t l);
int iswpunct_l(wint_t wc, __locale_t l);
int iswspace_l(wint_t wc, __locale_t l);
int iswupper_l(wint_t wc, __locale_t l);
int iswblank_l(wint_t wc, __locale_t l);
int iswxdigit_l(wint_t wc, __locale_t l);

wint_t towlower_l(wint_t wc, __locale_t l);
wint_t towupper_l(wint_t wc, __locale_t l);

#endif

typedef int wctype_t;
typedef int wctrans_t;

int iswctype(wint_t wc, wctype_t type);
wctype_t wctype(const char *s);
wctrans_t wctrans(const char *class);
wint_t towctrans(wint_t wc, wctrans_t trans);

__STDC_END

#endif  /* __WCHAR_H */
