#include <stddef.h>

// Multibyte/wide character conversions

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Defined in header <stdlib.h>

static int mblen_(const char *str, size_t lg)
{
    int len = 1;
    unsigned s = (unsigned char)(*str);
    if (s >= 0xfe)
        return -1;
    else if (s >= 0xfc)
        len = 6;
    else if (s >= 0xf8)
        len = 5;
    else if (s >= 0xf0)
        len = 4;
    else if (s >= 0xe0)
        len = 3;
    else if (s >= 0xc0)
        len = 2;
    else if (s >= 0x80)
        return -1;
    if (lg < (unsigned)len)
        return -1;
    return len;
}

// returns the number of bytes in the next multibyte character
int mblen(const char *str, size_t lg)
{
    int i, len = mblen_(str, lg);
    for (i = 1; i < len; ++i) {
        if ((str[i] & 0xc0) != 0x80)
            return -1;
    }
    return len;
}

// Converts the next multibyte character to wide character
int mbtowc(wchar_t *restrict pwc, const char *restrict str, size_t lg)
{
    // mbstate_t ps;
    // return mbrtowc(pwc, str, lg, &ps);
    int len = mblen(str, lg);
    if (len == 1) {
        *pwc = *str;
        return 1;
    }
    if (len < 1)
        return -1;
    int l = 0, i = len;
    int wc = 0;
    while (i-- > 1)
        wc |= (((unsigned char)str[i] & 0x3f) << (6 * l++));
    wc |= (((unsigned char)str[0]) & ((1 << (6 - l)) - 1)) << (6 * l);
    *pwc = wc;
    return len;
}

// converts a wide character to its multibyte representation
int wctomb(char *str, wchar_t wc)
{
    if (wc < 0)
        return -1;
    else if (wc < 0x80) {
        str[0] = wc & 0x7f;
        return 1;
    } else if (wc < 0x800) {
        str[0] = 0xc0 | ((wc >> 6) & 0x1f);
        str[1] = 0x80 | (wc & 0x3f);
        return 2;
    } else if (wc < 0x10000) {
        str[0] = 0xe0 | ((wc >> 12) & 0x0f);
        str[1] = 0x80 | ((wc >> 6) & 0x3f);
        str[2] = 0x80 | (wc & 0x3f);
        return 3;
    } else if (wc < 0x400000) {
        str[0] = 0xf0 | ((wc >> 18) & 0x07);
        str[1] = 0x80 | ((wc >> 12) & 0x3f);
        str[2] = 0x80 | ((wc >> 6) & 0x3f);
        str[3] = 0x80 | (wc & 0x3f);
        return 4;
    } else if (wc < 0x4000000) {
        str[0] = 0xf8 | ((wc >> 24) & 0x03);
        str[1] = 0x80 | ((wc >> 18) & 0x3f);
        str[2] = 0x80 | ((wc >> 12) & 0x3f);
        str[3] = 0x80 | ((wc >> 6) & 0x3f);
        str[4] = 0x80 | (wc & 0x3f);
        return 5;
    } else {
        str[0] = 0xfc | ((wc >> 30) & 0x01);
        str[1] = 0x80 | ((wc >> 24) & 0x3f);
        str[2] = 0x80 | ((wc >> 18) & 0x3f);
        str[3] = 0x80 | ((wc >> 12) & 0x3f);
        str[4] = 0x80 | ((wc >> 6) & 0x3f);
        str[5] = 0x80 | (wc & 0x3f);
        return 6;
    }
}


// int wctomb_s(int *restrict status, char *restrict str, rsize_t ssz, wchar_t wc);

// // converts a narrow multibyte character string to wide string
// size_t mbstowcs(wchar_t *restrict dst, const char *restrict src, size_t len);
// // int mbstowcs_s(size_t *restrict retval, wchar_t *restrict dst, rsize_t dstsz, const char *restrict src, rsize_t len);

// // converts a wide string to narrow multibyte character string
// size_t wcstombs(char *restrict dst, const wchar_t *restrict src, size_t len);
// // int wcstombs_s(size_t *restrict retval, char *restrict dst, rsize_t dstsz, const wchar_t *restrict src, rsize_t len );

// // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// // Defined in header <wchar.h>

// // checks if the mbstate_t object represents initial shift state
// int mbsinit(const mbstate_t *ps);

// // widens a single-byte narrow character to wide character, if possible
// win_t btowc(int c);

// // narrows a wide character to a single-byte narrow character, if possible
// int wctob(wint_t c);

// // returns the number of bytes in the next multibyte character, given state
// size_t mbrlen( const char *restrict s, size_t n, mbstate_t *restrict ps );

// // converts the next multibyte character to wide character, given state
// size_t mbrtowc( wchar_t *restrict pwc, const char *restrict s, size_t n, mbstate_t *restrict ps )
// {

// }

// // converts a wide character to its multibyte representation, given state
// size_t wcrtomb( char *restrict s, wchar_t wc, mbstate_t *restrict ps);
// int wcrtomb_s(size_t *restrict retval, char *restrict s, rsize_t ssz, wchar_t wc, mbstate_t *restrict ps);

// // converts a narrow multibyte character string to wide string, given state
// size_t mbsrtowcs( wchar_t *restrict dst, const char **restrict src, size_t len, mbstate_t *restrict ps);
// int mbsrtowcs_s( size_t *restrict retval, wchar_t *restrict dst, rsize_t dstsz, const char **restrict src, rsize_t len, mbstate_t *restrict ps);

// // converts a wide string to narrow multibyte character string, given state
// size_t wcsrtombs( char *restrict dst, const wchar_t **restrict src, size_t len, mbstate_t *restrict ps);
// int wcsrtombs_s( size_t *restrict retval, char *restrict dst, rsize_t dstsz, const wchar_t **restrict src, rsize_t len, mbstate_t *restrict ps);

// // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// // Defined in header <uchar.h>

// // generates the next 16-bit wide character from a narrow multibyte string
// size_t mbrtoc16(char16_t * restrict pc16, const char * restrict s, size_t n, mbstate_t * restrict ps);

// // converts a 16-bit wide character to narrow multibyte string
// size_t c16rtomb(char * restrict s, char16_t c16, mbstate_t * restrict ps);

// // generates the next 32-bit wide character from a narrow multibyte string
// size_t mbrtoc32(char32_t restrict * pc32, const char * restrict s, size_t n, mbstate_t * restrict ps);

// // converts a 32-bit wide character to narrow multibyte string
// size_t c32rtomb(char * restrict s, char32_t c32, mbstate_t * restrict ps);






// // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// // Defined in header <wchar.h>

// // conversion state information necessary to iterate multibyte character strings
// typedef int mbstate_t;


// // Defined in header <uchar.h>

// // 16-bit wide character type
// typedef signed short char16_t;
// // 32-bit wide character type
// typedef unsigned int char32_t;



// // Defined in header <limits.h>
// // maximum number of bytes in a multibyte character, for any supported locale
// #define MB_LEN_MAX  6

// // Defined in header <stdlib.h>
// // maximum number of bytes in a multibyte character, in the current locale
// #define MB_CUR_MAX  5


// // Defined in header <uchar.h>


// // indicates that UTF-16 encoding is used by mbrtoc16 and c16rtomb
// #define __STDC_UTF_16__  1


// // indicates that UTF-32 encoding is used by mbrtoc32 and c32rtomb
// #define __STDC_UTF_32__  1
