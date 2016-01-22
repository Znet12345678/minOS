#ifndef __ZTTY_H
#define __ZTTY_H
#include <stddef.h>
#include <kernel/types.h>
extern void t_init();
extern void t_putc(char c);
extern void t_write(const char *msg,ksize_t s);
extern void t_writestr(const char *msg);
#endif
