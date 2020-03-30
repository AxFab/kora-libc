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
#include <bits/cdefs.h>

#undef assert
#undef static_assert

#if defined NDEBUG
# define assert(n)  ((void)0)
#else
# define assert(n)   ((void)((n) || (__assert_fail(#n, __FILE__, __LINE__,__func__),0)))
#endif

#if defined __C11 && !defined __cplusplus
# define static_assert _Static_assert
#endif

__STDC_GUARD

_Noreturn void __assert_fail(const char *assertion, const char *file, unsigned line, const char *function);

__STDC_END

