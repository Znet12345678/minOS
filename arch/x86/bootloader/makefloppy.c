#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
void usage(char *arg){
	printf("%s -b1 [bootloader_first_stage.bin] -b2 [bootloader_second_stage.bin] -k [kernel.elf] -balloc [size_for_second_stage_bootloader] -kalloc [size_for_kernel -alloc [bytes for file system]\n",arg);
}
int get_arg(char *argv[],char *arg,int argc){
	int i = 0;
	while(i < argc){
		if(strcmp(argv[i],arg) == 0)
			return i;
		i++;
	}
	return -1;
}
int write_file(int s1,int s2,char *filename){
	int total_size = s1 + s2 + 512;
	FILE *f = fopen(filename,"wb");
	if(!(f))
		return -1;
	fseek(f,total_size - 1,SEEK_SET);
	fputc(0,f);
	fclose(f);
	return 0;
}
int write_to_file(char *read,char *write,int pos){
	FILE *fw = fopen(write,"r+b");
	FILE *fr = fopen(read,"rb");
	if(!(fw)){
		printf("Error opening %s for writing\n",write);
		return -1;
	}
	if(!(fr)){
		printf("Error opening %s for reading\n",read);
		return -1;
	}
	fseek(fw,pos,SEEK_SET);
	int c;
	while((c = fgetc(fr)) != EOF)
		fputc(c,fw);
	fclose(fw);
	fclose(fr);
	return 0;
}
int get_size(char *fname){
	FILE *f = fopen(fname,"rb");
	fseek(f,0,SEEK_END);
	int i = ftell(f);
	return i;
}
int main(int argc,char *argv[]){
	if(argc != 11 && argc != 13){
		usage(argv[0]);
		return -1;
	}
	if(write_file(atoi(argv[get_arg(argv,"-balloc",argc) + 1]),atoi(argv[get_arg(argv,"-kalloc",argc) + 1]),"floppy.img") < 0){
		printf("Error writing file!\n");
		return -1;
	}
	if(write_to_file(argv[get_arg(argv,"-b1",argc) + 1],"floppy.img",0) < 0)
		return -1;
	if(write_to_file(argv[get_arg(argv,"-b2",argc) + 1],"floppy.img",512) < 0)
		return -1;
	if(get_size(argv[get_arg(argv,"-b2",argc) + 1]) < atoi(argv[get_arg(argv,"-balloc",argc) + 1])){
		FILE *f = fopen("floppy.img","r+b");
		if(!(f)){
			printf("Error writing to file!\n");
			return -1;
		}
		fseek(f,512 + get_size(argv[get_arg(argv,"-b2",argc) + 1]),SEEK_SET);
		int ztr = atoi(argv[get_arg(argv,"-balloc",argc) + 1]) - get_size(argv[get_arg(argv,"-b2",argc) + 1]) ;
		for(int i = 0; i < ztr;i++)
			fputc(0,f);
		fclose(f);
	}
	if(write_to_file(argv[get_arg(argv,"-k",argc) + 1],"floppy.img",512 +  atoi(argv[get_arg(argv,"-balloc",argc) + 1])) < 0){
		return -1;
	}
	if(get_size(argv[get_arg(argv,"-k",argc) + 1]) < atoi(argv[get_arg(argv,"-kalloc",argc) + 1])){
		FILE *f = fopen("floppy.img","r+b");
		if(!(f)){
			printf("Error writing to file!\n");
			return -1;
		}
		fseek(f,512 + atoi(argv[get_arg(argv,"-balloc",argc) + 1]),SEEK_SET);
		int ztr = atoi(argv[get_arg(argv,"-kalloc",argc) + 1]) - get_size(argv[get_arg(argv,"-k",argc) + 1]);
		for(int i = 0; i < ztr; i++)
			fputc(0,f);
		fclose(f);
	}
	if(get_arg(argv,"-alloc",argc) != -1){
		FILE *f = fopen("floppy.img","r+b");
		if(!(f)){
			printf("Error writing to file!\n");
			return -1;
		}
		fseek(f,0,SEEK_END);
		for(int i = 0; i < atoi(argv[get_arg(argv,"-alloc",argc) + 1]);i++){
			fputc(0,f);
		}
		fclose(f);
	}
	printf("done writing floppy.img\n");
	return 0;
}
