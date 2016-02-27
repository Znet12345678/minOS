#ifndef __FS_H
#define __FS_H
#include <kernel/kbuf.h>
#define TYPE_UNALLOC 0
#define TYPE_DIR 1
#define TYPE_FILE 2
struct superblk{
	int sblksize;
	int numf;
	int numd;
	int rootblk;
	int numofallocatedblocks;
	int numofunallocatedblocks;
	int numofblocks;
	int infos;
	int infoe;
};
struct inode{
	int type;
	char *name;
	int infoblock;
	int *cont;	
};
struct info{
	int type;
	int is_long_name;
	int namepntr;
	int nameblk;
	int namelen;
	char *name;
	int len;
	int inode_offset;
};
struct dirent{
	int info_block;
	int num_cont;
	char **cont;
};
struct FILE{
	char *opp;
	int offset;
	char *name;
	int pos;
	int attr;
};
struct kbuf *mount(char *mountpoint,int flags);
struct superblk *parse_superblk(struct superblk *ret);
struct inode *parse_inode(struct superblk *sblk,int inum,struct inode *ret);
struct dirent *read_dir(char *name);
struct info *parse_info(const char *filename,struct superblk *sblk);
struct FILE *fopen(char *filename,const char *opp);
int fgets(char *buf,unsigned long len,struct FILE *f);
int fwrite(struct FILE *f,const char *buf);
int fgetc(char c,struct FILE f);

#endif
