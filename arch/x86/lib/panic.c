/*
*More panic Functions
*(c) 2015 Zachary James Schlotman
*Zachary Schlotman
*/
#include "panic.h"
void panic(){
	kprintf("A fatal error has been encountered in the kernel. Panic has been called.\n");
	kprintf("Continuing is not possible or is dangerous\n");
	kprintf("minOS kernel\n");
	while(1){ }
	_panic();
}
void __panic(char *reason){
	kprintf("Panic Reason:%s\n",reason);
	dump_args(reason);
	panic();
}
