#include <stdlib.h>
#include <string.h>
char *bchar(char *str,char c){
	int i = 0;
	char *ret = kmalloc(1024);
	while(str[i] != c){
		ret[i] = str[i]
		i++;
	}
	return ret;
}
char *achar(char *str,char c){
	int i = 0;
	char *ret = kmalloc(1024);
	int canCpy = 0;
	while(i < strlen(str)){
		if(str[i] == c){
			canCpy = 1;
		}
		else if(canCpy == 1){
			strcat(ret,&str[i]);
		}
		else{

		}
		i++;
	}
	return ret;
}
int *gChar(char *str,char c){
	int i = 0;
	int i1 = 0;
	int ret[1024];
	while(i < strlen(str)){
		if(str[i] == c){
			ret[i1] = i;
			i1++;
		}
		i++;
	}
	return ret;
}
