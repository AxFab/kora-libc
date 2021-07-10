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
#include <stddef.h>
#include <bits/wint.h>

wint_t btowc(int by)
{
    int ub = (unsigned char)by;
    if ((unsigned)ub < 128U)
        return ub;
    // if (MB_CUR_MAX == 1)
    return WEOF;
}

int wctob(wint_t wc)
{
    if ((unsigned)wc < 128U)
        return wc;
    // if (MB_CUR_MAX == 1)
    return -1;
}
