#include <stdio.h>
int main(int a,char *b[]){
	int i = 0;
	while(i < (a - 2)){
		kprintf("%s",b[i]);
		i++;
	}
}
