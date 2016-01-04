/*
*minOS libkern library
*Public domain
*strncmp function
*/
#include <libkern.h>
int strncmp(const char *str1,const char *str2,unsinged long n){
	int i = 0;
	while(i < n){
		if(str1[i] != str2[i])
			return (++i);
		i++;
	}
	return 0;
}
