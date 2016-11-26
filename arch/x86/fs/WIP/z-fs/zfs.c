#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include "zfs.h"
struct __Z_FS_SUPERBLK *__parse_superblock(){
	struct __Z_FS_SUPERBLK *ret = malloc(sizeof(struct __Z_FS_SUPERBLK *));
	char buf[513];
	ata_read_master(buf,2,0);
}
int __DETFS(){
	char buf[513];
	ata_read_master(buf,2,0);
	if(buf[0] == 1){
		if(buf[1] == 0x0f && buf[2] == 0x1f)
			return __FS_T_Z_FS;
		else
			return __FS_UNKNOWN;
	}
	return __FS_UNKNOWN;
}
int __MKFS(){
	int ret = 1;
	struct __Z_FS_SUPERBLK *sblk = malloc(sizeof(struct __Z_FS_SUPERBLK *));
	if(!(sblk))
		panic();
	sblk->version = __VERSION;
	char sig[] = {0x0f,0x1f};
	memcpy(sblk->sig,sig,2);
	sblk->first_dent_blk = 0;
	sblk->first_infblk = 0;
	int write[] = {sblk->version,sblk->sig[0],sblk->sig[1],sblk->first_dent_blk >> 8,sblk->first_dent_blk,sblk->first_infblk >> 8,sblk->first_infblk};
	ata_write_master_n(write,2,0);
	return ret;
}
