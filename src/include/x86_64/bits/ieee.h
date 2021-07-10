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
#ifndef __BITS_IEEE_H
#define __BITS_IEEE_H 1

#define IEEE_MAX_EXP  0x7fff

union IEEEl2bits {
    long double e;
    struct {
        unsigned int    manl    : 32;
        unsigned int    manh    : 32;
        unsigned int    exp : 15;
        unsigned int    sign    : 1;
        unsigned int    junk    : 16;
    } bits;
    struct {
        unsigned long long man  : 64;
        unsigned int    expsign : 16;
        unsigned int    junk    : 16;
    } xbits;
};

#endif  /* __BITS_IEEE_H */
