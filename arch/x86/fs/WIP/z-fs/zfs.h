/*
*z-fs header
*Public domain
*/
#ifndef __Z_FS_H
#define __Z_FS_H
#define __FS_T_Z_FS 0
#define __FS_T_ZFS 1
#define __FS_T_INFFS 2
#define __FS_UNKNOWN -1
#define __VERSION 1
struct __Z_FS_SUPERBLK{
	int version;
	int sig[2];//0x0f 0x1f
	int first_dent_blk;
	int first_infblk;
};
struct __Z_FS_DENTBLK{
	int alloc;
	//data
	int is_end_of_dir;
	int next_dent_offset;
	int next_dent_lba;
};
struct __ZFS_DENT{
	int size;
	char dirname[30];
	char filename[20];
	int file_inf_lba;
	int file_inf_offset;
};
struct __Z_FS_INF{
	int alloc;
	char name[20];
	char containing_dname[30];
	int datablk_start;
	int next_inf_offset;
	int next_inf_lba;
};
struct __Z_FS_DATABLK{
	int alloc;
	//data
	int is_last;
	int next_data_blk;
};
struct __FILE{
	struct __Z_FS_INF *inf;
	int pos;
	int opperation;
	int currlba;
	int nextlba;
};
#ifdef KBUILD
struct __Z_FS_SUPERBLK *__parse_superblock();
struct __Z_FS_DENT *read_dent(const char *name);
struct __Z_FS_INF *read_inf(const char *name,const char *dir);
int write_datablk(struct __Z_FS_DATABLK *dblk,char *data);
struct __FILE *__fopen(const char *fname,const char *opperation);
int __MKFS();
int __DETFS();
#endif
#endif
