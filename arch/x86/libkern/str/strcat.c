/*
*minOS Kernel Libray
*Public Domain
*Strcat function
*/
#include <libkern.h>
void strcat(char *dest,const char *src){
	strcpy(&dest[strlen(dest)],src);
}
