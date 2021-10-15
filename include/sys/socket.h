
#ifndef _SYS_SOCKET_H
#define _SYS_SOCKET_H 1

#include <bits/cdefs.h>
#include <bits/types.h>
// #include <sys/uio.h>

__STDC_GUARD

typedef __socklen_t socklen_t;
typedef unsigned sa_family_t;

struct sockaddr {
    unsigned short sa_family;
    unsigned short sa_port;
    char sa_data[12];
};

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




int accept(int, struct sockaddr *restrict, socklen_t *restrict);
int bind(int, const struct sockaddr *, socklen_t);
int connect(int, const struct sockaddr *, socklen_t);
int getpeername(int, struct sockaddr *restrict, socklen_t *restrict);
int getsockname(int, struct sockaddr *restrict, socklen_t *restrict);
int getsockopt(int, int, int, void *restrict, socklen_t *restrict);
int listen(int, int);
ssize_t recv(int, void *, size_t, int);
ssize_t recvfrom(int, void *restrict, size_t, int, struct sockaddr *restrict, socklen_t *restrict);
ssize_t recvmsg(int, struct msghdr *, int);
ssize_t send(int, const void *, size_t, int);
ssize_t sendmsg(int, const struct msghdr *, int);
ssize_t sendto(int, const void *, size_t, int, const struct sockaddr *, socklen_t);
int setsockopt(int, int, int, const void *, socklen_t);
int shutdown(int, int);
int sockatmark(int);
int socket(int, int, int);
int socketpair(int, int, int, int [2]);

int open_socket(int, struct sockaddr *, socklen_t);

typedef enum {
    NPROTO_TCP           = 1, // Ipv4 TCP
    NPROTO_UDP           = 2, // Ipv4 UDP
};

__STDC_END

#endif  /* _SYS_SOCKET_H */
