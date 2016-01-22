
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
	//while(i < 512){
	//	buf[i] = 0;
	//	i++;
	//}
	i = 0;
	ata_read_master(buf,2,0);
	//while(i < 512){
	//	kprintf("%c",buf[i]);
	//	i++;
	//}
	i = 0;
	//kprintf("%s\n",buf);
	//while(i < 512){
	//	t_putc(buf[i]);
	//	i++;	
	//}//
	//while(1) { };
	i = 0;
	char _buf[] = {buf[0],buf[1]};
	ret.blocksize = _todec(_buf);
	//if(buf[2] != 0x04)
	//	panic();
	int sb = buf[2];
	//if(sb != 4)
	//	panic();
	int si = buf[3];
	ret.starting_block = sb;
	ret.starting_inode = si;
	/*ret.numoffiles = buf[4];
	ret.numofdirs = buf[5];
	ret.fpntrs = malloc(1024);
	char *fn[1024] = {malloc(1024)};
	ret.filenames = fn;
	ret.dpntrs = buf[5];
	char *dirnames[1024] ={malloc(1024)};
	ret.dirnames = dirnames;*/
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
	ret.starting_block = (int)buf[2];
//	kprintf("%c\n%c\n",buf[2],0x04);
	//if(buf[2] != 4)
	//	panic();
	ret.starting_inode =(int) buf[3];
	//return &ret;*/
	//while(1) { };
	blk = ret;
	return &ret;
}
struct miscblk *parse_miscblk(struct miscblk garbage){
	//while(1){};
	char *buf = malloc(1024);
	ata_read_master(buf,10,0);
	garbage.numofallocdblocks = buf[0] << 16 | buf[1] << 8 | buf[2];
	garbage.numoffiles = buf[3] << 16 | buf[4] << 8 | buf[5];
	int i = 6;
	//kprintf("1");
	int lba = 10;
	garbage.fpnt = malloc(1024);
	garbage.dpnt = malloc(1024);
	int i1 = 0;
	while(buf[i] != 0){
		if(i >= 512){
			i = 0;
			buf = malloc(1024);
			ata_read_master(buf,++lba,0);
		}
		garbage.fpnt[i1] = buf[i];
		i1++;
		i++;
	}
	garbage.i = i;
	i++;
	i1 = 0;
	while(buf[i] != 0){
		if(i >= 512){
			i = 0;
			buf = malloc(1024);
			ata_read_master(buf,++lba,0);
		}
		garbage.dpnt[i1] = buf[i];
		i1++;
		i++;
	}
	garbage._i = i;
	i++;
	int i2 = 0;
	while(1){
		t_displayl();
		if(buf[i] == 0xff)
			break;
		if(i >= 512){
			i = 0;
			buf = malloc(1024);
			ata_read_master(buf,++lba,0);
		}
		garbage.names[i2] = malloc(1024);
		i1 = 0;
		char *tmpbuf = malloc(80);
		while(buf[i] != 0x20){
			if(i >= 512){
				i = 0;
                        	buf = malloc(1024);
                        	ata_read_master(buf,++lba,0);
               	 	}

			kstrcat(tmpbuf,&buf[i]);
			i++;
		}
		garbage.names[i2] = tmpbuf;
		//kprintf(".");
		i2++;
		i++;
	}
	i++;
	i2 = 0;
	while(1){
		t_displayl();
		if(buf[i] == 0xff)
			break;
		if(i >= 512){
			i = 0;
                        buf = malloc(1024);
                        ata_read_master(buf,++lba,0);
		}
		garbage.names[i2] = malloc(1024);
		i1 = 0;
		char *tmpbuf = malloc(80);
		while(buf[i] != 0x20){
			if(i >=512){
				i = 0;
                        	buf = malloc(1024);
                	        ata_read_master(buf,++lba,0);
        	        }
			kstrcat(tmpbuf,&buf[i]);
			i++;
			//garbage.names[i2
		}
		garbage.names[i2] = tmpbuf;

		i2++;
		i++;
	}
	debug("PARSE_MISCBLOCK","done");
	return &garbage;
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
struct block *parse_buffer_block(struct block ret,int lba,struct minfs_superblock *sblk,int i){
	char *buf = malloc(1024);
	ata_read_master(buf,lba,0x00);
	struct block _blk;
	//char *bufs[1024] = {malloc(1024)};
	//ata_read_master(bufs[0],4,0);
	//char _buf[] = {buf[0],buf[1]};
	//ret.sig = _buf;
	//kprintf("%c\n%c\n%c\n%c\n",buf[0],0x42,0x69,bufs[0][0]);
	if(buf[0] != 0x42 || buf[1] != 0x69){
		debug("PARSE_BUFFER_BLOCK","Failed to parse buffer:Invalid signature!");
		//kprintf("\n");
		//debug("KERNEL","panic");
		//__panic("Invalid signature");
		//__panic("Invalid Signature");
		#ifdef RELEASE
			debug("KERNEL","panic()");
			panic();
		#else
			debug("PARSE_BUFFER_BLOCK","__panic(char *reason)");
			__panic("Invalid signature");
		#endif
	}
	ret.cont = buf;
	char *strip = malloc(513);
	ret.strip = strip;
	ret.type = buf[2];
	//while(1){ };
	if(ret.type == 0x00){
		//Type is not allocated	
		debug("PARSE_BUFFER_BLOCK","Found unallocated block");
		//while(1) {};
		//panic();
		ret.isfile = 0;
		ret.isdir = 0;
		ret.isinfo = 0;
		ret.isallocated = 0;
		_blk = ret;
		return &_blk;
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
			ret.lba_len = (buf[4] << 16 | buf[5] << 8 | buf[6]);
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
		//char _infoblock[] = {buf[3],buf[4],buf[5]};
		ret.infoblock = (buf[3] << 16 | buf[4] << 8 | buf[5]);
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
		char _infoblock[] = {buf[3],buf[4],buf[5]};
		ret.infoblock = (buf[3] << 16 | buf[4] << 8 | buf[5]);
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
		char _infoblock[] = {buf[3],buf[4],buf[5]};
		ret.infoblock = (buf[3] << 16 | buf[4] << 8 | buf[5]);
	}
	else{
		debug("PARSE_BUFFER_BLOCK","Failed to parse buffer:Invalid type\n");
		//kprintf("%c",ret.type);
		__panic("Invalid type");
	}
	//_blk = ret;
	//return &_blk;
	return &ret;	
}
int mount_p1(char *buf,int drivenum,struct minfs_superblock *_superblk){
	//#ifdef DEBUG
	//while(1) { };
	t_init();
	//#endif
	struct minfs_superblock garbage;
	struct minfs_superblock *superblk;//= malloc(sizeof(struct minfs_superblock *));
	superblk = parse_superblk(0,garbage);
	if(superblk->starting_block <= 0)
		__panic("Null starting block");
	//while(1){ };
	//else if(superblk->starting_block == 4)
	//	panic();
	//else if(superblk->starting_block == 4)
	//	kprintf("!\n");
	debug("MINFS_MOUNT","init");
	debug("MINFS_MOUNT","...");
	char *block1 = malloc(1024);
//	char block1[1024]
	//kprintf("%s\n",block1);
	debug("MINFS_MOUNT","Allocating memory(About 524288 bytes) for buffers...");
	char *buffers[512] = {malloc(1024)};
	debug("MINFS_MOUNT","Allocating memory for File Table");
	char *file_table[102400] = {malloc(1024)};
	debug("MINFS_MOUNT","Allocating memory for Descriptor Table");
	char *desc_table[102400] = {malloc(1024)};
	int i = 0;
	//while(i < 512){
	//	block1[i] = 0;
	//	i++;
	//}
	debug("MINFS_MOUNT","Reading Starting Block");
	ata_read_master(block1,superblk->starting_block,0x00);
//	kprintf("%c\n",block1[2]);
	i = 0;
	debug("MINFS_MOUNT","Parsing starting Block");
	struct block inblock;
	struct block *_inblock = parse_buffer_block(inblock,superblk->starting_block,superblk,1);
	debug("MINFS_MOUNT","Finished parsing block");
	debug("MINFS_MOUNT","Tracking and parsing info block");
	//while(1){ };
	//kprintf("%c",block1[2]);

	/*if(inblock.type == 0){
		debug("MINFS_MOUNT","Starting block null");
		debug("MINFS_MOUNT","Nothing to do");
		return 0;
	}*/
	if(_inblock->type != 0x04){
		debug("MINFS_MOUNT","Couldn't find rootfs");
		debug("MINFS_MOUNT","hang");
		while(1){ };
	}
	else if(_inblock->infoblock < superblk->starting_block){
		debug("MINFS_MOUNT","Info block is at an invalid position. panic()");
		panic();
		//while(inblock.infoblock == 0)
			//inblock = parse_buffer_block(block1,superblk,1);
	}
	else{
		debug("MINFS_MOUNT","Succesfully read address of block,Jumping to it");
		char *inbuf = malloc(1024);
		int i = 0;
		//if(_inblock->infoblock == 1280 || _inblock->infoblock == 327680){
		//	kprintf("!");
		//}
		//while(i < _inblock->infoblock){
			//kprintf(".");
			//i++;
		//}
		ata_read_master(inbuf,_inblock->infoblock,0x00);
		debug("MINFS_MOUNT","Parsing info block\n");
		struct block infoblk;
		struct block *_infoblk = parse_buffer_block(infoblk,_inblock->infoblock,superblk,0); 
		debug("MINFS_MOUNT","Successfuly parsed block");
		debug("MINFS_MOUNT","Reading and Parsing miscblock");
		//while(1) { };
		struct miscblk mg;
		struct miscblk *mb = parse_miscblk(mg);
	}
	return 1;
}
#endif
