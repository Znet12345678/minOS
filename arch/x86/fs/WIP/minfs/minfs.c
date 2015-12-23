#ifndef __KERNEL_BUILD
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include "minfs.h"
#else
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "minfs.h"
#endif
int todec(char *buf){
	return ((uint32_t)buf[2] << 16 | buf[1] << 8 | buf[0]);
}
#ifndef __KERNEL_BUILD
int attach(char *in_name,char *out_name){
	//...
	return 0;
}
struct minfs_superblock *parse_superblk(char *in){
	struct minfs_superblock ret;
	//...
	return &ret;
}
struct inode *read_inode(char *in,int n,struct minfs_superblock *sblk){
	struct inode ret;
	//...
	return &ret;
}
struct block *read_block(char *in,int n,struct inode *inode,struct minfs_superblock *sblk){
	struct inode *_inode = read_inode(in,n,sblk);
	struct block *blk;
	//...
	return blk;
}
#else
struct minfs_superblock *parse_superblk(int drivenum){
	struct minfs_superblock ret;
	char *buf = malloc(1024);
	ata_read_master(buf,2,0);
	char _buf[] = {buf[0],buf[1]};
	ret.blocksize = todec(_buf);
	char __buf[] = {buf[2],buf[3],buf[4]};
	ret.starting_block = todec(__buf);
	char ___buf[] = {buf[5],buf[6],buf[7]};
	ret.starting_inode = todec(___buf);
	return &ret;
}
struct inode *read_inode(int drive,int n,struct minfs_superblock *sblk){
	/*Reads from drive number*/
	struct inode ret;
	char *buf = malloc(1024);
	if((n % 2) == 0)
		ata_read_master(buf,n,drive);
	else
		ata_read_master(buf,n + 1,drive);
	char _buf[] = {buf[0],buf[1]};
	ret.sig = _buf;
	char _sig[] = {0x42,0x69};
	if(strcmp(ret.sig,_sig) != 0)
		return;
	char __buf[] = {buf[2],buf[3],buf[4]};
	ret.numofdirs = todec(__buf);
	//...
	return &ret;
}
struct block *read_blk(int drive,int n,struct inode *inode,struct minfs_superblock *sblk){
	struct block ret;
	//...
	return &ret;
}
int minfs_mount(int drivenum,int partnum,char *path){
	//...
	return 0;
}
#endif
