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
#define _CTYPE_NO_MACROS  1
#include <ctype.h>

const unsigned char __ascii_b[] = {
    // 0x00
    _IScntrl, _IScntrl, _IScntrl, _IScntrl,
    _IScntrl, _IScntrl, _IScntrl, _IScntrl,
    _IScntrl, _IScntrl, _IScntrl, _IScntrl,
    _IScntrl, _IScntrl, _IScntrl, _IScntrl,
    // 0x10
    _IScntrl, _IScntrl, _IScntrl, _IScntrl,
    _IScntrl, _IScntrl, _IScntrl, _IScntrl,
    _IScntrl, _IScntrl, _IScntrl, _IScntrl,
    _IScntrl, _IScntrl, _IScntrl, _IScntrl,
    // 0x20
    _ISblank | _ISprint | _ISspace, _ISprint | _ISpunct, _ISprint | _ISpunct, _ISprint | _ISpunct,
    _ISprint | _ISpunct, _ISprint | _ISpunct, _ISprint | _ISpunct, _ISprint | _ISpunct,
    _ISprint | _ISpunct, _ISprint | _ISpunct, _ISprint | _ISpunct, _ISprint | _ISpunct,
    _ISprint | _ISpunct, _ISprint | _ISpunct, _ISprint | _ISpunct, _ISprint | _ISpunct,
    // 0x30
    _ISprint | _ISdigit, _ISprint | _ISdigit, _ISprint | _ISdigit, _ISprint | _ISdigit,
    _ISprint | _ISdigit, _ISprint | _ISdigit, _ISprint | _ISdigit, _ISprint | _ISdigit,
    _ISprint | _ISdigit, _ISprint | _ISdigit, _ISprint | _ISpunct, _ISprint | _ISpunct,
    _ISprint | _ISpunct, _ISprint | _ISpunct, _ISprint | _ISpunct, _ISprint | _ISpunct,
    // 0x40
    _ISprint | _ISpunct, _ISprint | _ISalpha | _ISxdigit, _ISprint | _ISalpha | _ISxdigit, _ISprint | _ISalpha | _ISxdigit,
    _ISprint | _ISalpha | _ISxdigit, _ISprint | _ISalpha | _ISxdigit, _ISprint | _ISalpha | _ISxdigit, _ISprint | _ISalpha,
    _ISprint | _ISalpha, _ISprint | _ISalpha, _ISprint | _ISalpha, _ISprint | _ISalpha,
    _ISprint | _ISalpha, _ISprint | _ISalpha, _ISprint | _ISalpha, _ISprint | _ISalpha,
    // 0x50
    _ISprint | _ISalpha, _ISprint | _ISalpha, _ISprint | _ISalpha, _ISprint | _ISalpha,
    _ISprint | _ISalpha, _ISprint | _ISalpha, _ISprint | _ISalpha, _ISprint | _ISalpha,
    _ISprint | _ISalpha, _ISprint | _ISalpha, _ISprint | _ISalpha, _ISprint | _ISpunct,
    _ISprint | _ISpunct, _ISprint | _ISpunct, _ISprint | _ISpunct, _ISprint | _ISpunct,
    // 0x60
    _ISprint | _ISpunct, _ISprint | _ISalpha | _ISxdigit, _ISprint | _ISalpha | _ISxdigit, _ISprint | _ISalpha | _ISxdigit,
    _ISprint | _ISalpha | _ISxdigit, _ISprint | _ISalpha | _ISxdigit, _ISprint | _ISalpha | _ISxdigit, _ISprint | _ISalpha,
    _ISprint | _ISalpha, _ISprint | _ISalpha, _ISprint | _ISalpha, _ISprint | _ISalpha,
    _ISprint | _ISalpha, _ISprint | _ISalpha, _ISprint | _ISalpha, _ISprint | _ISalpha,
    // 0x70
    _ISprint | _ISalpha, _ISprint | _ISalpha, _ISprint | _ISalpha, _ISprint | _ISalpha,
    _ISprint | _ISalpha, _ISprint | _ISalpha, _ISprint | _ISalpha, _ISprint | _ISalpha,
    _ISprint | _ISalpha, _ISprint | _ISalpha, _ISprint | _ISalpha, _ISprint | _ISpunct,
    _ISprint | _ISpunct, _ISprint | _ISpunct, _ISprint | _ISpunct, _IScntrl,
};

const int __ascii_lower[] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
    0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
    0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
    0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
    0x40, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
    0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
    0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,
    0x78, 0x79, 0x7A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F,
    0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
    0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
    0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,
    0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F,
};

const int __ascii_upper[] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
    0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
    0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
    0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
    0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
    0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F,
    0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57,
    0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F,
    0x60, 0x61, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
    0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F,
    0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57,
    0x58, 0x59, 0x5A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F,
};


const unsigned char **__ctype_b_loc(void)
{
    return (const unsigned char **)(&__ascii_b);
}

const int **__ctype_tolower_loc(void)
{
    return (const int **)(&__ascii_lower);
}

const int **__ctype_toupper_loc(void)
{
    return (const int **)(&__ascii_upper);
}


unsigned char __ctype_b(int chr)
{
    if (chr < 0 || chr > 0x7f)
        return 0;
    return __ascii_b[chr];
}

int __ctype_tolower(int chr)
{
    if (chr < 0 || chr > 0x7f)
        return 0;
    return __ascii_lower[chr];
}

int __ctype_toupper(int chr)
{
    if (chr < 0 || chr > 0x7f)
        return 0;
    return __ascii_upper[chr];
}




int isalnum(int c)
{
    return (_ISalpha | _ISdigit) & __ctype_b(c);
}

int isalpha(int c)
{
    return _ISalpha & __ctype_b(c);
}

int iscntrl(int c)
{
    return _IScntrl & __ctype_b(c);
}

int isdigit(int c)
{
    return _ISdigit & __ctype_b(c);
}

int islower(int c)
{
    return toupper(c) != c;
}

int isgraph(int c)
{
    return !(_ISspace & __ctype_b(c)) && (_ISprint & __ctype_b(c));
}

int isprint(int c)
{
    return _ISprint & __ctype_b(c);
}

int ispunct(int c)
{
    return _ISpunct & __ctype_b(c);
}

int isspace(int c)
{
    return _ISspace & __ctype_b(c);
}

int isupper(int c)
{
    return tolower(c) != c;
}

int isxdigit(int c)
{
    return _ISxdigit & __ctype_b(c);
}

int isblank(int c)
{
    return _ISblank & __ctype_b(c);
}


int tolower(int c)
{
    return __ctype_tolower(c);
}

int toupper(int c)
{
    return __ctype_toupper(c);
}

int isascii(int c)
{
    return (unsigned)(c) < 128;
}

int toascii(int c)
{
    return _ISalpha & __ctype_b(c);
}
