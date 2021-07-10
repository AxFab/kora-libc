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
#ifndef __STDDEF_H
#define __STDDEF_H 1

#ifdef __cplusplus
# define NULL 0
#else
# define NULL ((void*)0)
#endif


#ifndef itemof
#  undef offsetof
#  define offsetof(t,m)   ((size_t)&(((t*)0)->m))
#  define itemof(p,t,m)   ((t*)itemof_((p), offsetof(t,m)))
static inline void *itemof_(void *ptr, int off)
{
    return ptr ? (char *)ptr - off : 0;
}
#endif


typedef unsigned long size_t;
typedef int wchar_t;


#endif  /* __STDDEF_H */
