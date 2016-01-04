/*
*minOS libkern header
*This containes all the functions that are
*present in this library. This library will
*likely not be used until later on in the 
*development of this kernel. It is just now 
*being layed out. It is not by any means
*a stand alone c library. Once this kernel
*is complete it will contain the syscalls
*for io.
*/
#ifndef __LIBKERN_H
#define __LIBKERN_H
unsigned long strlen(const char *str); /*Returns length of string*/
int strcmp(const char *str1,const char *str2); /*Returns 0 if strings are equal. If they are not it returns the value + 1 of which they diverge.*/
void strcpy(char *str1,const char *str2); /*Copies str2 to end of str1. Works best for malloced strings*/
void strcat(char *str1,const char *str2); /*Copies str2 to end of str1. Works best for everything else*/
int strncmp(const char *str1,const char *str2,unsigned long n); /*Compares the two strings until after n bytes have been compared*/
int strncpy(char *str1,const char *str2,unsigned long n); /*Copies n bytes of str2 to end of str1. Works best for malloced strings*/
int strncat(char *str1, const char *str2,unsigned long n); /*copies n bytes of str2 to end of str1. Works best for everything else*/
void *malloc(unsigned long n);/*Allocates n bytes for pointer*/
int printf(const char *str, ...);
#ifdef COMPLETED_KERNEL
#include <minfs.h>
struct FILE{
	unsigned long offset;
	unsigned long endoffset;
	struct block *ptr;
};
int open(char *path,char *op);
int read(struct FILE *file,char *buf,int n);/*reads n bytes of file to buf*/
int write(struct FILE *file,char *buf,int n); /*writes n bytes of buf to file*/
#else
int read(int lba,char *buf,int n);/*Reads n bytes of raw data at lba to buf*/
int write(int lba,char *buf,int n);/*Writes n bytes of buf to drive at lba*/
#endif
#endif
