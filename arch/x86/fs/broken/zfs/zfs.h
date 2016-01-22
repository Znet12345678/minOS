#ifndef __ZFS_H
#define __ZFS_H
#include <stdint.h>
struct zfs_blk{
	int bytes[512];
	int freebytes;
	int used;
};
struct zfs_rootblk{
	int sig;
	int offset;
	int pos;
};
struct zfs_supblk{
	struct zfs_blk *blks;
	struct zfs_rootblk rblk;
};
int zfs_scan(int force);
int zfs_scanend(uint16_t drive,int offset);
int zfs_mount(int offset,int end);
int zfs_as();
#define ROOTSIG 0x26,0x01,0x03,0x08
#define ENDSIG  0xFF,0xAA,0x00
#endif

