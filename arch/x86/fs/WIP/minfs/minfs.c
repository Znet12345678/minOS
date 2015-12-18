#ifndef __KERNEL_BUILD
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#else
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#endif
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
struct inode *read_inode(char *in,int n,struct minfs_supeblock *sblk){
	struct inode ret;
	//...
	return &ret;
}
struct block *read_block(char *in,int n,struct inode *inode){
	struct inode *inode = read_inode(in,n);
	struct block *blk;
	//...
	return blk;
}
#else
struct minfs_superblock *parse_superblk(int drivenum){
	struct minfs_superblock ret;
	//...
	return &ret;
}
struct inode *read_inode(int drive,int n,struct minfs_superblock *sblk){
	/*Reads from drive number*/
	struct inode ret;
	//...
	return &ret;
}
struct block *read_blk(int drive,int n,struct inode *inode,struct minfs_superblock *sblk){
	struct block ret;
	//...
	return &ret;
}
int mount(int drivenum,int partnum,char *path){
	//...
	return 0;
}
#endif
