//
//  inffs.c
//  
//
//  Created by Zach Schlotman on 4/27/16.
//
//
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <io.h>
#include <string.h>
#include <kernel/tty.h>
#include "inffs.h"
int num_of_levels(const char *path){
	int i = 0;
	int ret = 0;
	while(i < strlen(path)){
		if(*path == '/')
			ret++;
		*path++;
		i++;
	}
	return ret;
}
struct inffs_path *parse_path(const char *path,struct inffs_path *_path){
	int case1 = 0;
	//struct inffs_path *_path = malloc(sizeof(struct inffs_path *));
	if(path[strlen(path) - 1] == '/')
		case1 = 1;
	if(case1){
		int i = 0;
		int j = 0;
		while(i < (num_of_levels(path))){
			int k = 0;
			if(path[j] == '/')
				j++;
			else
				while(path[j] != '/'){
					_path->dir[k] = path[j];
					k++;
					j++;
				}
			i++;
		}
		int k = 0;
		while(path[j] != '/'){
			_path->name[k] = path[j];
			k++;
			j++;
		}
		return _path;
	}
	else{
                int i = 0;
                while(i < (num_of_levels(path))){
			int k = 0;
			if(*path == '/')
				*path++;
			else
				while(*path != '/'){
					_path->dir[k] = *path;
					k++;
					*path++;
				}
			i++;
		}
		int k = 0;
		while(*path != 0){
			_path->name[k] = *path;
			k++;
			*path++;
		}
                return _path;

	}
}
int __MINOS_GET_DISK_SIZE(){
    int i = 1;
    int j = 0;
    int blk = 0;
    int inc = 1000000000;
    while(inc > 0){
        if(ata_check_lba(i * inc) == 0){
            //kprintf(".");
            blk+=inc;
        }
        else{
 	    for(int i = 0; i < 8;i++)
	    	kprintf(".");
            inc/=10;
        }
        i++;
    }
    return blk;
}
int __INFFS_MKFS_FULLDISK(){
    t_init();
    kprintf("%d\n",1024);
    kprintf("\nMaking full disk filesystem\n");
    struct __INFFS_SUPERBLK ret;
    char sig[] = {'I',0x0f,'N',0x0f,'F',0x0f,'F',0x0f,'S',0x0f};
    ret.sig = sig;
    kprintf("Getting disk size\n");
    int disk_size = __MINOS_GET_DISK_SIZE();
    kprintf("Done Getting disk size\n");
    //if(disk_size > 102400)
      //  ret.ninfblk = disk_size / 1024;
    //else if(disk_size > 100)
  //      ret.ninfblk = disk_size / 100;
//    else
    ret.ninfblk = 1024;
    ret.inf_start_lba = 5;
 //   if(ret.inf_start_lba == 5)
//	panic();
    ret.inf_end_lba = 5 + ret.ninfblk;
    ret.fs_size = disk_size;
  //  kprintf("%d\n",ret.inf_start_lba);
    kprintf("Writing:[disk_size]%d [ninfblk]%d [inf_start_lba]%d\n[inf_end_lba]%d [fs_size]%d\n",disk_size,ret.ninfblk,ret.inf_start_lba,ret.inf_end_lba,ret.inf_end_lba,ret.fs_size);
    char sblk_raw[] = {'I',0x0f,'N',0x0f,'F',0x0f,'F',0x0f,'S',0x0f,ret.ninfblk >> 24,ret.ninfblk >> 16, ret.ninfblk >> 8,ret.ninfblk >> 0,ret.inf_start_lba,ret.inf_end_lba >> 24,ret.inf_end_lba >> 16,ret.inf_end_lba >> 8,ret.inf_end_lba >> 0,ret.fs_size >> 24,ret.fs_size >> 16,ret.fs_size >> 16,ret.fs_size >> 8,ret.fs_size >> 0};
 //   if(ret.inf_start_lba == 5024)
//	panic();
    kprintf("Writing data\n");
    if(ata_write_master_n(sblk_raw,5,sizeof(sblk_raw)) < 0){
        kprintf("Error making file system!\n");
        return -1;
    }
    char *buf = malloc(1024);
    ata_read_master(buf,5,0);
    kprintf("Read data:[ninfblk]%d [inf_start_lba]%d\n[inf_end_lba]%d [fs_size]%d\n",(buf[10] << 24 | buf[11] << 16 | buf [12] << 8 | buf[13] ),buf[14],(buf[15] << 24,buf[16] << 16 | buf[17] << 8 | buf[18]),(buf[19] << 24 | buf[20] << 16 | buf[21] << 8 | buf[22]));
    kprintf("Done\n");
}
int __IS_INFFS(){
	char *buf = malloc(1024);
	ata_read_master(buf,5,0);
	if(buf[0] == 'I' && buf[1] == 0x0F && buf[2] == 'N'&& buf[3] == 0x0f && buf[4] == 'F' && buf[5] == 0x0f && buf[6] == 'F' && buf[7] == 0x0f &&buf[8] == 'S'&&buf[9]==0x0f)
		return 1;
	return 0;
}
struct __INFFS_SUPERBLK *__INFFS_PARSE_SUPERBLK(struct __INFFS_SUPERBLK *ret){
   	//struct __INFFS_SUPERBLK *ret = malloc(sizeof(struct __INFFS_SUPERBLK*));
    	char *buf = malloc(1024);
 	ata_read_master(buf,5,0);
	ret->sig[0] = __IS_INFFS();
	//while(1)
	//	;
	if(!(ret->sig[0]))
		return (struct __INFFS_SUPERBLK *)-1;
	ret->ninfblk = buf[10] << 24 | buf[11] << 16 | buf[12] << 8 | buf[13];
	ret->inf_start_lba = buf[14];
	ret->inf_end_lba = buf[15] << 24 | buf[16] << 16 | buf[17] << 8 | buf[18];
	kprintf("%d\n",ret->inf_end_lba);
	ret->fs_size = buf[19] << 24 | buf[20] << 16 | buf[21] << 8 | buf[22];
	return ret;
}
struct __INFFS_INFOBLK *__INFFS_GET_INFBLK(struct inffs_path *pth,struct __INFFS_SUPERBLK *sblk){
	struct __INFFS_INFOBLK *ret = malloc(sizeof(struct __INFFS_INFOBLK*));
	int lba = sblk->inf_start_lba;
	while(lba < sblk->inf_end_lba){
		char *buf = malloc(1024);
		ata_read_master(buf,lba,0);
		int i = 0;
		while(i < 512){
			ret->isalloc = buf[i];
			if(!(ret->isalloc))
				return (struct __INFFS_INFOBLK *)-1;
			i++;
			ret->len = buf[i];
			i++;
			ret->blk = buf[i] << 24 | buf[i + 1] << 16 | buf[i + 2] << 8 | buf[i+3];
			i+=4;
			ret->sizeinblocks = buf[i] << 24 | buf[i + 1] <<16 | buf[i + 2] << 8 | buf[i + 3];
			i+=4;
			ret->namelen = buf[i];
			i++;
			int j = 0;
			while(j < ret->namelen){
				ret->name[j] = buf[j];
				j++;
			}
			ret->dent_pntr = buf[i] << 24 | buf[i + 1] << 16 | buf[i + 2] << 8 | buf[i + 3];
			i+=3;
			if(strcmp(ret->name,pth->name) == 0)
				return ret;
			i++;
		}
		lba++;
	}
}
struct __INFFS_INFBLK_FREE{
        int start_lba;
        int start_offset;
        int end_lba;
        int end_offset;
};

