

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




