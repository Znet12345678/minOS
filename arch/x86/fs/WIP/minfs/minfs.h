#ifndef ___MINFS_H
#define ___MINFS_H
struct minfs_superblock{
	unsigned long blocksize;
	unsigned long starting_block;
	unsigned long starting_inode;
};
struct inode{
	char *sig;
	int numofdirs;
	int numoffiles;
	int dirpnt;
	int fpnt;
};
struct block{
	char *sig;
	char *cont;
	char *strip;
	char type;
	int isdir;
	int isfile;
	int isinfo;
	int isallocated;
	int foff;
	int doff;
	int ending_block;
	int infoblock;
	//Info blocks only
	int is_long;
	int lba_len;
	int blocks;
	char *containing_dir;
	int starting_lba;
	//only applicable for directories
	char *files;

};
struct dir{
	char *dirname;
	int num_of_files;
};
struct file{
	char *filename;
	char *contents;
};
int mount_p1(char *buf,int drive,struct minfs_superblock *superblk);
#endif
