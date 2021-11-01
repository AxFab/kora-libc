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
#include <wchar.h>
#include <ctype.h>
#include <string.h>


struct unicode_map {
    unsigned unicode_base;
    unsigned unicode_limit;
    const char *block;
    const char *set;
    int flags;
    int to_upper;
    int to_lower;
};

struct unicode_map unicode_table[] = {
    // 0000-007F  ASCII
    { 0x0000, 0x001f, "Basic Latin", "C0 Controls", 0, 0, 0, },
    { 0x0020, 0x002f, "Basic Latin", "ASCII punctuation and symbols", 0, 0, 0 },
    { 0x0030, 0x0039, "Basic Latin", "ASCII digits", 0, 0, 0 },
    { 0x003a, 0x0040, "Basic Latin", "ASCII punctuation and symbols", 0, 0, 0 },
    { 0x0041, 0x005a, "Basic Latin", "Uppercase latin", _ISalpha, 0, 0x20 },
    { 0x005b, 0x0060, "Basic Latin", "ASCII punctuation and symbols", 0, 0, 0 },
    { 0x0061, 0x007a, "Basic Latin", "Lowercase latin", _ISalpha, 0, 0x20 },
    { 0x007b, 0x007e, "Basic Latin", "ASCII punctuation and symbols", 0, 0, 0 },
    { 0x007f, 0x007f, "Basic Latin", "Control character", 0, 0, 0 },
    // 0080-00FF  Latin-1
    // 0100-017F  Latin Extended-A
    // 0180-024F  Latin Extended-B
    // 0250-02AF  IPA Extended
    // 02B0-02FF  Spacing Modifier Letters
    // 10A0-10FF  Georgian
    { 0x10d0, 0x10f0, "Georgian", "Mkhedruli", _ISalpha, (0x1c90 - 0x10d0), 0 },
    { 0x1c90, 0x1cb0, "Georgian", "Mtavruli", _ISalpha, 0, -(0x1c90 - 0x10d0) },
    // FF00-FFEF  Halfwidth and fullwidth froms
    // FFF0-FFFF  Special
    { 0xfff0, 0xffff, "Special", "Special", 0, 0, 0, },
};

#define unicode_table_length (sizeof(unicode_table) / sizeof(struct unicode_map))


#define _IN_RANGE(w,min,max)  ((unsigned)(w)-(min)<=(unsigned)(max)-(min))

static wint_t __towcase(wint_t wc, int lower)
{
    // No case on those ranges
    if (!iswalpha(wc) ||
        _IN_RANGE(wc, 0x0600, 0x0fff) ||
        _IN_RANGE(wc, 0x2e00, 0xa63f) ||
        _IN_RANGE(wc, 0xa800, 0xab52) ||
        _IN_RANGE(wc, 0xabc0, 0xfeff))
        return wc;

    // U+10d0:U+10f0  Georgian/Mkhedruli (lower)
    // U+1c90:U+1cb0  Georgian/Mtavruli (upper)
    if (_IN_RANGE(wc, 0x10d0, 0x10f0))
        return lower ? wc : wc + (0x1c90 - 0x10d0);
    else if (_IN_RANGE(wc, 0x10d0, 0x10f0))
        return lower ? wc - (0x1c90 - 0x10d0) : wc;

    return wc;
}

static int __iswtype(wint_t wc, int flags)
{
    for (unsigned i = 0; i < unicode_table_length; ++i) {
        if (wc > unicode_table[i].unicode_limit)
            continue;
        if (wc < unicode_table[i].unicode_base)
            break;
        return (unicode_table[i].flags & flags) ? 1 : 0;
    }
    return 0;
}



int iswalpha(wint_t wc)
{
    return __iswtype(wc, _ISalpha);
}

int iswprint(wint_t wc)
{
    return __iswtype(wc, _ISprint);
}

int iswspace(wint_t wc)
{
    return __iswtype(wc, _ISspace);
}

int iswblank(wint_t wc)
{
    return __iswtype(wc, _ISblank);
}

int iswcntrl(wint_t wc)
{
    return __iswtype(wc, _IScntrl);
}

int iswpunct(wint_t wc)
{
    return __iswtype(wc, _ISpunct);
}

int iswdigit(wint_t wc)
{
    return __iswtype(wc, _ISdigit);
}

int iswxdigit(wint_t wc)
{
    return (unsigned)wc < 128 && isxdigit(wc & 0x7F);
}

int iswgraph(wint_t wc)
{
    return !iswspace(wc) && iswprint(wc);
}

int iswalnum(wint_t wc)
{
    return __iswtype(wc, _ISalpha | _ISdigit);
}

int iswlower(wint_t wc)
{
    return towupper(wc) != wc;
}

int iswupper(wint_t wc)
{
    return towlower(wc) != wc;
}


wint_t towupper(wint_t wc)
{
    return (unsigned)wc < 128 ? (wint_t)toupper(wc) : __towcase(wc, 0);
}

wint_t towlower(wint_t wc)
{
    return (unsigned)wc < 128 ? (wint_t)tolower(wc) : __towcase(wc, 1);
}


// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#define WCTYPE_ALNUM  1
#define WCTYPE_ALPHA  2
#define WCTYPE_BLANK  3
#define WCTYPE_CNTRL  4
#define WCTYPE_DIGIT  5
#define WCTYPE_GRAPH  6
#define WCTYPE_LOWER  7
#define WCTYPE_PRINT  8
#define WCTYPE_PUNCT  9
#define WCTYPE_SPACE  10
#define WCTYPE_UPPER  11
#define WCTYPE_XDIGIT 12

int iswctype(wint_t wc, wctype_t type)
{
    switch (type) {
    case WCTYPE_ALNUM:
        return iswalnum(wc);
    case WCTYPE_ALPHA:
        return iswalpha(wc);
    case WCTYPE_BLANK:
        return iswblank(wc);
    case WCTYPE_CNTRL:
        return iswcntrl(wc);
    case WCTYPE_DIGIT:
        return iswdigit(wc);
    case WCTYPE_GRAPH:
        return iswgraph(wc);
    case WCTYPE_LOWER:
        return iswlower(wc);
    case WCTYPE_PRINT:
        return iswprint(wc);
    case WCTYPE_PUNCT:
        return iswpunct(wc);
    case WCTYPE_SPACE:
        return iswspace(wc);
    case WCTYPE_UPPER:
        return iswupper(wc);
    case WCTYPE_XDIGIT:
        return iswxdigit(wc);
    }
    return 0;
}

wctype_t wctype(const char *s)
{
    static const char *name[] = {
        "alnum", "alpha", "blank", "cntrl", "digit", "graph",
        "lower", "print", "punct", "space", "upper", "xdigit",
        NULL,
    };

    for (int i = 0; i < 12; ++i) {
        if (strcmp(name[i], s) == 0)
            return i + 1;
    }
    return 0;
}


// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#define WCTRANS_UPPER 1
#define WCTRANS_LOWER 2

wctrans_t wctrans(const char *class)
{
    if (!strcmp(class, "toupper"))
        return WCTRANS_UPPER;
    if (!strcmp(class, "tolower"))
        return WCTRANS_LOWER;
    return 0;
}

wint_t towctrans(wint_t wc, wctrans_t trans)
{
    if (trans == WCTRANS_UPPER)
        return towupper(wc);
    if (trans == WCTRANS_LOWER)
        return towlower(wc);
    return wc;
}
