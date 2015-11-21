/*
*Not needed a bunch of minimal function implementations for newlib
*/
#include <stdint.h>
# define __iomem        __attribute__((noderef, address_space(2)))
char _end;
typedef uint8_t u8;
static inline void writeb(u8 b, volatile void __iomem *addr)
{
         *(volatile u8 *) addr = b;
}
static inline u8 readb(const volatile void __iomem *addr)
{
         return *(const volatile u8 *) addr;
}
void _outbyte(int c)
{
        while ((readb(0x60) & 0x20) == 0)
                ;

        writeb ((char)c,0x60+1);
}

void outbyte(int c)
{
        static char prev = 0;
        if (c < ' ' && c != '\r' && c != '\n' && c != '\t' && c != '\b')
                return;
        if (c == '\n' && prev != '\r') _outbyte('\r');
        _outbyte(c);
        prev = c;
}
int close(int file) {
  return -1;
}
#include <errno.h>
#undef errno
extern int errno;
int execve(char *name, char **argv, char **env) {
  errno = ENOMEM;
  return -1;
}
#include <errno.h>
#undef errno
extern int errno;
int fork(void) {
  errno = EAGAIN;
  return -1;
}
//extern int _end;
#include <sys/stat.h>
int fstat(int file, struct stat *st) {
  st->st_mode = S_IFCHR;
  return 0;
}
int getpid(void) {
  return 1;
}
int isatty(int file) {
  return 1;
}
#undef errno
extern int errno;
int kill(int pid, int sig) {
  errno = EINVAL;
  return -1;
}
#undef errno
extern int errno;
int link(char *old, char *new) {
  errno = EMLINK;
  return -1;
}
int lseek(int file, int ptr, int dir) {
  return 0;
}
/*int read(int file, char *ptr, int len) {
  return 0;
}*/
caddr_t sbrk(int incr) {
  extern char _end;		/* Defined by the linker */
  static char *heap_end;
  char *prev_heap_end;
 
  if (heap_end == 0) {
    heap_end = &_end;
  }
  prev_heap_end = heap_end;
  /*if (heap_end + incr > ) {
    write (1, "Heap and stack collision\n", 25);
  //  panic ();
  }*/

  heap_end += incr;
  return (caddr_t) prev_heap_end;
}
int times(struct tms *buf) {
  return -1;
}
#include <errno.h>
#undef errno
extern int errno;
int unlink(char *name) {
  errno = ENOENT;
  return -1; 
}
#include <errno.h>
#undef errno
extern int errno;
int wait(int *status) {
  errno = ECHILD;
  return -1;
}
/*int write(int file, char *ptr, int len) {
  int todo;

  for (todo = 0; todo < len; todo++) {
    outbyte (*ptr++);
  }
  return len;
}*/
