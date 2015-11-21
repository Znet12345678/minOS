#include <stdint.h>
#include <asm.h>
void inportsl(unsigned short _port,unsigned long *_buff,unsigned _len){
	int i = 0;
	while(i < _len){
		unsigned long o = inportb(_port);
		_buff[i] = o;
		i++;
	}
}

void insl(unsigned short _port,unsigned long *_buff,unsigned _len){
        asm("cld; rep; insl" :: "D" (_buff), "d" (_port), "c" (_len));
}
uint8_t inw(uint16_t port){
	uint8_t ret;
	asm volatile("inw %1,%0" :"=a"(ret):"Nd"(port));
	return ret;
}
