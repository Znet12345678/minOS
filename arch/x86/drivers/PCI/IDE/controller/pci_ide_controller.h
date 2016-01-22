#ifndef __PCI_IDE_CONTROLLER_H
#define __PCI_IDE_CONTROLLER_H
extern void ide_init(unsigned int B0,unsigned int B1,unsigned int B2, unsigned int B3,unsigned int b4);
/*Begin Status Macros*/
#define ATA_SR_BSY 0x80 /*Drive is busy*/
#define ATA_SR_RDY 0x40 /*Drive is read*/
#define ATA_SR_DF 0x20 /*Write fault*/
#define ATA_SR_DSC 0x10 /*Seek complete*/
#define ATA_SR_DRQ 0x8 /*Data request ready*/
#define ATA_SR_CORR 0x04 /*Corrected data*/
#define ATA_SR_IDX 0x02 /*Inlex*/
#define ATA_SR_ERROR 0x01 /*Error*/
/*End Status Macros*/
/*Begin ATA ERRORS*/
#define ATA_ER_BADSECTOR 0x80 /*Bad Sector*/
#define ATA_ER_BDATA 0x40 /*Bad data*/
#define ATA_ER_MC 0x20 /*No Media*/
#define ATA_ER_IDNF 0x10 /*No ID mark*/
#define ATA_ER_MCR 0x08 /*Again No media*/
#define ATA_ER_ABRT 0x04 /*Abort*/
#define ATA_ER_TKONF 0x02/*Trak 0 not found*/
#define ATA_ER_AMNF 0x01 /*No address mark*/
/*End ATA ERRORS*/
/*Begin Commands*/
#define ATA_CMD_READ_PIO 0x20
#define ATA_CMD_READ_PIO_EXIT 0x24
#define ATA_CMD_READ_DMA 0xC8
#define ATA_CMD_READ_DMA_EXIT 0x25
#define ATA_CMD_WRITE_PIO 0x30
#define ATA_CMD_WRITE_PIO_EXIT 0x34
#define ATA_CMD_WRITE_DMA 0xCA
#define ATA_CMD_WRITE_DMA_EXIT 0x35
#define ATA_CMD_CACHE_FLUSH 0xE7
#define ATA_CMD_CACHE_FLUSH_EXIT 0xEA
#define ATA_CMD_PACKET 0xA0
#define ATA_CMD_IDENT_PACK 0xA1
#define ATA_CMD_IDENT 0xEC
#define ATAPI_CMD_READ 0xA8
#define ATAPI_CMD_EJECT 0x1B
#define ATA_IDENT_DEVICE_T 0
#define ATA_IDENT_CYL 2
#define ATA_IDENT_HEADS 6
#define ATA_IDENT_SECTORS 12
#define ATA_IDENT_SERIAL 20
#define ATA_IDENT_MODEL
#define ATA_IDENT_CAP 98
#define ATA_IDENT_FIELDVALID 106
#define ATA_IDENT_MAX_LBA 120
#define ATA_IDENT_CMDSETS 164
#define ATA_IDENT_MAX_LBA_EXT 200
#define IDE_ATA 0x00
#define IDE_ATAPI 0x01
#define ATA_MASTER 0x00
#define ATA_SLAVE 0x01
#define ATA_REG_DATA       0x00
#define ATA_REG_ERROR      0x01
#define ATA_REG_FEATURES   0x01
#define ATA_REG_SECCOUNT0  0x02
#define ATA_REG_LBA0       0x03
#define ATA_REG_LBA1       0x04
#define ATA_REG_LBA2       0x05
#define ATA_REG_HDDEVSEL   0x06
#define ATA_REG_COMMAND    0x07
#define ATA_REG_STATUS     0x07
#define ATA_REG_SECCOUNT1  0x08
#define ATA_REG_LBA3       0x09
#define ATA_REG_LBA4       0x0A
#define ATA_REG_LBA5       0x0B
#define ATA_REG_CONTROL    0x0C
#define ATA_REG_ALTSTATUS  0x0C
#define ATA_REG_DEVADDRESS 0x0D
/*End Commands*/
/*Begin Channels*/
#define ATA_PRIMARY 0x00
#define ATA_SECONDARY 0x01
/*End Channels*/
/*Begin Directions*/
#define ATA_READ 0x00
#define ATA_WRITE 0x01
/*End Directions*/
/*Begin Structures,typedefs, and var decl*/
struct IDEChannelReg{
	unsigned short base;
	unsigned short ctrl;
	unsigned short bmide;
	unsigned char nIEN;
}channels[2];
typedef struct IDEChannelReg channel_t;
unsigned char ide_buffer[2048] = {0};
unsigned static char ide_irq_invoked = 0;
unsigned static char atapi_packet[12] = {0x10,0,0,0,0,0,0,0,0,0,0,0};
struct ide_dev{
	unsigned char Reserved;
	unsigned char Channel;
	unsigned char Drive;
	unsigned short Type;
	unsigned short Signature;
	unsigned short Capabilities;
	unsigned int commandsets;
	unsigned int Size;
	unsigned char Model[41];
}ide_devices[4];
typedef struct ide_dev idedev_t;
extern unsigned char ide_read(unsigned char channel,unsigned char reg);
/*End Structures,typedefs, and var decl*/
#endif
