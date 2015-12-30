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
int _todec(char *buf){
	return ((uint32_t)buf[1] << 16| buf[0] << 8 );
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
struct minfs_superblock *parse_superblk(int drivenum,struct minfs_superblock blk){
	struct minfs_superblock ret;
	char *buf = malloc(1024);
	int i = 0;
	while(i < 512){
		buf[i] = 0;
		i++;
	}
	i = 0;
	ata_read_master(buf,2,0);
	char _buf[] = {buf[0],buf[1]};
	ret.blocksize = _todec(_buf);
	ret.starting_block = buf[2];
	ret.starting_inode = buf[3];
/*	//kprintf("%s\n",buf);
	//int i = 0;
	char _buf[] = {buf[0],buf[1]};
	//if(buf[1] != 2)
	//	while(1) { };
	//while(i < 512){
	//	kprintf("%c",buf[i]);
	//	i++;
	//}
	//kprintf("%s\n",_buf);
//	while(1){ };

	ret.blocksize = _todec(_buf);
	//if(ret.blocksize != 512)
	//	while(1) { };
	//char __buf[] = {buf[2],buf[3],buf[4]};
	//ret.starting_block = todec(__buf);
	//char ___buf[] = {buf[5],buf[6],buf[7]};
	//ret.starting_inode = todec(___buf);
	ret.starting_block = buf[2];
//	kprintf("%c\n%c\n",buf[2],0x04);
	//if(buf[2] != 4)
	//	panic();
	ret.starting_inode = buf[3];
	//return &ret;*/
	blk = ret;
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
struct block *parse_buffer_block(char *buf,struct minfs_superblock *sblk,int i){
	struct block ret;
	char *bufs[1024] = {malloc(1024)};
	ata_read_master(bufs[0],3,0);
	char _buf[] = {buf[0],buf[1]};
	ret.sig = _buf;
	if(buf[0] != 0x42 && buf[1] != 0x69 && i != 0){
		debug("PARSE_BUFFER_BLOCK","Failed to parse buffer:Invalid signature!");
		//debug("PARSE_BUFFER_BLOCK","Continuing...");
		//debug("PARSE_BUFFER_BLOCK","dumping raw buffer");
		//int i = 0;
		//while(i < 512){
		//	kprintf("%c",buf[i]);
		//	i++;
		//}
		kprintf("\n");
		debug("KERNEL","panic");
		__panic("Invalid signature");
		//__panic("Invalid Signature");
	}
	ret.cont = buf;
	char *strip = malloc(512);
	ret.strip = strip;
	ret.type = buf[2];
	if(ret.type == 0x00){
		//Type is not allocated	
		debug("PARSE_BUFFER_BLOCK","Found unallocated block");
		//while(1) {};
		//panic();
		ret.isfile = 0;
		ret.isdir = 0;
		ret.isinfo = 0;
		ret.isallocated = 0;
		return &ret;
	}
	else if(ret.type == 0x01){
		debug("PARSE_BUFFER_BLOCK","Found Info block");
		//Type is info
		ret.isfile = 0;
		ret.isdir = 0;
		ret.isinfo = 1;
		ret.isallocated = 1;
		int _infoblock = 0;
		ret.infoblock = _infoblock;
		ret.ending_block = 1;
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
			__panic("Invalid long byte");
		}
	}
	else if(ret.type == 0x02){

		//Type is file
		debug("PARSE_BUFFER_BLOCK","Found file block");
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
	else if(ret.type == 0x03){
		debug("PARSE_BUFFER_BLOCK","Found dir block");
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
	else if(ret.type == 0x04){
		debug("PARSE_BUFFER_BLOCK","Found rootfs block");
		//Root file system
		ret.isfile = 0;
		ret.isdir = 1;
		ret.isinfo = 0;
		ret.isallocated = 1;

	}
	else{
		debug("PARSE_BUFFER_BLOCK","Failed to parse buffer:Invalid type\n");
		__panic("Invalid type");
	}
	return &ret;
}
int mount_p1(char *buf,int drivenum,struct minfs_superblock *_superblk){
	t_init();
	struct minfs_superblock garbage;
	struct minfs_superblock *superblk;
	superblk = parse_superblk(0,garbage);
	if(superblk->starting_block <= 0)
		__panic("Null starting block");
	//else if(superblk->starting_block == 4)
	//	panic();
	//else if(superblk->starting_block == 4)
	//	kprintf("!\n");
	debug("MINFS_MOUNT","start");
	char *block1 = malloc(1024);
//	char block1[1024]
	//kprintf("%s\n",block1);
	debug("MINFS_MOUNT","Allocating memory(About 524288 bytes) for buffers...\n");
	char *buffers[512] = {malloc(1024)};
	int i = 0;
	//while(i < 512){
	//	block1[i] = 0;
	//	i++;
	//}
	debug("MINFS_MOUNT","Reading Starting Block");
	//if(superblk->starting_block != 4)
	//	panic()
	//while(i < superblk->starting_block){
	///	kprintf(".");
	//	i++;
	//}
	ata_read_master(block1,superblk->starting_block,0x00);
	//kprintf("%s\n",block1);
	debug("MINFS_MOUNT","Parsing starting Block");
	struct block *inblock = parse_buffer_block(block1,superblk,1);
	debug("MINFS_MOUNT","Finished parsing block");
	debug("MINFS_MOUNT","Tracking and parsing info block");
	if(inblock->type == 0){
		debug("MINFS_MOUNT","Starting block null");
		debug("MINFS_MOUNT","Nothing to do");
		return 0;
	}
	else if(inblock->infoblock == 0){
		debug("MINFS_MOUNT","Info block is null hanging until it isn't(Probaly never)");
		while(inblock->infoblock == 0)
			inblock = parse_buffer_block(block1,superblk,1);
	}
	else{
		debug("MINFS_MOUNT","Succesfully read address of block,Jumping to it");
		ata_read_master(buffers[0],inblock->infoblock,drivenum);
		debug("MINFS_MOUNT","Parsing info block\n");
		struct block *infoblk = parse_buffer_block(buffers[0],superblk,0); 
		debug("MINFS_MOUNT","Successfuly parsed block");
		
	}
	return 1;
}
#endif
