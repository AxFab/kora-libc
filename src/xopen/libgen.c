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
#include <string.h>

char *basename(char *path)
{
    int lg = strlen(path);
    if (lg > 0 && path[lg - 1] == '/')
        path[lg - 1] = '\0';

    char *name = strrchr(path, '/');
    if (name == NULL)
        name = path;
    else
        name++;
    return name;
}

char *dirname(char *path)
{
    int lg = strlen(path);
    if (lg > 0 && path[lg - 1] == '/')
        path[lg - 1] = '\0';

    char *last = strrchr(path, '/');
    if (last != NULL)
        last[0] = '\0';
    return path;
}

