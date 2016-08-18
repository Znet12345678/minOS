/*
*minOS memory allocater
*Writen by:Zachary James Schlotman
*Public Domain
*/
#include <stdlib.h>
int malloc_init(){
	/*int *pntr = (int*)0x00100000;
	int mem = 0x00100000;
	while(mem < 0x00EFFFFF){
		*pntr = 1;
		*pntr++;
		mem++;
	}
	*pntr = 0x0f;
	*pntr = 0x3a;*/
}
void *malloc(unsigned long n){
	char *membuf;
	char *pntr = (char*)0x01000000;
	char mem = 0x01000000;
	int i = 0;
	while(i < n){
		if(*pntr == 1){
			*pntr++;
			mem++;
			continue;
		}
		else{
			*membuf = *pntr;
			*pntr = 1;
			*pntr++;
			*membuf++;
			mem++;
		}
		i++;
	}
	membuf[n] = 0x0f;
	membuf[n + 1] = 0x1f;
	return (void *)membuf;
}
int free(void *v){
	char *membuf = (char *)v;
	int i = 0;
	while(1){
		if(*membuf == 0x0f)
			if(*++membuf == 0x1f)
				break;
		*membuf = 0;
		*membuf++;
	}
	void *_v;
	v = _v;
	return 1;
}
void *kmalloc(unsigned long n){
	void *ret;
	char *membuf;
	int *pntr = (int*)0x00100000;
	int i = 0;
	while(i < n){
		if(*pntr == 1){
			*membuf = *pntr;
			*pntr = 0;
			*pntr++;
			*membuf++;
		}
		else{
			*pntr++;
			continue;
		}
		i++;
	}
        membuf[n + 1] = 0x0f;
        membuf[n + 2] = 0x1f;

	return (void *)membuf;
}
