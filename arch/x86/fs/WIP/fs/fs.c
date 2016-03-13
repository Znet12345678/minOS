#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "fs.h"
struct superblk *nfs_parse_superblk(struct superblk *ret){
	char *buf = malloc(1024);
	ata_read_master(buf,2,0);
	ret->sblksize = buf[0] << 8 | buf[1];
	ret->numf = buf[2] << 16 | buf[3] << 8 | buf[4];
	ret->numd = buf[5] << 16 | buf[6] << 7 | buf[7];
	ret->rootblk = buf[8] << 8 | buf[9];
	ret->numofallocatedblocks = buf[10] << 16 | buf[11] << 8 | buf[12];
	ret->numofunallocatedblocks = buf[13] << 16 | buf[14]  << 8 | buf[15];
	ret->numofblocks = buf[16] << 16 | buf[17] << 8 | buf[18];
	ret->infos = buf[19] << 16 | buf[20] << 8 | buf[21];
	ret->infoe = buf[22] << 16 | buf[23] << 8 | buf[24];
	return ret;	
}
struct inode *parse_inode(struct superblk *blk,int inum,struct inode *ret){
	char *buf = malloc(1024);
	ata_read_master(buf,blk->rootblk + inum,0);
	ret->type = buf[0];
	if(buf[0] == 0)
		return ret;
	char name[8] = {0};	
	for(int i = 0; i < 8;i++){
		name[i] = buf[i + 1];
	}
	ret->name = name;
	int infoblock; 
	infoblock = buf[9] << 16 | buf[10] << 8| buf[11];
	ret->infoblock = infoblock;
	int *info = malloc(512);
	for(int i = 0; i < 501;i++){
		info[i] = buf[i + 12];
	}
	ret->cont = info;
	return ret;
}
struct info * parse_info(const char *filename,struct superblk *sblk){
	struct info *ret;
	for(int i = sblk->infos;i < sblk->infoe;i++){
		char *buf = malloc(1024);
		ata_read_master(buf,i,0);
		for(int j = 0; j < 32;j++){
			ret->type = buf[j * 16];
			if(ret->type == TYPE_UNALLOC)
				continue;
			else if(ret->type == TYPE_DIR){
				ret->is_long_name = buf[j * 16 + 1];
				if(ret->is_long_name && strlen(filename) > 8){
					ret->namepntr = buf[j * 16 + 2] << 16 | buf[j * 16 + 3] << 8 | buf[j * 16 + 4];
					ret->nameblk = buf[j * 16 + 5] << 16 | buf[j * 16 + 6] << 8 | buf[j * 16 + 7];
					ret->namelen = buf[j * 16 + 8] << 8 | buf[j * 16 + 9];
					ret->name = malloc(1024);
					char *namebuf = malloc(513);
					ata_read_master(namebuf,ret->nameblk,0);
					for(int k = ret->namepntr; k < ret->namepntr + ret->namelen;k++){
						kstrcat(ret->name,&namebuf[k]);
					}
					if(strcmp(ret->name,filename) == 0){
						ret->len = buf[j * 16 + 10] << 16 | buf [j * 16 + 11] << 8 | buf[j * 16 + 12];
						ret->inode_offset = buf[j * 16 + 13] << 16 | buf[ j * 16 + 14] << 8 | buf[j * 16 + 15];
						return ret;
					}
					continue;
				}
				else if(strlen(filename) <= 8 && ret->is_long_name == 0){
					ret->name = malloc(1024);
					for(int k = 0; k < 8;k++){
						kstrcat(ret->name,&buf[j * 16 + 2 + k]);
					}
					if(strcmp(ret->name,filename) == 0){
						ret->len = buf[j * 16 + 10] << 16 | buf [j * 16 + 11] << 8 | buf[j * 16 + 12]; 
                                                ret->inode_offset = buf[j * 16 + 13] << 16 | buf[ j * 16 + 14] << 8 | buf[j * 16 + 15];
                                                return ret;
					}
					continue;
				}
				else
					continue;
			}
			else if(ret->type == TYPE_FILE){
				ret->is_long_name = buf[j * 16 + 1];
				if(ret->is_long_name && strlen(filename) > 8){
					
				}
			}
		}
	}
}
