#ifndef __MINOS_STDIO_H
#define __MINOS_STDIO_H
void kprintf(const char *format,...);
void kputs(const char *str);
void kputc(int ic);
void debug(char *proccess,char *output);
char *kgets();
char kgetc();
#endif
