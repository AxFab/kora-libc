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
#include <string.h>
#include <endian.h>

// Create an endpoint for communication
int socket(int domain, int type, int protocol)
{
    return -1;
}


// Bind a name to a socket
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
    return -1;
}


// Connect a socket with a single address.
int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
    return -1;
}


// send a message on a socket
__ssize_t sendmsg(int sockfd, const struct msghdr *msg, int flags)
{
    return -1;
}


// Receive a message from a socket
__ssize_t recvmsg(int sockfd, struct msghdr *msg, int flags)
{
    return -1;
}


// Accept a connection on a socket
int accept4(int sockfd, struct sockaddr *restrict addr, socklen_t *restrict addrlen, int flags)
{
    return -1;
}


// listen for connections on a socket
int listen(int sockfd, int backlog)
{
    return -1;
}


// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

// send a message on a socket
// send(.., 0) => write();
__ssize_t send(int sockfd, const void *buf, size_t len, int flags)
{
    struct iovec vc = { (void *)buf, len };
    struct msghdr hd;
    memset(&hd, 0, sizeof(hd));
    hd.msg_iov = &vc;
    hd.msg_iovlen = 1;
    return sendmsg(sockfd, &hd, flags);
}

__ssize_t sendto(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen)
{
    struct iovec vc = { (void *)buf, len };
    struct msghdr hd;
    memset(&hd, 0, sizeof(hd));
    hd.msg_name = (void *)dest_addr;
    hd.msg_namelen = addrlen;
    hd.msg_iov = &vc;
    hd.msg_iovlen = 1;
    return sendmsg(sockfd, &hd, flags);
}

// Receive a message from a socket
// recv(.., 0) => read();
__ssize_t recv(int sockfd, void *buf, size_t len, int flags)
{
    struct iovec vc = { buf, len };
    struct msghdr hd;
    memset(&hd, 0, sizeof(hd));
    hd.msg_iov = &vc;
    hd.msg_iovlen = 1;
    return recvmsg(sockfd, &hd, flags);
}

__ssize_t recvfrom(int sockfd, void *restrict buf, size_t len, int flags, struct sockaddr *restrict src_addr, socklen_t *restrict addrlen)
{
    struct iovec vc = { buf, len };
    struct msghdr hd;
    memset(&hd, 0, sizeof(hd));
    hd.msg_name = src_addr;
    hd.msg_namelen = addrlen ? *addrlen : 0;
    hd.msg_iov = &vc;
    hd.msg_iovlen = 1;
    return recvmsg(sockfd, &hd, flags);
}

// Accept a connection on a socket
int accept(int sockfd, struct sockaddr *restrict addr, socklen_t *restrict addrlen)
{
    return accept4(sockfd, addr, addrlen, 0);
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=



// int getpeername(int, struct sockaddr *restrict, socklen_t *restrict);
// int getsockname(int, struct sockaddr *restrict, socklen_t *restrict);
// int getsockopt(int, int, int, void *restrict, socklen_t *restrict);
// int setsockopt(int, int, int, const void *, socklen_t);
// int shutdown(int, int);
// int sockatmark(int);
// int socketpair(int, int, int, int [2]);

// int open_socket(int, struct sockaddr *, socklen_t);



// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

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

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

