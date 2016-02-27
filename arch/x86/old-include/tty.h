#ifndef __ZTTY_H
#define __ZTTY_H
#include <stddef.h>
#include <kernel/types.h>
void t_init();
void t_putc(char c);
void t_write(const char *msg,ksize_t s);
void t_writestr(const char *msg);
void place_cursor();
#endif
