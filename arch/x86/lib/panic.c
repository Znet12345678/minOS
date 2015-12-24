/*
*More panic Functions
*(c) 2015 Zachary James Schlotman
*Zachary Schlotman
*/
#include "panic.h"
void panic(){
	t_init();
	kprintf("A fatal error has been encountered in the kernel. Panic has been called.\n");
	kprintf("Continuing is not possible or is dangerous\n");
	kprintf("minOS kernel\n");
	kprintf("If you are getting a panic it is most likely that your hardware is not supported.\nThis works best in QEMU\n");
	kprintf("This build will NOT continue after a panic.");
	dump_args("NULL");
	//#ifndef NOPANIC
	while(1){ }
	//#endif
	//_panic();
}
void __panic(char *reason){
	kprintf("Panic Reason:%s\n",reason);
	dump_args(reason);
	panic();
}
