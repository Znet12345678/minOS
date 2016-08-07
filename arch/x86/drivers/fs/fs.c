#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ata.h>
#include <string.h>
#include "drv_fs.h"
int detfs(){
	char buf[1024];
	ata_read_master(buf,2,0);
	int alloc = buf[0];
	if(alloc){
		char _buf[8];
		for(int i = 1; i < 8;i++)
			_buf[i - 1] = buf[i];
	        char __ZFS_SIG[8] = {0xff,'z',0xff,'f',0xff,'s',0xff};
		//kprintf("%s\n",__ZFS_SIG);
		if(strcmp(_buf,__ZFS_SIG) == 0)
			return 2;
		return -1;
	}
	ata_read_master(buf,5,0);
	char inffs_sig[] = {'I',0x0f,'N',0x0f,'F',0x0f,'F',0x0f,'S',0x0f};

	if(strncmp(buf,inffs_sig,strlen(inffs_sig)) == 0)
		return 1;
	return -1;
}
