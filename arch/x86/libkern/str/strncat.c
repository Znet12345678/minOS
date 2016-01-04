/*
*minOS libkern
*public domain
*strncat function
*/
#include <libkern.h>
void strncat(char *dest,const char *src,unsigned long n){
	int i = 0;
	int i1 = strlen(dest);
	char *buf = malloc(1024);
	while(i < n){
		buf[i] = src[i];
	}
	i = 0;
	strcpy(&dest[strlen(dest)],buf);
}
