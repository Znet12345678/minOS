/*
*MinFS File System Driver
*Not Completed
*(c) 2015 Zachary James Schlotman
*For Use only in minOS
*Linked into kernel
*Not to be used as module
*/
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
struct block *parse_buffer_block(char *buf,struct minfs_superblock *sblk){
	struct block ret;
	char _buf[] = {buf[0],buf[1]};
	ret.sig = _buf;
	if(_buf[0] != 42 || _buf[1] != 69){
		debug("PARSE_BUFFER_BLOCK","Failed to parse buffer:Invalid signature!");
		debug("KERNEL","panic");
		panic();
	}
	ret.cont = buf;
	char *strip = malloc(512);
	ret.strip = strip;
	ret.type = buf[2];
	if(ret.type == 0){
		//Type is not allocated	
		ret.isfile = 0;
		ret.isdir = 0;
		ret.isinfo = 0;
		ret.isallocated = 0;
		return &ret;
	}
	else if(ret.type == 1){
		//Type is info
		ret.isfile = 0;
		ret.isdir = 0;
		ret.isinfo = 1;
		ret.isallocated = 1;
		int _infoblock = 0;
		ret.infoblock = _infoblock;
		ret.endingblock = 1;
		ret.is_long = buf[3];
		if(ret.is_long == 1){
			char _lba_len[] = {buf[4],buf[5],buf[6]};
			ret.lba_len = todec(_lba_len);
			ret.blocks = ret.lba_len;
			char _containing_dir[80];
			int i = 7;
			int i1 = 0;
			while(buf[i] != 0){
				_containing_dir[i1] = buf[i];
				i1++;
				i++;
			}
			ret.containing_dir = _containing_dir;
		}
		else if(ret.is_long == 0){
			ret.lba_len = buf[4];
			ret.blocks = ret.lba_len;
			char _containing_dir[80];
			int i = 5;
			int i1 = 0;
			while(buf[i] != 0){
				_containing_dir[i1] = buf[i];
				i1++;
				i++;
			}
			ret.containing_dir = _containing_dir;
		}
		else{
			debug("PARSE_BUFFER_BLOCK","Failed to parse buffer:Invalid long byte");
			panic();
		}
	}
	else if(ret.type == 2){
		//Type is file
		ret.isfile = 1;
		ret.isdir = 0;
		ret.isinfo = 0;
		ret.isallocated = 1;
		char _infoblock[] = {buf[3],buf[4],buf[5]};
		ret.infoblock = todec(_infoblock);
		//ret.endingblock = ret.infoblock;
		int i = 6;
		int i1 = 0;
		char _strip[506];
		while(i < 512){
			_strip[i1] = buf[i];
			i1++;
			i++;
		}
		ret.strip = _strip;
		if(buf[510] == 0 && buf[511] == 42 && buf[512] == 69){
			ret.ending_block = 0;
		}
		else{
			char _ending_block[] = {buf[510],buf[511],buf[512]};
			ret.ending_block = todec(_ending_block);
		}
		
	}
	else if(ret.type == 3){
		//Type is directory
		ret.isfile = 0;
		ret.isdir = 1;
		ret.isinfo = 0;
		ret.isallocated = 1;
		char _infoblock[] = {buf[4],buf[4],buf[5]};
		ret.infoblock = todec(_infoblock);
		char _files[512];
		int i = 6;
		while(i < 512){
			_files[i] = buf[i];
			i++;
		}
		ret.files = _files;
		
	}
	else if(ret.type == 4){
		//Root file system
		ret.isfile = 0;
		ret.isdir = 1;
		ret.isinfo = 0;
		ret.isallocated = 1;

	}
	else{
		debug("PARSE_BUFFER_BLOCK","Failed to parse buffer:Invalid type\n");
		panic();
	}
	return &ret;
}
int mount_p1(char *buf,int drivenum,struct minfs_superblock *superblk){
	debug("MINFS_MOUNT","start");
	char *block1 = malloc(512);
	debug("MINFS_MOUNT","Allocating memory(About 524288 bytes) for buffers...\n");
	char *buffers[512] = {malloc(1024)};
	int i = 0;
	debug("MINFS_MOUNT","Reading Starting Block");
	ata_read_master(block1,superblk->starting_block,drivenum);
	debug("MINFS_MOUNT","Parsing starting Block");
}
#endif
