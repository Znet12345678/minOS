#include <stdint.h>
static inline uint16_t inw(uint32_t s){
        uint16_t ret;
        asm volatile("inw %%dx, %%ax": "=a"(ret):  "d"(s));
        return ret;
}

