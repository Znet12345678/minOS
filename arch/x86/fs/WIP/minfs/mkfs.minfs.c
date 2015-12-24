/*
*MinFS maker
*(c)2015 Zachary James Schlotman
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "minfs.h"
int get_end(char *file){
	FILE *f = fopen(file,"rb");
	fseek(f,0,SEEK_END);
	int ret = ftell(f);
	fclose(f);
	return ret;
}
int zero_out(char *file){
	int end = get_end(file);
	FILE *f = fopen(file,"wb");
	if(!(f))
		return -1;
	int i = 0;
	while(i < end){
		fputc(0x00,f);
		i++;
	}
	return 0;
}
int mkfs_minfs(struct minfs_superblock *sblk,struct inode *inode,char *output){
	zero_out(output);
	FILE *f = fopen(output,"wb");
	if(!(f))
		return -1;
//	zero_out(output);
	fseek(f,1024,SEEK_SET);
	char blksz[] = {sblk->blocksize / 100,sblk->blocksize % 100};
	fputc(blksz[0],f);
	fputc(blksz[1],f);
	if(sblk->starting_block < 10){
		fputc(0,f);
		fputc(0,f);
		fputc(sblk->starting_block,f);
	}
	else if(sblk->starting_block < 100){
		fputc(0,f);
		fputc(sblk->starting_block / 10,f);
		fputc(sblk->starting_block % 10,f);
	}
	else if(sblk->starting_block < 1000){
		fputc(sblk->starting_block / 100,f);
		fputc((sblk->starting_block % 100) / 10,f);
		fputc(sblk->starting_block % 10,f);
	}
	else{
		printf("Starting Block too large!\n");
		return -1;
	}
	if(sblk->starting_inode < 10){
		fputc(0,f);
		fputc(0,f);
		fputc(sblk->starting_inode,f);
	}
	else if(sblk->starting_inode < 100){
		fputc(0,f);
		fputc(sblk->starting_inode /10,f);
		fputc(sblk->starting_inode %10,f);
	}
	else if(sblk->starting_inode < 1000){
		fputc(sblk->starting_inode / 100,f);
		fputc((sblk->starting_inode % 100) / 10,f);
		fputc(sblk->starting_block % 10,f);
	}
	else{
		printf("Starting inode too large!\n");
		return -1;
	}
	fclose(f);
}
int main(int argc,char *argv[]){
	if(argc != 2)
		return -1;
	struct minfs_superblock sblk;
	sblk.blocksize = 512;
	sblk.starting_block = 4;
	sblk.starting_inode = 4;
	mkfs_minfs(&sblk,NULL,argv[1]);
}
