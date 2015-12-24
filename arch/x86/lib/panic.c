#include "panic.h"
void panic(){
	kprintf("A fatal error has been encountered in the kernel. Panic has been called.\n");
	kprintf("minOS Alpha\n");
	kprintf("panic()\n");
	//#ifdef DEV
	kprintf("Development build dumping Kernel Arguments\n");
	//dump_args("Unkown");
//	#endif
	while(1){ }
	_panic();
}
void __panic(char *reason){
	kprintf("Panic Reason:%s\n",reason);
	dump_args(reason);
	panic();
}
