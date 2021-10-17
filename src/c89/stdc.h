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
#ifndef __BITS_CRT_H
#define __BITS_CRT_H 1

#include <stddef.h>

void *malloc(size_t len);
void free(void *ptr);

int open(const char *path, int flags, ...);
int close(int fd);
int read(int fd, char *buf, size_t len);
int write(int fd, const char *buf, size_t len);
int lseek(int fd, int off, int whence);


#endif  /* __BITS_CRT_H */
