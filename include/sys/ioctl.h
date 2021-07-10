#ifndef __SYS_IOCTL_H
#define __SYS_IOCTL_H 1

#include <bits/cdefs.h>
#include <bits/ioctl.h>

__STDC_GUARD

int ioctl(int fd, unsigned long int request, ...);

__STDC_END

#endif  /* __SYS_IOCTL_H */
