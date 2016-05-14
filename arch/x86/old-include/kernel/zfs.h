#ifndef __ZFS_H
#define __ZFS_H
#define TYPE_DEV 0
#define TYPE_DIR 1
#define TYPE_FILE 2
#define OP_READ 0x00
#define OP_WRITE 0x01
#include <stdint.h>
struct file_struct{
	uint32_t startingblock;
	uint32_t endingblock;
	uint32_t offset;
	uint32_t posx;
	uint32_t posy;
	uint32_t pos;
	uint32_t endingpos;
	uint32_t blockpos;
	char *filename;
	uint32_t opperation;
	uint32_t tpos;
};
struct zfs_superblock{
	uint32_t allocblk;
	uint32_t unallocblk;
	uint32_t tblk;
	uint32_t dataresv;
	uint32_t rootfsblk;
	uint32_t numoff;
	uint32_t numofd;
	uint32_t fds;
};
struct data{
	uint32_t alloc;
	uint32_t islongname;
	uint32_t namelen;
	char *name;
	uint32_t type;
	uint32_t offset;
	uint32_t endingpos;
	uint32_t blockpos;
	uint32_t startingblock;
 	uint32_t endingblock;
};
#ifndef __KERNEL_BUILD
void write_fs(struct zfs_superblock *sblk);
#else
struct zfs_superblock *read_superblock(struct zfs_superblock *ret);
typedef FILE struct file_struct *;
struct file_struct *request_file(const char *filename,char *op);
struct data *ffind(const char *filename,struct zfs_superblock *sblk);

#endif
#endif
