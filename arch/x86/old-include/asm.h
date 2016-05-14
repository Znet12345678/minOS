#ifndef __ASM_H
#define __ASM_H
#include <stdint.h>
static inline uint8_t inw(uint16_t s);
static inline void outw(uint16_t port,uint8_t val);
#endif
