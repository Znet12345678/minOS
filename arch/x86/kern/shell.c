/*
*public domain
*Zachary James Schlotman
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_COMMANDS 100
int scmp(const char *str1,const char *str2,unsigned int n){
	unsigned int i = n;
	int i1 = 0;
	while(i1 < strlen(str2)){
		//kprintf(".");
		if(str1[i] != str2[i1])
			return ++i;
		i1++;
		//kprintf(".");
		i++;
	}
	return 0;
}
void shell_process(const char *str){
	char *arg1 = malloc(1024);
	char *args = malloc(1024);
	int i = 0;
	while(str[i] != ' ' && str[i] != 0x00){
		//kprintf(".");
		arg1[i] = str[i];
		i++;
	}
	arg1[i] = 0;
	//kprintf("%s",arg1);
	const char *commands[MAX_COMMANDS] = { 0 };
	const char *response[MAX_COMMANDS] = { 0 };
	commands[0] = "version";
	commands[1] = "ls";
	commands[2] = "help";
	commands[3] = "commands";
	commands[4] = "contact";
	commands[5] = "copyright";
	commands[6] = "boot";
	//commands[7] = "calc";
	response[0] = "v0.3-alpha\n";
	response[1] = "No File System completed\n";
	char lc[3] = {0x0A,'l','c'};
	response[2] = lc;
	response[3] = lc;
	response[4] = "Email:znet12345678@gmail.com Phone:972-800-8197\n";
	response[5] = "(c) 2016 Zachary James Schlotman";
	char b[2] = {0x0A,'b'};
	response[6] = b;
	//char c[2] = {0x0A,'c'};
	//response[7] = c;
	//int i;
	for(i = 0; i < MAX_COMMANDS;i++){
		if(strcmp(arg1,commands[i]) == 0){
			if(response[i][0] == 0x0A){
				if(scmp(response[i],"lc",1) == 0){
					kprintf("\nCommands:\n");
					for(int j = 0; j < MAX_COMMANDS; j++){
						if(commands[j] != 0)
							kprintf("%s",commands[j]);
						if(commands[j][0] != 0)
							kprintf(" ");
					}
				}
				else if(scmp(response[i],"b",1) == 0){
					kprintf("\nReading first sector of hd then jumping to it\n");
					char *buf = malloc(1024);
					ata_read_master(buf,0,0);
					kprintf("Writing to memory:0x01000000\n");
					char *mem =(char *)0x01000000;
					for(int i = 0; i < 512;i++){
						//kprintf(".");
						//write_memory(mem,buf[i]);
						*mem = buf[i];
						//	kprintf("%c.%c",buf[i],*mem);
						*mem++;
					}
					//kprintf("%c\n",(int)0x10000000);
					//kprintf("%c\n",buf[0]);
					//if((int)0x00100000 == buf[1])
					//	kprintf("Y\n");
					//else
					//	kprintf("N\n");
					//for(int i = 0; i < 100;i++){
					//	kprintf("%c",buf[i]);
					//}
					//char *pntr = (char*)0x00100000;
					//kprintf("\n");
					//for(int i = 0; i < 100; i++){
					//	kprintf("%c",*pntr);
					//	*pntr++;
					//}
					//kprintf("%c.%c\n",0x00100001,buf[0]);
					//jmp_boot();
					//go_real();
					//chainload();
					//chainload();
					kprintf("Jumping to memory location!\nThis won't work if the program requires real mode!\n");
					__asm__ ("jmp 0x01000000");
					panic();
					//asm("JMP 0xA0000000");
				}
				//else if(scmp(response[i],"c",1) == 0){
				//	calculator_init();
				//	calculator();
				//}
				//else
				//	kprintf(".");
			}
			else
				kprintf("\n%s",response[i]);
			break;
		}

	}
	if(i >= MAX_COMMANDS - 1)
		kprintf("\nUnkown command!\n");

}
#ifndef __LIB_BUILD
void *_fmalloc(unsigned long s){
        char ret[s];
        return (void *)ret;
}
#else
void *fmalloc(unsigned long s){
	char ret[s];
	return (void *)ret;
}
#endif
char *_kgets(){
        char *args =fmalloc(80);
        char oldc = '\n';
        char c;
        int i = 0;
        while(1){
                c = kgetc();
                if(c == oldc)
                        continue;
                if(c == '\001')
                        continue;
                oldc = kgetc();
                if(c == '\n')
                        break;
                if(inportb(0x60) == 0x1C)
                        break;
                t_putc(c);
                args[i] = c;
                i++;

        }
         i = 0;
        return args;
}
void call(char *func,char *args){
		//asm("push %esp, offset %P0" : : "m"(args));
		//asm("call %P0" : : "m"(func));
		//asm("pop %esp");
}
void zsh(){
	t_init();
	kprintf("zOS precompiled shell\n");
	while(1){
		//char *s = malloc(1024);
		char s[80];
		kprintf("#");
		kstrcpy(s,_kgets());	
		char args[80];
		int i = 0;
		int b = 0;
		while(s[i] != 0){
			if(s[i] == ' ')
				b = 1;
			if(b == 1)
				kstrcat(args,&s[i]);
			i++;
		}
		call(s,args);
	}
}
