#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ata.h>
#include "zfs.h"
struct zfs_superblock *read_superblock(struct zfs_superblock *ret){
	char *buf = malloc(1024);
	ata_read_master(buf,2,0);
	ret->allocblk = buf[0] << 16 | buf[1] << 8 | buf[2];
	ret->unallocblk = buf[3] << 16 | buf[4] << 8 | buf[5];
	ret->tblk = buf[6] << 16 | buf[7] << 8 | buf[9];
	ret->dataresv = buf[10] << 8 | buf[11];
	ret->rootfsblk = buf[12] << 8 | buf[13];
	ret->numoff = buf[14] << 16 | buf[15] << 16 | buf[16] << 8 | buf[17];
	ret->numofd = buf[18] << 16 | buf[19] << 16 | buf[20] << 8 | buf[21];
	ret->fds = buf[22] << 8 | buf[23];
	return ret;
}
struct file_struct *request_file(const char *filename,char *op){
	struct file_struct *ret;
	if(strcmp(op,"r") == 0){
		ret->posx = 0;
		ret->posy = 0;
		ret->filename = filename;
		ret->opperation = OP_READ;
		struct zfs_superblock *sblk = malloc(1024);
		read_superblock(sblk);
		int i = 0;
		int j = sblk->fds;
		int n = sblk->dataresv;
		while(i < n){
			char *buf = malloc(1024);
			ata_read_master(buf,j,0);
			struct data *data = malloc(1024);
			int k = 0;
			int a = 0;
			int b = 30;
			while(k < b){
				data->islongname = buf[a * k];
				if(data->islongname && strlen(filename) > 10){
					data->namelen = buf[a * k + 1];
					b-=(data->namelen / 10);
					data->name = malloc(1024);
					int c;
					for( c = 0; c < data->namelen;c++){
						data->name[c] = buf[a * k + 2 + c];
					}
					if(strcmp(data->name,filename) == 0){
						ret->offset = a * k + 2 + c;
						ret->startingblock = buf[a * k  + c + 3] << 16 | buf[a * k + c + 4] << 8 | buf[a * k + c + 5];
						ret->endingblock = buf[a * k + c + 6] << 16 | buf[a * k + c + 7] << 8 | buf[a * k + c + 8];
					}

				}
				else if(strlen(filename) < 10 && data->islongname){
					a++;k++;
					continue;
				}
				a++;
				k++;
			}
			i++;j++;
		}
	}
}
