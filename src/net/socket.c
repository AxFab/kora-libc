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
#include <sys/socket.h>
#include <endian.h>

int socket(int family, int stream, int protocol)
{
    return -1;
}

__ssize_t recvfrom(int sock, void *restrict buf, size_t len, int flags, struct sockaddr *restrict addr, socklen_t *restrict alen)
{
    return -1;
}

__ssize_t sendto(int sock, const void * buf, size_t len, int flags, const struct sockaddr * addr, socklen_t alen)
{
    return -1;
}

// int accept(int, struct sockaddr *restrict, socklen_t *restrict);
// int bind(int, const struct sockaddr *, socklen_t);
// int connect(int, const struct sockaddr *, socklen_t);
// int getpeername(int, struct sockaddr *restrict, socklen_t *restrict);
// int getsockname(int, struct sockaddr *restrict, socklen_t *restrict);
// int getsockopt(int, int, int, void *restrict, socklen_t *restrict);
// int listen(int, int);
// __ssize_t recv(int, void *, size_t, int);
// __ssize_t recvmsg(int, struct msghdr *, int);
// __ssize_t send(int, const void *, size_t, int);
// __ssize_t sendmsg(int, const struct msghdr *, int);
// int setsockopt(int, int, int, const void *, socklen_t);
// int shutdown(int, int);
// int sockatmark(int);
// int socketpair(int, int, int, int [2]);

// int open_socket(int, struct sockaddr *, socklen_t);


uint32_t htonl(uint32_t hostlong)
{
#if __BYTE_ORDER == __LITTLE_ENDIAN
    return __bswap32(hostlong);
#else
    return hostlong;
#endif
}

uint16_t htons(uint16_t hostshort)
{
#if __BYTE_ORDER == __LITTLE_ENDIAN
    return __bswap16(hostshort);
#else
    return hostshort;
#endif
}

uint32_t ntohl(uint32_t netlong)
{
#if __BYTE_ORDER == __LITTLE_ENDIAN
    return __bswap32(netlong);
#else
    return netlong;
#endif
}

uint16_t ntohs(uint16_t netshort)
{
#if __BYTE_ORDER == __LITTLE_ENDIAN
    return __bswap16(netshort);
#else
    return netshort;
#endif
}
