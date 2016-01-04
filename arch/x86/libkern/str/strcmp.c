/*
*minOS kernel library
*Public domain
*strcmp function
*/
#include <libkern.h>
int strcmp(const char *cmp1,const char *cmp2){
	int i = 0;
	while(i < strlen(str)){
		if(cmp1[i] != cmp2[i])
			return (++i);
		i++;
	}
	return 0;
}
