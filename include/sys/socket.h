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

#ifndef _SYS_SOCKET_H
#define _SYS_SOCKET_H 1

#include <bits/cdefs.h>
#include <bits/types.h>
#include <stdint.h>
// #include <sys/uio.h>

__STDC_GUARD

typedef __socklen_t socklen_t;

struct sockaddr {
    short sin_family;
    char sin_addr[14];
};

// IPv4 Socket address
struct in_addr {
    union {
        struct {
            unsigned char s_b1, s_b2, s_b3, s_b4;
        } S_un_b;
        struct {
            unsigned short s_w1, s_w2;
        } S_un_w;
        unsigned long S_addr;
    } S_un;
#define s_addr  S_un.S_addr /* can be used for most tcp & ip code */
#define s_host  S_un.S_un_b.s_b2    // host on imp
#define s_net   S_un.S_un_b.s_b1    // network
#define s_imp   S_un.S_un_w.s_w2    // imp
#define s_impno S_un.S_un_b.s_b4    // imp #
#define s_lh    S_un.S_un_b.s_b3    // logical host
};

struct sockaddr_in {
    short sin_family;
    unsigned short sin_port;
    struct in_addr sin_addr;
    char sin_zero[8];
};


// Definitions of bits in internet IPv4 address.
#define IN_CLASSA(i)  (((long)(i) & 0x80000000) == 0)
#define IN_CLASSA_NET  0xff000000
#define IN_CLASSA_NSHIFT  24
#define IN_CLASSA_HOST  0x00ffffff
#define IN_CLASSA_MAX  128

#define IN_CLASSB(i)  (((long)(i) & 0xc0000000) == 0x80000000)
#define IN_CLASSB_NET  0xffff0000
#define IN_CLASSB_NSHIFT  16
#define IN_CLASSB_HOST  0x0000ffff
#define IN_CLASSB_MAX  65536

#define IN_CLASSC(i)  (((long)(i) & 0xe0000000) == 0xc0000000)
#define IN_CLASSC_NET  0xffffff00
#define IN_CLASSC_NSHIFT  8
#define IN_CLASSC_HOST  0x000000ff

#define IN_CLASSD(i)  (((long)(i) & 0xf0000000) == 0xe0000000)
#define IN_CLASSD_NET  0xf0000000
#define IN_CLASSD_NSHIFT  28
#define IN_CLASSD_HOST  0x0fffffff
#define IN_MULTICAST(i)  IN_CLASSD(i)

#define INADDR_ANY  0x00000000UL
#define INADDR_LOOPBACK  0x7f000001UL
#define INADDR_BROADCAST  0xffffffffUL
#define INADDR_NONE  0xffffffffUL



// struct sockaddr_storage
// struct msghdr
// struct iovec  => <sys/uio.h>
// struct cmsghdr
// struct linger
// SCM_RIGHTS
// CMSG_DATA(cmsg)
// CMSG_NXTHDR(mhdr,cmsg)
// CMSG_FIRSTHDR(mhdr)

#define INVALID_SOCKET  (SOCKET)(~0)
#define SOCKET_ERROR            (-1)



#define SOCK_STREAM     1               /* stream socket */
#define SOCK_DGRAM      2               /* datagram socket */
#define SOCK_RAW        3               /* raw-protocol interface */
#define SOCK_RDM        4               /* reliably-delivered message */
#define SOCK_SEQPACKET  5               /* sequenced packet stream */


#define SOL_SOCKET      0xffff          /* options for socket level */

#define SO_DEBUG        0x0001          /* turn on debugging info recording */
#define SO_ACCEPTCONN   0x0002          /* socket has had listen() */
#define SO_REUSEADDR    0x0004          /* allow local address reuse */
#define SO_KEEPALIVE    0x0008          /* keep connections alive */
#define SO_DONTROUTE    0x0010          /* just use interface addresses */
#define SO_BROADCAST    0x0020          /* permit sending of broadcast msgs */
#define SO_USELOOPBACK  0x0040          /* bypass hardware when possible */
#define SO_LINGER       0x0080          /* linger on close if data present */
#define SO_OOBINLINE    0x0100          /* leave received OOB data in line */

#define SO_DONTLINGER   (int)(~SO_LINGER)
#define SO_EXCLUSIVEADDRUSE ((int)(~SO_REUSEADDR)) /* disallow local address reuse */

