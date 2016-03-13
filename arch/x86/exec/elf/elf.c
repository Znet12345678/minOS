/*
*minOS ELF loader
*Written by Zachary James Schlotman
*/
#include "elf.h"
#include <kernel/zfs.h>
#include <stdio.h>
#include <stdlib.h>

void write_memory(const char *addr,int value){
	*addr = value;
}
void bin_error(){
	kprintf("Couldn't execute binary file!\n");
}
struct elf_header *parse_header(struct file_struct *f){
	struct elf_header *ret = malloc(sizeof(elf_header *));
	char sig[4];
	fs_read(sig,f,4);
	ret->err = 0;
	if(sig[0] == 0x7F && sig[1] == 'E' && sig[2] == 'L' && sig[3] == 'F')
		ret->sig = sig;
	else{
		bin_error();
		ret->sig = sig;
		ret->err = 1;
		return ret;
	}
	char i;
	fs_read(&i,f,1);
	if(i != 1){
		bin_error();
		ret->arch = i;
		ret->err = 1;
		return ret;
	}
	fs_read(&i,f,1);
	if(i != 1 && i != 2){
		bin_error();
		ret->endian = i;
		ret->err = 1;
		return ret;
	}
	fs_read(&i,f,1);
	ret->version = i;
	fs_read(&i,f,1);
	ret->osabi = i;
	char *garbage = malloc(1024);
	fs_read(garbage,f,8);
	char type[2];
	fs_read(type,f,2);
	ret->type = type[0] << 8 | type[1];
	char inst[2];
	fs_read(inst,f,2);
	ret->inst = inst[0] << 8 | inst[1];
	if(inst != 0x3){
		bin_error();
		ret->err = 1;
		return ret;
	}
	char vers[4];
	fs_read(vers,f,4);
	ret->version2 = vers[0] << 16 | vers[1] << 16 | vers[2] << 8 | vers[3];
	char entry[4];
	fs_read(entry,f,4);
	ret->program_entry = entry [0] << 16 | entry[1] << 16 | entry[2] <<8 | entry[3];
	char phtp[4];
	fs_read(phtp,f,4);
	ret->phtp = phtp[0] << 16 | phtp[1] << 16 | phtp[2] << 8 | phtp[3];
	char shtp[4];
	fs_read(shtp,f,4);
	ret->shtp = shtp[0] << 16 |shtp[1] << 16 | shtp[2] << 8 | shtp[3];
	char flags[4];
	fs_read(flags,f,4);
	ret->flags = flags[0] << 16 | flags[1] << 16 | flags[2] << 8 | flags[3];
	char header_size[2];
	fs_read(header_size,f,2);
	ret->header_size = header_size[0] << 8 | hear_size[1];
	char size[2];
	fs_read(size,f,2);
	ret->entry_size = size[0] << 8 | size[1];
	char number[2];
	fs_read(number,f,2);
	ret->numberofentries = number[0] << 8 | number[1];
	char shsize[2];
	fs_read(shsize,f,2);
	ret->shsize = shsize[0] << 8 | shsize[1];
	char num[2];
	fs_read(num,f,2);
	ret->numofentries = num[0] << 8 | num[1];
	char index[2];
	fs_read(index,f,2);
	ret->index = index[0] << 8 | index[1];
	return ret;
}
struct program_header_32 * parse_ph(struct file_struct *f, struct elf_header *h){
	struct program_header_32 *ret = malloc(sizeof(program_header_32 *));
	if(h->arch != 1){
		bin_error();
		ret->err = 1;
		return ret;
	}
	char type[4];
	seek(f,h->phtp);
	read(type,f,4);
	ret->typeofsegment = type[0] << 16 | type[1] << 16
}
void elf_exec(const char *text,unsigned char *data,struct elf_header *h,struct program_header_32 *ph32,unsigned char *mem){
	
}


