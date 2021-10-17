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


#if WORDSIZE == 32

struct msghdr {
    void *msg_name;
    socklen_t msg_namelen;
    struct iovec *msg_iov;
    int msg_iovlen;
    void *msg_control;
    socklen_t msg_controllen;
    int msg_flags;
};

struct cmsghdr {
    socklen_t cmsg_len;
    int cmsg_level;
    int cmsg_type;
};

#elif WORDSIZE == 64 && __BYTE_ORDER == __LITTLE_ENDIAN

struct msghdr {
    void *msg_name;
    socklen_t msg_namelen;
    struct iovec *msg_iov;
    int msg_iovlen, __pad1;
    void *msg_control;
    socklen_t msg_controllen, __pad2;
    int msg_flags;
};

struct cmsghdr {
    socklen_t cmsg_len;
    int __pad1;
    int cmsg_level;
    int cmsg_type;
};

#elif WORDSIZE == 64 && __BYTE_ORDER == __BIG_ENDIAN

struct msghdr {
    void *msg_name;
    socklen_t msg_namelen;
    struct iovec *msg_iov;
    int __pad1, msg_iovlen;
    void *msg_control;
    int __pad2;
    socklen_t msg_controllen;
    int msg_flags;
};

struct cmsghdr {
    int __pad1;
    socklen_t cmsg_len;
    int cmsg_level;
    int cmsg_type;
};

#else
#  error "Unsupported architecture data-model"
#endif
