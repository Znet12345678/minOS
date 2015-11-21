/*
*Not to be compiled until Mounting is implemented
*/
#include <fcntl.h>
#include <stdarg.h>
#define NULL ""
int open(const char *file,int flag,...){
	int mode;
	if(file == NULL){
		return -1;
	}
	if(flag & O_CREAT){
		va_list arg;
		va_start(arg,flag);
		mode = va_arg(arg,int);
		va_end(arg);
	}
	return -1;
}
