//
//  PCI.c
//  
//
//  Created by Zach Schlotman on 4/25/16.
//
//

#include "PCI.h"
#include <stdint.h>
uint32_t inl(uint16_t port){
    uint32_t ret;
    __asm__ volatile ("inl %w1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}
uint32_t outl(uint16_t port,uint32_t data){
    asm volatile ("outl %0, %w1" : : "a" (data), "Nd" (port));
}
uint16_t pci_cfg_read_word(uint8_t bus,uint8_t slot,uint8_t func,uint8_t offset){
    uint32_t addr;
    uint32_t lbus = (uint32_t)bus;
    uint32_t lslot = (uint32_t) slot;
    uint32_t lfunc = (uint32_t)lfunc;
    uint16_t ret = 0;
    address = (uint32_t)((lbus << 16) | (lslot << 11) | (lfunc << 8) | offset & 0xfc) | ((uint32_t)0x80000000));
    outl(0xCF8,address);
    ret = (uint16_t)(( inl(0xCFC) >> ((offset & 2) * 8)) & 0xffff));
    return ret;
    
}
int ata_dma_write_master(uint16_t *buf,int lba){
    
}