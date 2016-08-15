#include <stdlib.h>
int malloc_init(){
	int *pntr = (int*)0x01000000;
	int mem = 0x01000000;
	while(mem < 0x01FFFFFF){
		*pntr = 1;
		*pntr++;
		mem++;
	}
}
void *malloc(unsigned long n){
	void *ret;
	char *membuf;
	int *pntr = (int*)0x01000000;
	int i = 0;
	while(i < n){
		if(*pntr == 1){
			*pntr = 0;
			*membuf = *pntr;
			*pntr++;
			*membuf++;
		}
		else{
			*pntr++;
			continue;
		}
		i++;
	}
	return (void *)membuf;
}
