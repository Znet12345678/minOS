// // inffs.h // // // Created by Zach Schlotman on 4/27/16. // //

#ifndef ____inffs__
#define ____inffs__

#include <stdio.h>
#define __INFFS_FOPP_READ 0
#define __INFFS_FOPP_WRITE 1
struct __INFFS_SUPERBLK{
    char *sig;//10 bytes
    int ninfblk;//4 bytes
    char inf_start_lba;//1 byte
    int inf_end_lba;//4 bytes
    int fs_size;//4 bytes
};
struct __INFFS_INFOBLK{
    int isalloc;
    int len;
    int blk;
    int sizeinblocks;
    int namelen;
    char name[80];
    int dent_pntr;
};
struct __INFFS_DIRENT{
    int isalloc;
    int sizeinbytes;
    int nof;
    int namelen;
    char name[80];
    int sizeofb;
    int sizeoff;
    int	file_pntr[80];
    int _sizeofb;
    int _sizeoff;
    int infblk_pntr[80];
};
struct __INFFS_FILE{
    //Set on file system
    char name[80];
    int isalloc;
    int sig;
    int fsize;
    int start_lba;
    int end_lba;
    int endingval;
    //End Set on file system
    //Set by a function
    int pos;
    int opperation;
    int blkpos;
    int _blkpos;
};
struct __INFFS_BLKDEV{
    int IO_BASE;
    int starting_lba;
};
struct inffs_path{
	char dir[1024];
	char name[80];
};
struct __INFFS_FILE *__INFFS_FULLDISK_FS_FOPEN(const char *path,int opperation,struct __INFFS_FILE *ret);
int __INFFS_MKFS_FULLDISK();
int __INFFS_FULLDISK_FS_FREAD(struct __INFFS_FILE *file,int *buf,int n);
int __INFFS_FULLDISK_FS_FWRITE(struct __INFFS_FILE *file,uint8_t *buf,int n);
int __IS_INFFS();
#endif /* defined(____inffs__) */
