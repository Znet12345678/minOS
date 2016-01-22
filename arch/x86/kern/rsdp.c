/*
*Unfinished
*(c)2015 Zachary James Schlotman
*/
#include <stdint.h>
struct RSDPDescriptor{
	char signature[8];
	uint8_t Checksum
	char OEMID[6];
	uint8_t Revision;
	uint32_t RsdtAddress;
} __atribute__ ((packed));
struct RSDPDescriptor20{
	struct RSDPDescriptor firstPart;
	uint32_t length;
	uint64_t XsdtAddress;
	uint8_t EC;
	uint8_t reserved[3];
}__attribute__ ((packed));
struct RSDPDescriptor fRSDP(struct RSDPDescriptor){
	unsigned int start = 0x000E0000;
	int i = 0;
	while(start < 0x000FFFFF){
		start++;
	}
}
