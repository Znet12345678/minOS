#ifndef __Z_ATA_H
#define __Z_ATA_H
#include <stdint.h>
int ata_read_master(uint8_t *buf,uint32_t _lba,uint16_t drive);
#endif
