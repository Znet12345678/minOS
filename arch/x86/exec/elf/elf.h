/*
*ELF Loader
*Written by Zachary James Schlotman
*/
#ifndef __ELF_H
#define __ELF_H
#include <stdint.h>
#include <kernel/zfs.h>
struct elf_header{
	uint32_t magic_num; /*3 bits long Magic ELF Number 0x7F ELF*/
	uint32_t arch;/*1 32 bit 2 64 bit*/
	uint32_t endian;/*1 little endian, 2 big endian*/
	uint32_t version;/*ELF version*/
	uint32_t osabi;/*OS ABI*/
	uint32_t type;/*1 relocatable,2 executable, 3 shared, 4 core*/
	uint32_t insset;/*0x3 x86(what we want) 0x3E x86_64,etc*/
	uint32_t version2;
	uint32_t program_entry;/*Where program enters*/
	uint32_t phtp;/*Header table pos*/
	uint32_t shtp;/*Section header table pos*/
	uint32_t flags;
	char *sig;
	uint32_t header_size;
	uint32_t entry_size;
	uint32_t numberofentries;/*Program header table*/
	uint32_t sizeofentryph;/*Size of entries on program header table*/
	uint32_t numofentries;/*Section header table*/
	uint32_t shsize; /*Section header size*/
	uint32_t index;
	uint32_t err;
};/*Header for elf files.*/
struct program_header_32{
	uint32_t typeofsegment;
	uint32_t offset;
	uint32_t p_vaddr;
	uint32_t p_filesz;
	uint32_t p_memsz;
	uint32_t flags;
	uint32_t alignment;
	uint32_t err;
};

struct elf_header *parse_header(struct file_struct *f);/*Returns pouint32_ter to elf header struct*/
void write_mem(unsigned char *pntr, uint32_t c);/*Writes c to memory pouint32_ter pntr*/
struct program_header_32 * parse_ph(struct file_struct *f, struct elf_header *h);/*Returns pouint32_ter to program header*/
uint32_t elf_exec(unsigned char *text,unsigned char *data,struct elf_header *h,struct program_header_32 *ph32,unsigned char *mem);

#endif
