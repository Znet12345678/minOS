#ifndef __Z_STDLIB_H
#define __Z_STDLIB_H
void *malloc(unsigned long s);
void panic();
void t_displayl();
void t_displaylq();
void sleep(int n);
int free(void *v);
int malloc_init();
int atoi(const char *str);
#define LAST_MEM_SEGMENT 0x1f
struct memory_data{
	int sig;
	int alloc;
	int size;
	int pntr;
};
#endif
