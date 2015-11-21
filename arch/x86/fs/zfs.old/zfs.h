#ifndef __ZFS_H
#define __ZFS_H
#define ENDFS 0xFE
struct zfs_file{
	char *sig;
	char *path;
	char *cont;
	unsigned long len;
}
struct zfs_dir{
	char *sig;
	int path_len;
	char *path;
	char *cont;
	unsigned long len;
	struct zfs_file *files;
};
const unsigned char root_sig[] = {0xFF,0x01,0x11,0x21,0x31,0x41,0x51,0x61,0x71,0x81,0x91,0xA1,0xB1,0xC1,0xD1,0xE1,0xF1};
const unsigned char dev_sig[] = {0xFF,0xAA,0x01};
const unsigned char dir_sig = 0xFF;
const unsigned char f_sig[] = {0xFF,0xAA};
struct zfs_block{
	struct block *next;
	char *rcont;
	struct zfs_dir *dirs;
}block;
struct superblock{
	struct block *blk;
	struct zfs_dirs *dirs;
	char *rfs;
};
void assemble_fs();
void mount_zfs();
#endif
