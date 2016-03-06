#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int mkfszfs(char *filename){
	FILE *f;
	printf("Getting file size\n");
	if(!(f = fopen(filename,"r")))
		return -1;
	fseek(f,0,SEEK_END);
	int i = ftell(f);
	printf("Size:%d bytes\n",i);
	fseek(f,0,SEEK_SET);
	fclose(f);
	if(!(f = fopen(filename,"w")))
		return -1;
	printf("Zeroing file\n");
	for(int j = 0; j < i;j++){
		fputc(0,f);
	}
	printf("Writing superblock\n");
	fseek(f,1024,SEEK_SET);
	fputc(0,f);
	fputc(0,f);
	fputc(0,f);
	fputc((i / 512) >> 16,f);
	fputc((i / 512) >> 8,f);
	fputc((i / 512),f);
	fputc((i / 512) >> 16,f);
	fputc((i / 512) >> 16,f);
	fputc((i / 512),f);
	fputc(0,f);
	fputc(50,f);
	fputc(0,f);
	fputc(51,f);
	fputc(0,f);
	fputc(0,f);
	fputc(0,f);
	fputc(0,f);
	fputc(0,f);
	fputc(1,f);
	fputc(2,f);
	fputc(0,f);
	printf("Finished writing superblock\n");
	
}
int main(int argc, char *argv[]){
	if(argc != 2)
		return -1;
	mkfszfs(argv[1]);
}
