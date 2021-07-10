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
#include <bits/ieee.h>

static const long double __huge = 0x1p16000L, __tiny = 0x1p-16000L;

long double __copysignl(long double x, long double y)
{
    union IEEEl2bits ux, uy;
    ux.e = x;
    uy.e = y;
    ux.bits.sign = uy.bits.sign;
    return (ux.e);
}

long double __scalbnl(long double x, int n)
{
    union IEEEl2bits u;
    u.e = x;

    int k = u.bits.exp + n;
    if (u.bits.exp == 0) {
        if ((u.bits.manh | u.bits.manl) == 0)
            return x; // zero
        u.e *= 0x1p+128;
        k = u.bits.exp - 128;
        if (n < -50000)
            return __copysignl(__tiny, x); // Underflow
    }

    if (k == IEEE_MAX_EXP)
        return x + x; // NaN or Inf.
    if (k >= IEEE_MAX_EXP)
        return __copysignl(__huge, x); // Overflow
    if (k >= 0) {
        u.bits.exp = k;
        return u.e;
    }
    if (k <= - 128) {
        if (n > 50000)
            return __copysignl(__huge, x); // Overflow
        return __copysignl(__tiny, x); // Underflow
    }
    k += 128;
    u.bits.exp = k;
    return u.e * 0x1p-128;
}

long double __scaldcl(long double x, int n)
{
    union IEEEl2bits u;
    u.e = x;

    // Dummy !!
    long double ex = 1.0;
    for (; n > 0; --n)
        ex *= 10.0;
    for (; n < 0; ++n)
        ex /= 10.0;

    return u.e * ex;
}
