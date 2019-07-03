#ifndef __SYS_IOCTL_H
#define __SYS_IOCTL_H 1

#include <bits/cdefs.h>
// #include <bits/ioctl.h>
// kernel ioctl

struct winsize {
    unsigned short int ws_row;
    unsigned short int ws_col;
    unsigned short int ws_xpixel;
    unsigned short int ws_ypixel;
};


struct termio {
    unsigned short int c_iflag;
    unsigned short int c_oflag;
    unsigned short int c_cflag;
    unsigned short int c_lflag;
    unsigned char c_line;
    unsigned char c_cc[8];
};


int ioctl(int fd, unsigned long int request, ...);

#endif  /* __SYS_IOCTL_H */
