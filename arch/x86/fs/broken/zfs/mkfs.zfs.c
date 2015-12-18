
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
int getsize(char *path){
	//printf("%s\n","start");
	int desc = open(path,O_RDONLY);
	int size = 0;
	//printf("Meh\n");
	char *buf = malloc(1024);
	while(read(desc,buf,1) > 0){
		//printf(".");
		size++;
	}
	printf("End\n");
	return (size);
}
int mkfszfs(char *path){
	int i = open(path,O_RDWR);
	//int size = getsize(path);
	printf("Setting %s as ZFS\n",path);
	char str[] = {0x26,0x01,0x03,0x08};
	write(i,str,4);
	int i1 = 0;
	char c = 0x00;
	//char c[1048576];
	while(write(i,&c,1));
	char end[] = {0xFF,0xAA,0x00};
}
int main(int a,char *b[]){
	if(a < 2){
		printf("Usage: %s dev\n",b[0]);
		return 0;
	}
	else{
		mkfszfs(b[1]);
	}
}
