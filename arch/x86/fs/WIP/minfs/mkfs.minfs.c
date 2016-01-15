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
	//char blksz[] = {sblk->blocksize / 100,sblk->blocksize % 100};
	//fputc(sblk->blocksize,f);
	printf("Writing superblock\n");
	char blksz = (sblk->blocksize >> 16);
	char blksz1 = sblk->blocksize >> 8;
	printf("Writing block size\n");
	fputc(blksz,f);
	fputc(blksz1,f);
	//fputc(blksz1,f);
	printf("Writing block information\n");
	fputc(sblk->starting_block,f);
	fputc(sblk->starting_inode,f);
	/*printf("Writing file information\n");
	fputc(sblk->numoffiles,f);
	fputc(sblk->numofdirs,f);
	printf("Writing files\n");
	int i = 0;
	while(i < sblk->numoffiles){
		fprintf(f,"%s",sblk->filenames[i]);
		fputc(sblk->fpntrs[i],f);
		fputc(TERMINATE,f);
		i++;
	}
	i = 0;
	printf("Writing directories\n");
	while(i < sblk->numofdirs){
		fprintf(f,"%s",sblk->dirnames[i]);
		fputc(sblk->dpntrs[i],f);
		fputc(TERMINATE,f);
		i++;
	}*/
//	printf("Writing misc block\n");
	//fputc(SUPERBLKTERMINATE,f);
	//fprintf(f,"%s",
//	fputc(0,f);
//	fputc(0,f);
//	fputc(5,f);
	/*fputc(blksz[0],f);
	fputc(blksz[1],f);
	if(sblk->starting_block < 10){
		fputc(0,f);
		fputc(0,f);
		fputc(sblk->starting_block,f);
		//fputc(0,f);
		//fputc(0,f);
	}
	else if(sblk->starting_block < 100){
		fputc(0,f);
		fputc(sblk->starting_block / 10,f);
		fputc(sblk->starting_block % 10,f);
		//fputc(0,f);
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
		//fputc(0,f);
		//fputc(0,f);
	}
	else if(sblk->starting_inode < 100){
		fputc(0,f);
		fputc(sblk->starting_inode /10,f);
		fputc(sblk->starting_inode %10,f);
		//fputc(0,f);
	}
	else if(sblk->starting_inode < 1000){
		fputc(sblk->starting_inode / 100,f);
		fputc((sblk->starting_inode % 100) / 10,f);
		fputc(sblk->starting_block % 10,f);
	}
	else{
		printf("Starting inode too large!\n");
		return -1;
	}*/
	fseek(f,2048,SEEK_SET);
	printf("Writing rootfs block\n");
	fputc(0x42,f);
	fputc(0x69,f);
	fputc(0x04,f);	
	fputc(0x00,f);
	fputc(0x00,f);
	fputc(5,f);
	fseek(f,2560,SEEK_SET);
	printf("Writing info block\n");
	fputc(0x42,f);
	fputc(0x69,f);
	fputc(0x01,f);
	fputc(0x00,f);
	fputc(0x01,f);
	fputc('/',f);
	fputc(0x00,f);
	printf("Writing misc block\n");
	fseek(f,5120,SEEK_SET);
	fputc(0,f);
	fputc(0,f);
	fputc(1,f);
	fputc(0,f);
	fputc(0,f);
	fputc(0,f);
	fputc(0,f);
	fputc(0x04,f);
	fputc(0,f);
	fputc(0xFF,f);
	fputc('/',f);
	fputc(0xFF,f);

	fclose(f);
}
int main(int argc,char *argv[]){
	if(argc != 2){
		printf("Invalid usage!\n");
		return -1;
	}
	printf("Preparing superblock\n");
	struct minfs_superblock sblk;
	sblk.blocksize = 512;
	sblk.starting_block = 4;
	sblk.starting_inode = 4;
	/*sblk.numoffiles = 0;
	sblk.numofdirs = 1;
	sblk.dpntrs = malloc(1024);
	sblk.dpntrs[0] = 4;*/
	//printf("Allocating memory for dirnames[0]\n");
	//sblk.dirnames[0] = malloc(1024);
	char *dirnames[1024] = {malloc(1024)};
	dirnames[0] = "/";
	//sblk.dirnames = dirnames;
	printf("Finished preparing superblock\n");
	mkfs_minfs(&sblk,NULL,argv[1]);

}
