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
#ifndef _SYS_VFS_H
#define _SYS_VFS_H 1

#include <bits/types.h>



struct statfs {
    unsigned short f_type; /* type of file system (see below) */
    unsigned short f_bsize; /* optimal transfer block size */
    __fsblkcnt_t f_blocks; /* total data blocks in file system */
    __fsblkcnt_t f_bfree; /* free blocks in fs */
    __fsblkcnt_t f_bavail; /* free blocks available to unprivileged user */
    __fsfilcnt_t f_files; /* total file nodes in file system */
    __fsfilcnt_t f_ffree; /* free file nodes in fs */
    __fsid_t f_fsid; /* file system id */
    unsigned short f_namelen; /* maximum length of filenames */
    unsigned short f_frsize; /* fragment size (since Linux 2.6) */
    unsigned short f_spare[5];
};


#define ADFS_SUPER_MAGIC 0xadf5
#define AFFS_SUPER_MAGIC 0xADFF
#define BEFS_SUPER_MAGIC 0x42465331
#define BFS_MAGIC 0x1BADFACE
#define CIFS_MAGIC_NUMBER 0xFF534D42
#define CODA_SUPER_MAGIC 0x73757245
#define COH_SUPER_MAGIC 0x012FF7B7
#define CRAMFS_MAGIC 0x28cd3d45
#define DEVFS_SUPER_MAGIC 0x1373
#define EFS_SUPER_MAGIC 0x00414A53
#define EXT_SUPER_MAGIC 0x137D
#define EXT2_OLD_SUPER_MAGIC 0xEF51
#define EXT2_SUPER_MAGIC 0xEF53
#define EXT3_SUPER_MAGIC 0xEF53
#define EXT4_SUPER_MAGIC 0xEF53
#define HFS_SUPER_MAGIC 0x4244
#define HPFS_SUPER_MAGIC 0xF995E849
#define HUGETLBFS_MAGIC 0x958458f6
#define ISOFS_SUPER_MAGIC 0x9660
#define JFFS2_SUPER_MAGIC 0x72b6
#define JFS_SUPER_MAGIC 0x3153464a
#define MINIX_SUPER_MAGIC 0x137F /* orig. minix */
#define MINIX_SUPER_MAGIC2 0x138F /* 30 char minix */
#define MINIX2_SUPER_MAGIC 0x2468 /* minix V2 */
#define MINIX2_SUPER_MAGIC2 0x2478 /* minix V2, 30 char names */
#define MSDOS_SUPER_MAGIC 0x4d44
#define NCP_SUPER_MAGIC 0x564c
#define NFS_SUPER_MAGIC 0x6969
#define NTFS_SB_MAGIC 0x5346544e
#define OPENPROM_SUPER_MAGIC 0x9fa1
#define PROC_SUPER_MAGIC 0x9fa0
#define QNX4_SUPER_MAGIC 0x002f
#define REISERFS_SUPER_MAGIC 0x52654973
#define ROMFS_MAGIC 0x7275
#define SMB_SUPER_MAGIC 0x517B
#define SYSV2_SUPER_MAGIC 0x012FF7B6
#define SYSV4_SUPER_MAGIC 0x012FF7B5
#define TMPFS_MAGIC 0x01021994
#define UDF_SUPER_MAGIC 0x15013346
#define UFS_MAGIC 0x00011954
#define USBDEVICE_SUPER_MAGIC 0x9fa2
#define VXFS_SUPER_MAGIC 0xa501FCF5
#define XENIX_SUPER_MAGIC 0x012FF7B4
#define XFS_SUPER_MAGIC 0x58465342
#define _XIAFS_SUPER_MAGIC 0x012FD16D


int statfs(const char *path, struct statfs *buf);
int fstatfs(int fd, struct statfs *buf);


#endif /* _SYS_VFS_H */
