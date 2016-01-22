/*
*minOS libkern library
*Public domain
*strlen function
*/
#include <libkern.h>
unsigned long strlen(const char *str){
	unsigned long i = 0;
	while(str[i] != 0)
		i++;
	return i;
}
