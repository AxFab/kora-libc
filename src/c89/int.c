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
#include <stdlib.h>
#include <inttypes.h>

int abs(int value)
{
    return (value >= 0) ? value : -value;
}

long labs(long value)
{
    return (value >= 0) ? value : -value;
}

long long llabs(long long value)
{
    return (value >= 0) ? value : -value;
}

div_t div(int numer, int denom)
{
    div_t rc;
    rc.quot = numer / denom;
    rc.rem  = numer % denom;
    return rc;
}

ldiv_t ldiv(long numer, long denom)
{
    ldiv_t rc;
    rc.quot = numer / denom;
    rc.rem  = numer % denom;
    return rc;
}

lldiv_t lldiv(long long numer, long long denom)
{
    lldiv_t rc;
    rc.quot = numer / denom;
    rc.rem  = numer % denom;
    return rc;
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

intmax_t imaxabs(intmax_t value)
{
    return (value >= 0) ? value : -value;
}

imaxdiv_t imaxdiv(intmax_t numer, intmax_t denom)
{
    imaxdiv_t rc;
    rc.quot = numer / denom;
    rc.rem  = numer % denom;
    return rc;
}
