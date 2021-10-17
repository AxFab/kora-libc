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

void exit(int);
void printf(const char *, ...);

void __ni(const char *func)
{
    printf("Not Implemented: %s\n", func);
    exit(-1);
}

#define __NI(n) void n() { __ni(#n); }

__NI(waitpid)
__NI(getpid)
__NI(kill)
__NI(sigaction)
__NI(vfwprintf)
__NI(vfscanf)
__NI(pspawn)
__NI(vfwscanf)
__NI(sigprocmask)
