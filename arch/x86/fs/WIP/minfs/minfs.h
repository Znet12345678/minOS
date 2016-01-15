#ifndef ___MINFS_H
#define ___MINFS_H
#define TERMINATE 0x1F
#define SUPERBLKTERMINATE 0x00
struct minfs_superblock{
	int blocksize;
	int starting_block;
	int starting_inode;
};
struct miscblk{
	int numofallocdblocks;
	int numoffiles;
	int *fpnt;
	int i;
	int *dpnt;
	int _i;
	char **names;
	char **_names;
};
struct inode{
	char *sig;
	int isalloc;
	char *fname;
	char *dirname;
	int islong;
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
struct FILE{
	char *filename;
	char *contents;
	int offset;
	int lba;
	int b_len;
};
int mount_p1(char *buf,int drive,struct minfs_superblock *superblk);
#define F_READ 0x00
#define F_WRITE 0x01
#define F_APPEND 0x02
#endif
