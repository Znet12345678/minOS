#include <stdio.h>
void kernel_init(){
	t_init();
	//while(1) { };
}
void kernel_main(){
	kprintf("This is your own kernel!\n");
	kprintf("If you would like you could just add your code to kern/yourkernel.c\n");
	kprintf("Or you could simply compile your c file with a void kerne_init() and void kernel_main() and then compile with $(CC) kern/yourkernel.o kern/crti.o kern/crtn.o $(CRTBEGIN) $(CRTEND) -o yourkernel.elf -nostdlib -L. -lkern -T linker.ld\n");
	kprintf("Thank you for using minOS!\n");
	while(1){ };
}