#define SO_SNDBUF       0x1001          /* send buffer size */
#define SO_RCVBUF       0x1002          /* receive buffer size */
#define SO_SNDLOWAT     0x1003          /* send low-water mark */
#define SO_RCVLOWAT     0x1004          /* receive low-water mark */
#define SO_SNDTIMEO     0x1005          /* send timeout */
#define SO_RCVTIMEO     0x1006          /* receive timeout */
#define SO_ERROR        0x1007          /* get error status and clear */
#define SO_TYPE         0x1008          /* get socket type */


// The maximum backlog queue length.
#define SOMAXCONN       0x7fffffff


#define AF_UNSPEC       0               // unspecified
#define AF_UNIX         1               // local to host (pipes, portals)
#define AF_INET         2               // internetwork: UDP, TCP, etc.
// #define AF_IMPLINK      3               // arpanet imp addresses
// #define AF_PUP          4               // pup protocols: e.g. BSP
// #define AF_CHAOS        5               // mit CHAOS protocols
// #define AF_NS           6               // XEROX NS protocols
// #define AF_IPX          AF_NS           // IPX protocols: IPX, SPX, etc.
// #define AF_ISO          7               // ISO protocols
// #define AF_OSI          AF_ISO          // OSI is ISO
// #define AF_ECMA         8               // european computer manufacturers
// #define AF_DATAKIT      9               // datakit protocols
// #define AF_CCITT        10              // CCITT protocols, X.25 etc
// #define AF_SNA          11              // IBM SNA
// #define AF_DECnet       12              // DECnet
// #define AF_DLI          13              // Direct data link interface
// #define AF_LAT          14              // LAT
// #define AF_HYLINK       15              // NSC Hyperchannel
// #define AF_APPLETALK    16              // AppleTalk
// #define AF_NETBIOS      17              // NetBios-style addresses
// #define AF_VOICEVIEW    18              // VoiceView
// #define AF_FIREFOX      19              // Protocols from Firefox
// #define AF_UNKNOWN1     20              // Somebody is using this!
// #define AF_BAN          21              // Banyan
// #define AF_ATM          22              // Native ATM Services
// #define AF_INET6        23              // Internetwork Version 6
// #define AF_CLUSTER      24              // Microsoft Wolfpack
// #define AF_12844        25              // IEEE 1284.4 WG AF
// #define AF_IRDA         26              // IrDA
// #define AF_NETDES       28              // Network Designers OSI & gateway



struct msghdr {
    void *msg_name; /* Optional address */
    socklen_t msg_namelen; /* Size of address */
    struct iovec *msg_iov; /* Scatter/gather array */
    size_t msg_iovlen; /* # elements in msg_iov */
    void *msg_control; /* Ancillary data, see below */
    size_t msg_controllen; /* Ancillary data buffer len */
    int msg_flags; /* Flags on received message */
};


int accept(int, struct sockaddr *restrict, socklen_t *restrict);
int bind(int, const struct sockaddr *, socklen_t);
int connect(int, const struct sockaddr *, socklen_t);
int getpeername(int, struct sockaddr *restrict, socklen_t *restrict);
int getsockname(int, struct sockaddr *restrict, socklen_t *restrict);
int getsockopt(int, int, int, void *restrict, socklen_t *restrict);
int listen(int, int);
__ssize_t recv(int, void *, size_t, int);
__ssize_t recvfrom(int, void *restrict, size_t, int, struct sockaddr *restrict, socklen_t *restrict);
__ssize_t recvmsg(int, struct msghdr *, int);
__ssize_t send(int, const void *, size_t, int);
__ssize_t sendmsg(int, const struct msghdr *, int);
__ssize_t sendto(int, const void *, size_t, int, const struct sockaddr *, socklen_t);
int setsockopt(int, int, int, const void *, socklen_t);
int shutdown(int, int);
int sockatmark(int);
int socket(int, int, int);
int socketpair(int, int, int, int [2]);

int open_socket(int, struct sockaddr *, socklen_t);


uint32_t htonl(uint32_t hostlong);
uint16_t htons(uint16_t hostshort);
uint32_t ntohl(uint32_t netlong);
uint16_t ntohs(uint16_t netshort);


typedef enum {
    NPROTO_TCP           = 1, // Ipv4 TCP
    NPROTO_UDP           = 2, // Ipv4 UDP
};

__STDC_END

#endif  /* _SYS_SOCKET_H */
