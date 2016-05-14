#ifndef __Z_STRING_H
#define __Z_STRING_H
unsigned long strlen(const char *str);
int strcmp(const char *s1,const char *s2);
int strncmp(const char *s1,const char *s2,unsigned long n);
void kstrcpy(char *dest,const char *src);
void kstrcat(char *dest,const char *src);
void *memcpy(void *dest,const void *src,unsigned long s);
void* memmove(void* dstptr, const void* srcptr, unsigned long size);
void *memset(void* bufptr, int value, unsigned long size);
#endif
