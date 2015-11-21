void panic(){
	kprintf("A fatal error has been encountered in the kernel. Panic has been called\n");
	kprintf("panic()\n");
	#ifdef DEV
	//kprintf("Development build dumping Kernel Arguments\n");
	//dump_args();
	#endif
	while(1){ }
	_panic();
}
