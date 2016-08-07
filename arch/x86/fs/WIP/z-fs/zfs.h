/*
*Znet file system driver for minOS kernel
*(c) 2016 Zachary James Schlotman
*/
#ifndef __ZFS_H
#define __ZFS_H
int __ZFS_SIG[] = {0xff,'z',0xff,'f',0xff,'s',0xff};
struct __ZFS_SUPERBLK{
	int alloc;
	int sig[7];
	int fs_type;
	int first_infblk;
};
#define TYPE_DIR 0xff /*Directory*/
#define TYPE_FILE 0xaa /*File*/
#define TYPE_DEVICE 0x4a /*Device file*/
#define F_TYPE_TXT 0x00 /*Text*/
#define F_TYPE_EXEC 0x80 /*Executable*/
#define BLK_TYPE_REG 0x10 /*Regular block*/
#define BLK_TYPE_INF 0x8a /*Info block*/
struct __ZFS_BLK{
	int alloc;
	int type;
};
struct __ZFS_INF{
	int type;
	//FILE ATRIBUTES (0 if directory)
	int f_type;
	//DIRECTORY
	int dent_pntr;
	//SHARED
	int size;
	char name[80];
	int lba_start;
	int lba_end;
	int next_infoblk;
};
struct __ZFS_DIRENT{
	int numoffiles;
	int numofdirectories;
	int start;
	int end;
};
#define OP_WR 0x00
#define OP_RD 0x20
#define OP_DT 0x40
#define OP_APND 0x80
struct __ZFS_FILE{
	char name[80];
	int operation;
	int lba_start;
	int lba_end;
	int sizeinbytes;
	int end_offset;
	int begin_offset;
};
struct __ZFS_FILE *__ZFS_FOPEN(const char *name,int op);
int update_dir(int arga,int argb,char *dir_name);
#ifdef KERNBUILD
/*
*returns:
*1 on success
*<0 on fail
*Creates whole disk file system
*/
int __K_ZFS_CREATE_FS();
/*
*returns:
*1 on success
*<0 on failure
*WIPES ALL DATA ON BLOCK
*Initializes block
*/
int __K_ZFS_WRITE_BLK(int lba,struct __ZFS_BLK *blk);
/*
*returns:
*0 for unalloc
*1 for regular
*2 for info
*reads block info
*/
int __K_ZFS_GETBLK_INF(int lba);
#endif
#endif
