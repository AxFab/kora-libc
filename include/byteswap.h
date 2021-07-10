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
#ifndef __BYTESWAP_H
#define __BYTESWAP_H 1

#include <bits/cdefs.h>
#include <stdint.h>

static inline uint16_t __bswap16(uint16_t x)
{
    return ((x & 0xFF00) >> 8) | ((x & 0xFF) << 8);
}

static inline uint32_t __bswap32(uint32_t x)
{
    return ((x & 0xFF000000) >> 24) |
           ((x & 0xFF0000) >> 8) |
           ((x & 0xFF00) << 8) |
           ((x & 0xFF) << 24);
}

static inline uint64_t __bswap64(uint64_t x)
{
    return ((__bswap32(x) + 0ULL) << 32) | __bswap32(x >> 32);
}

#define bswap_16(x) __bswap16(x)
#define bswap_32(x) __bswap32(x)
#define bswap_64(x) __bswap64(x)

#endif  /* __BYTESWAP_H */
