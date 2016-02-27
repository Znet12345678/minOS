#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
int write_initial_header_zbin_i386(const char *filename){
	FILE *f;
	if(!(f = fopen("out.zbin","w"))){
		return -1;
	}
	fputc(0x0A,f);
	fputc(1,f);
	fputc(2,f);
	fputc(0xFF,f);
	fputc(0xFF,f);
	for(int i = 0; i < 507;i++){
		fputc(0,f);
	}
	fclose(f);
	return 1;
}
int write_initial_header_zexec_i386(const char *filename){
	FILE *f;
	if(!(f = fopen("out.zexec","w")))
		return -1;
	fputc(0x0A,f);
	fputc(1,f);
	fputc(1,f);
	fputc(0xFF,f);
	fputc(0xFF,f);
	for(int i = 0; i < 507;i++){
		fputc(0,f);
	}
	fclose(f);
	return 1;
}
int write_initial_header_zbin_generic(const char *filename){
	FILE *f;
	if(!(f = fopen("out.zexec","w")))
		return -1;
	fputc(0x0A,f);
	fputc(4,f);
	fputc(2,f);
	fputc(0xFF,f);
	fputc(0xFF,f);
	for(int i = 0; i < 507;i++){
		fputc(0,f);
	}
	fclose(f);
	return 1;
}
void assemble_raw(const char *filename){

}
void assemble_zbin(const char *filename){
	write_initial_header_zbin_i386(filename);
	char *binbuf = malloc(102400);
	
}
void assemble_zexec(const char *filename){
	write_initial_header_zexec_i386(filename);
}
void usage(const char *name){
	printf("Usage:%s -f fmt input\n",name);
}
int main(int argc,const char *argv[]){
	if(argc != 4){
		usage(argv[0]);
		return -1;
	}
	else{
		if(strcmp(argv[1],"-f") != 0){
			usage();
			return -1;
		}
		if(strcmp(argv[2],"bin") == 0)
			assemble_raw(argv[3]);
		else if(strcmp(argv[2],"zbin") == 0)
			assemble_zbin(argv[3]);
		else if(strcmp(argv[2],"zexec") == 0)
			assemble_zexec(argv[3]);
		else
			assemble_raw(argv[3]);
	}
}
