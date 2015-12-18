#ifndef ___MINFS_H
#define ___MINFS_H
struct minfs_superblock{
	unsigned long blocksize;
	unsigned long starting_block;
	unsigned long starting_inode;
};
struct inode{
	int numofdirs;
	int numoffiles;
	int dirpnt;
};
struct block{
	struct file **fptr;
	struct dir **dptr;
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
