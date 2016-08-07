#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "zfs.h"
int __K_ZFS_WRITE_BLK(int lba,struct __ZFS_BLK *blk){
	char wr[1024] = {blk->alloc,blk->type};
	//kprintf("%c\n",wr[0] + '0');
	if(ata_write_master(wr,lba) < 0)
		return -1;
	return 1;
}
int __K_ZFS_CREATE_FS(){
	int lba = 2;
	char data[11] = {1,0xff,'z',0xff,'f',0xff,'s',0xff,1,5};
	ata_write_master_n(data,2,11);
	struct __ZFS_BLK blk;
	blk.alloc = 1;
	blk.type = BLK_TYPE_INF;
	if(__K_ZFS_WRITE_BLK(5,&blk) != 1){
		debug("ZFS","Couldn't make file system,panicing!");
		return -1;
	}
	debug("ZFS","Done");
	return 1;
}
