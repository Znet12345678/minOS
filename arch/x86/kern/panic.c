
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
