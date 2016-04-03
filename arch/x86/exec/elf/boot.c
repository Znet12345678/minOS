/*
*Parses and boots kernel
*(c)2016 Zachary James Schlotman
*/
#include "elf.h"
#include <stdlib.h>
#define BAD_ARCH -1
#define BAD_ENDIAN -2
#define BAD_INSTRUCTION_SET -3
int read_memory(char *buf,unsigned char *mem,int n){
	for(int i = 0; i < n;i++){
		buf[i] = *mem
		*mem++
	}
	return 1;
}
struct elf_header *parse_elf_header(unsigned char *loc,int n){
	unsigned char *buf = malloc(1024);
	read_memory(buf,loc,n);
	struct elf_header *ret = malloc(1024);
	if(buf[0] != 0x7F || buf[1] != 'E' || buf[2] != 'L' || buf[3] != 'F')
		return (struct elf_header *)-1;
	ret->arch = buf[4];
	if(ret->arch != 1)
		return BAD_ARCH;
	ret->endian = buf[5];
	ret->version = buf[6];
	ret->osabi = buf[7];
	
	return ret;
}
int multiboot(unsigned char *loc,int n){
	struct elf_header *elfh;
	if(!(parse_elf_heaader(loc,n)))
		return -1;
}
int exec_elf_kernel(){
	if(multiboot((unsigned char *)0x00007C00,512) < 0){
		kprintf("Failed to boot kernel!\n");
		kprintf("Memory in undesirable condition!\n");
		panic();
	}
	return 1;
}

