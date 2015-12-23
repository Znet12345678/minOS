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
	int isdir;
	int isfile;
	int foff;
	int doff;
};
struct dir{
	char *dirname;
	int num_of_files;
};
struct file{
	char *filename;
	char *contents;
};
#endif
