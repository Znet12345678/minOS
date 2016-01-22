#ifndef __Z_VGA_H
#define __Z_VGA_H
#include <stdint.h>
#include <kernel/types.h>
enum vga_colour{
	COLOUR_BLACK = 0,
	COLOUR_BLUE = 1,
	COLOUR_GREEN = 2,
	COLOUR_CYAN = 3,
	COLOUR_RED = 4,
	COLOUR_MAGENTA = 5,
	COLOUR_BROWN = 6,
	COLOUR_LIGHT_GREY = 7,
	COLOUR_DARK_GREY = 8,
	COLOUR_LIGHT_BLUE = 9,
	COLOUR_LIGHT_GREEN = 10,
	COLOUR_LIGHT_CYAN = 11,
	COLOUR_LIGHT_RED = 12,
	COLOUR_LIGHT_MAGENTA = 13,
	COLOUR_LIGHT_BROWN = 14,
	COLOUR_WHITE = 15,
};
static inline uint8_t mkcolour(enum vga_colour fg,enum vga_colour bg){
	return fg | bg << 4;
}
static inline uint16_t mkent(char c,uint8_t colour){
	uint16_t c16 = c;
	uint16_t colour16 = colour;
	return c16 | colour16 << 8;
}
static const ksize_t VW = 80;
static const ksize_t VH = 25;
static uint16_t* const VMEM = (uint16_t*) 0xB8000;
#endif