struct __INFFS_INFBLK_FREE *find_freeinfblk(int n,struct __INFFS_INFBLK_FREE *ret){
	struct __INFFS_SUPERBLK *sblk = malloc(sizeof(struct __INFFS_SUPERBLK *));
	__INFFS_PARSE_SUPERBLK(sblk);
	int meh = 0;
	//while(1)
	//	;
	int lba = sblk->inf_start_lba;
	int i = 0;
	int free = 0;
	ret->start_lba = -1;
	ret->start_offset = -1;
	ret->end_lba = -1;
	ret->end_offset = -1;
	while(lba < sblk->inf_end_lba){
		i = 0;
		//kprintf(".");
		char *buf = malloc(1024);
		ata_read_master(buf,lba,0);
		while(i < 512){
			if(free == n){
				ret->end_lba = lba;
				ret->end_offset = i;
				return ret;
			}
			else if(buf[i] == 0 && ret->start_lba == -1){
				ret->start_lba = lba;
				ret->start_offset = i;
				free++;
			}
			else if(buf[i]= 0)
				free++;
			else{
				ret->start_lba = -1;
				ret->start_offset = -1;
				free = 0;
			}
			i++;
		}
		lba++;
	}
}
struct __INFFS_FILE * __INFFS_FULLDISK_FS_FOPEN(const char *path,int opperation,struct __INFFS_FILE *ret) {
	struct __INFFS_SUPERBLK *sblk = malloc(sizeof(struct __INFFS_SUPERBLK *));
	__INFFS_PARSE_SUPERBLK(sblk);
	///while(1)
	//	;
	//struct __INFFS_FILE *ret = malloc(sizeof(struct __INFFS_FILE *));
	//struct __INFFS_INFOBLK *infblk = __INFFS_GET_INFBLK(parse_path(path),sblk);
	struct inffs_path *_path = malloc(sizeof(struct inffs_path *));
	parse_path(path,_path);
	if(opperation == __INFFS_FOPP_READ){
		struct __INFFS_INFOBLK *infblk = __INFFS_GET_INFBLK(_path,sblk);
		kstrcpy(ret->name,_path->name);
		//kprintf("%s\n",ret->name);
		if(!(sblk)){
			debug("INFFS","Failed to parse superblock");
			return -1;
		}
		if(!(infblk)){
			debug("INFFS","Invalid file\n");
			return -1;
		}
		int lba = infblk->blk;
		char *buf = malloc(1024);
		ata_read_master(buf,lba,0);
		ret->isalloc = buf[0];
		if(!(ret->isalloc)){
			debug("INFFS","Something is wrong with your file system!");
			return -1;
		}
		ret->sig = buf[1];
		if(ret->sig != 0x0F){
			debug("INFFS","Something is wrong with your file system!");
			return -1;
		}
		ret->fsize = buf[2] << 24 | buf[3] << 16 | buf[4] << 8 | buf[5];
		ret->start_lba = lba;
		ret->end_lba = (infblk->blk + infblk->sizeinblocks);
		ret->endingval = buf[6] << 8 | buf[7];
		ret->pos = 0;
		ret->opperation = opperation;
		ret->blkpos = 0;
		ret->_blkpos = 0;
		return ret;
	}
	else{
		kstrcpy(ret->name,_path->name);
		kprintf("%s\n",ret->name);
		ret->fsize = 0;
		struct __INFFS_INFBLK_FREE *infblk = malloc(sizeof(struct __INFFS_INFBLK_FREE *));
		find_freeinfblk(strlen(_path->name) + 12,infblk);
		ret->start_lba = infblk->start_lba;
		//if(!(ret->start_lba)){
		//	debug("__INFFS_FULLDISK_FS_FOPEN","Invalid infblk");
		//}
		ret->endingval = infblk->end_lba;
		ret->pos = infblk->start_offset;
		ret->opperation = opperation;
		ret->blkpos = infblk->start_offset;
		ret->_blkpos = 0;
		return ret;
	}
}
struct free{
	unsigned int lba_begin;
	unsigned int lba_end;
	unsigned int offset_begin;
	unsigned int offset_end;
};
struct free *find_free(unsigned long size,struct free *ret){
	//while(1)
	//	;
	struct __INFFS_SUPERBLK *sblk =  malloc(sizeof(struct __INFFS_SUPERBLK *));
	__INFFS_PARSE_SUPERBLK(sblk);
	//while(1)
	//	;
	if(!(sblk)){
		debug("INFFS","Failed to parse superblock");
		panic();
	}
	int lba = sblk->inf_end_lba + 1;
	char *buf = malloc(1024);
	if(!(buf)){
		debug("INFFS","Failed to allocate memory");
		panic();
	}
	int free = 0;
	int blkf = 0;
	if(!(ret)){
		debug("INFFS","Failed to allocate memory");
	}
	ret->lba_begin = -1;
	ret->lba_end = -1;
	ret->offset_begin = -1;
	ret->offset_end = -1;
	while(ata_read_master(buf,lba,0) > 0){
		t_displaylq();
		int i = 0;
		while(i < 512){
			if(buf[i] == 0 && ret->lba_begin == -1 && free < size){
				ret->lba_begin = lba;
				ret->offset_begin = i;
				free++;
			}
			else if(buf[i] == 0 && ret->offset_begin == -1 && free <size){
				ret->offset_begin = i;
				free++;
			}
			else if(free == size){
				ret->offset_end = i;
				ret->lba_end = lba;
				return ret;
			}
			else if(buf[i] == 0)
				free++;
			else{
				free = 0;
				ret->lba_begin = -1;
				ret->lba_end = -1;
				ret->offset_begin = -1;
				ret->offset_end = -1;
			}
			i++;
		}
		ret->offset_begin = -1;
		ret->offset_end = -1;
		lba++;
	}
	return ret;
}
int __INFFS_FULLDISK_FS_FWRITE(struct __INFFS_FILE *f,int *buf,int n){
	if(f->opperation != __INFFS_FOPP_WRITE)
		return -1;
	kprintf("Writing %s\n",f->name);
	kprintf("Finding free info block\n");
	struct __INFFS_INFBLK_FREE *free = malloc(sizeof(struct __INFFS_INFSBLK_FREE *));
	find_freeinfblk(strlen(f->name) + 12,free);
	if(!(free)){
		kprintf("Failed to find free space for infoblock\n");
		panic();
	}
	kprintf("Finding enough free space on drive\n");
	//while(1)
	//	;
	struct free *f_file = malloc(sizeof(struct free *));
	find_free(n,f_file);
	//while(1)
	//	;
	if(!(f_file)){
		kprintf("Failed to find free space for file\n");
		panic();
	}
	char wbuf[] = {1,(strlen(f->name) + 12),f_file->lba_begin >> 24,f_file->lba_begin >> 16,f_file->lba_begin >> 8,f_file->lba_begin >> 0,(n/512) >> 24,(n/512) >> 16,(n/512) >> 8,(n/512) >> 0,strlen(f->name)};
	char *fwbuf = malloc(1024);
	for(int i = 0; i < (sizeof(wbuf)/sizeof(*wbuf));i++)
		fwbuf[i] = wbuf[i];
	kstrcat(fwbuf,f->name);
	char c = 0;
	kstrcat(fwbuf,&c);
	kprintf("Writing buf 1\n");
	ata_write_master_no_no_ow(fwbuf,free->start_lba,free->start_offset,strlen(f->name) + 12);
	int i = f_file->offset_begin;
	int lba = f_file->lba_begin;
	char *tmpbuf = malloc(1024);
	int j = 0;
	kprintf("Writing buf 2\n");
	ata_write_master_no_no_ow((uint8_t*)buf,lba,i,n);
	j++;
	lba++;
}
int  __INFFS_FULLDISK_FS_FREAD(struct __INFFS_FILE *file,int *buf,int n){
	if(file->opperation != __INFFS_FOPP_READ)
		return -1;
	int read = 0;
	int i = 0;
	int remaining = n;
	if(file->pos >= file->end_lba * 512)
		return 0;
	while(read < n){
		char *_buf = malloc(1024);
		ata_read_master(_buf,file->blkpos,0);
		if(file->blkpos != file->end_lba &&( (n % 512) == 0 || ((remaining - 512) > (file->blkpos + 512))) && n > 512){
			int j = 0;
			while(j < 512){
				buf[i] = *_buf;
				*_buf++;
				i++;
				j++;
			}
			remaining-=512;
			file->blkpos++;
			file->pos+=512;
			read+=512;
		}
		else if(file->blkpos == file->end_lba && remaining > file->endingval){
			int j = 0;
			while(j < file->endingval){
				buf[i] = _buf[j];
				j++;
				i++;
			}
			read+=512;
			return read;
		}
		else if(remaining < 512){
			int j = 0;
			while(j < remaining){
				buf[i] = _buf[j];
				read++;
				i++;
				j++;
			}
			return read;
		}
		else if(n < 512){
			int j = 0;
			while(j < n){
				buf[i] = _buf[j];
				read++;
				i++;
				j++;
			}
			return read;
		}
	}
	return read;
}
