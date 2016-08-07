#ifndef __MINOS_IO_H
#define __MINOS_IO_H
#include <stdint.h>
static inline void outsw(unsigned short int port,const void *val,unsigned long int n);
//static inline void outsw(uint16_t port,uint8_t val);
static inline void outw(uint16_t port,uint8_t val);
inline static void outb(uint16_t port,uint8_t val);
inline static uint16_t inb(uint32_t s);
static inline uint16_t inw(uint32_t s);
static inline uint16_t inportb(uint32_t s);
static inline void outb(uint16_t port,uint8_t val){
     __asm__ volatile ("outb %w0, %w1" : : "a"(val), "Nd"(port));
}
static inline uint16_t inb(uint32_t port){
        uint16_t ret;
        __asm__ volatile("inw %%dx, %%ax": "=a"(ret):  "d"(port));
        return ret;
}
static inline uint16_t inportb(uint32_t port){
        return inb(port);
}

static inline void outw(uint16_t port,uint8_t val){
     __asm__ volatile ("outw %w0, %w1" : : "a"(val), "Nd"(port));
}
static inline void outsw(unsigned short int port,const void *val,unsigned long int n){
        unsigned long cnt = 1;
        __asm__ volatile ("rep outsw" :  "+S"(val),"+c"(n) : "d"(port));
}
static inline uint16_t inw(uint32_t s){
        uint16_t ret;
        __asm__ volatile("inw %%dx, %%ax": "=a"(ret):  "d"(s));
        return ret;
}
int ata_check_lba(uint32_t lba);
int ata_read_master_n(uint8_t *buf,uint32_t lba,unsigned int n);
int ata_read_master_no(uint8_t *buf,uint32_t lba,unsigned int offset,unsigned int n);
int ata_read_master(uint8_t *buf,uint32_t _lba,uint16_t drive);
int ata_write_master_n(uint8_t *buf,uint16_t lba,unsigned int n);
int ata_write_master_no(uint8_t *buf,uint16_t lba,unsigned int offset,unsigned int n);
int ata_write_master(uint8_t *buf,uint16_t lba);
int ata_write_master_no_no_ow(uint8_t *buf,uint16_t _lba,unsigned int offset,unsigned int n);
#endif
