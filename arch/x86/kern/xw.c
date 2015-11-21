#include <stdint.h>
#include <asm.h>
static inline uint8_t inw(uint16_t port){
	uint8_t ret;
	asm volatile("inw %1, %0" : "=a"(ret) :"Nd"(port));
	return ret;
}
