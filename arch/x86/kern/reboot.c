#include <stdint.h>
void reboot(){
	debug("KERNEL","Halting System NOW!");
	uint8_t good = 0x02;
	while(good & 0x02)
		good = inb(0x64);
	outb(0x64,0xFE);
	asm volatile("hlt");
	//debug("KERNEL","hlt");
	//debug("KERNEL","hang");
	//while(1){ };
}
