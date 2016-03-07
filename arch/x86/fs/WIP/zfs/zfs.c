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
	struct file_struct *ret = malloc(1024);
	int found = 0;
	if(strcmp(op,"r") == 0){
		ret->posx = 0;
		ret->posy = 0;
		ret->pos = 0;
		ret->filename = filename;
		ret->opperation = OP_READ;
		struct zfs_superblock *sblk = malloc(1024);
		read_superblock(sblk);
		int i = 0;
		int j = sblk->fds;
		int n = sblk->dataresv;
		//int found;
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
						found = 1;
						ret->offset = a * k + 2 + c;
						ret->startingblock = buf[a * k  + data->namelen + 3] << 16 | buf[a * k + data->namelen + 4] << 8 | buf[a * k + data->namelen + 5];
						ret->endingblock = buf[a * k + data->namelen + 6] << 16 | buf[a * k + data->namelen + 7] << 8 | buf[a * k + data->namelen + 8];
						ret->endingpos = buf[a * k + data->namelen + 10] << 8 | buf[a * k + data->namelen + 11];
						ret->blockpos = ret->startingblock;
						break;
					}


				}
				else if(strlen(filename) < 10 && data->islongname){
					a++;k++;
					continue;
				}
				else if(strlen(filename) < 10 && !(data->islongname)){
					data->name = malloc(1024);
					int c;
					for(c = 0; c < 10;c++){
						data->name[c] = buf[a * k + 2 + c];
					}
					if(strcmp(data->name,filename) == 0){
						found = 1;
						ret->offset = a * k + 12;
						ret->startingblock = buf[a * k + 13] << 16 | buf[a * k + 14] << 8 | buf[a * k + 15];
						ret->endingblock = buf[a * k + 16] << 16 | buf[a * k + 17] << 8 | buf[a * k + 18];
						ret->endingpos = buf[a * k + 19] << 8 | buf[a * k + 20];
						ret->blockpos = ret->startingblock;
						break;
					}
				}
				a++;
				k++;
			}
			i++;j++;
		}
	}
	if(found != 1){
		kprintf("Aborted:Couldn't find file\n");
		return -1;
	}
	/*char *fbuf = malloc(512 * (ret->endingblock - ret->startingblock));
	char *blk = malloc(1024);
	int d;
	int f = 0;
	for(d = ret->startingblock; d < ret->endingblock;d++){
		ata_read_master(blk,d,0);
		for(int e = 0; e < 512;e++,f++){
			fbuf[f] = blk[e];
		}
		blk = malloc(1024);
	}*/
	return ret;
}
int read(char *buf,struct file_struct *f,int n){
	int read = 0;
	char *blk = malloc(513);
	int d = 0;
	int _f = 0;
		/*if(f->endingpos == 512){
			for(d = f->startingblock; d < (f->endingblock + 1); d++){
				ata_read_master(blk,d,0);
				for(int e = 0; e < 512; e++,f++){
					buf[f] = blk[e];
				}
				f->pos+=512;
			}
			return ((f->endingblock - f->startingblock) * 512);
		}
		else{
			for(d = f->startingblock; d < (f->endingblock + 1); d++){
				ata_read_master(blk,d,0);
				if(d == f->endingblock){
					for(int g = 0; g < f->endingpos;g++,f++)
						buf[f] = blk[g];
					f->pos+=f->endingpos;
				}
				else{
					for(int g = 0; g < 512;g++,f++)
						buf[f] = blk[g]
					f->pos+=f->endingpos;
				}
			}
			return (((f->endingblock - f->startingblock) * 512) - f->endingpos);

		}*/
	if(f->endingpos == 512){
		for(int i = f->blockpos; i <= f->endingblock && read < n;i++){
			f->pos = 0;
			ata_read_master(blk,d,0);
			for(int j = f->pos; j < 512;j++,_f++){
				buf[_f] = blk[j];
				f->pos++;
				read++;
			}
				//f->pos = 0;
			f->blockpos++;
			blk = malloc(1024);
		}
	}
	else{
		for(int i = f->blockpos; i <=f->endingblock && read < n; i++){
			f->pos = 0;
			ata_read_master(blk,d,0);
			if(i == f->endingblock){
				for(int j = f->pos; j < f->endingpos;j++,_f++){
					buf[_f] = blk[j];
					read++;
					f->pos++;
				}
				return read;
			}
			else{
				for(int j = f->pos ; j < 512;j++,_f++){
					buf[_f] = blk[j];
					read++;
					f->pos++;
				}
				return read;
			}
			f->blockpos++;
		}
	}

}

