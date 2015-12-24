/*
*minOS kernel (c) 2015 Zachary James Schlotman
*panic functions
*/
#include <stdio.h>
void _panic(){
	kprintf("Secondary Kernel panic{_panic();} has been called. It is recommended to reboot. If this is a development build please submit the issue to the developer.\n\n\n\n");
	kprintf("Press any key to try again\n");
	int prevc = inb(0x60);
	int i = 0;
	while(1) {
		int c = inb(0x60);
		if(c != prevc )
			break;
		//asm volatile("cli;hlt");
	}
	void *unreachable = malloc(1024);
}
char *__kgets(){
	int i = 0;
	int c;
	int oldc;
	char *buf = malloc(1024);
	while(1){
		if(c == '\n')
			break;
		if(c == oldc)
			break;
		c = oldc;
		kstrcat(buf,&c);
	}
	return buf;
}
void panic_shell(){
	//char *buf;
	kprintf("A semi-fatal panic has been encountered.\nYou will be dropped into a minimalistic shell\n");
	while(1){
		char buf[80];
		//char *buf = malloc(1024);
		kprintf("panic-sh@minOS#");
		kstrcpy(buf,kgets());
		//kprintf("ISSUE:%s\n",buf);
		if(strncmp(buf,"help",4) == 0){
			kprintf("\npanic\nhalt");
		}
		else if(strncmp(buf,"panic",5) == 0){
			panic();
		}
		else if(strncmp(buf,"halt",4) == 0){
			halt();
		}
		else{
			kprintf("Invalid command:%s\n",buf);
		}
		kprintf("\n");
	}
}
