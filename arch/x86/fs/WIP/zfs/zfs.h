#ifndef __ZFS_H
#define __ZFS_H
#define TYPE_DEV 0
#define TYPE_DIR 1
#define TYPE_FILE 2
#define OP_READ 0x00
#define OP_WRITE 0x01
struct file_struct{
	int startingblock;
	int endingblock;
	int offset;
	int posx;
	int posy;
	char *filename;
	int opperation;
};
struct zfs_superblock{
	unsigned int allocblk;
	unsigned int unallocblk;
	unsigned int tblk;
	unsigned int dataresv;
	unsigned int rootfsblk;
	unsigned int numoff;
	unsigned int numofd;
	unsigned int fds;
};
struct data{
	int islongname;
	int namelen;
	char *name;
	int type;
	int startingblock;
 	int endingblock;
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
