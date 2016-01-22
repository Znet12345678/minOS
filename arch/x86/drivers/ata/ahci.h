#ifndef __MINOS_AHCI_H
#define __MINOS_AHCI_H
#include <stdint.h>
#include <stdio.h>
typedef enum{
	FIS_TYPE_REG_H2D = 0x27,
	FIS_TYPE_REG_D2H = 0x34,
	FIS_TYPE_REG_DMA_ACT = 0x39,
	FIS_TYPE_DMA_SETUP = 0x41,
	FIS_TYPE_DATA = 0x46,
	FIS_TYPE_BIST = 0x58,
	FIS_TYPE_PIO_SETUP = 0x5F,	
	FIS_TYPE_DEV_BITs = 0xA1,
}FIS_TYPE;
int get_io();
#endif
