//OBSOLETE
#include "pci_ide_controller.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
//#include <asm.h>
unsigned long _strlen(const char *str){
	unsigned long ret = 0;
	while(str[ret] != 0)
		ret++;
	return ret;
}
void wait_irq(){
	while(!ide_irq_invoked)
		;
	ide_irq_invoked = 0;
}
void ide_irq(){
	ide_irq_invoked = 1;
}

void ide_read_buffer(unsigned char channel, unsigned char reg, unsigned int buffer,unsigned int quads) {
   if (reg > 0x07 && reg < 0x0C)
      ide_write(channel, ATA_REG_CONTROL, 0x80 | channels[channel].nIEN);
   asm("pushw %es; movw %ds, %ax; movw %ax, %es");
   if (reg < 0x08)
      insl(channels[channel].base  + reg - 0x00, buffer, quads);
   else if (reg < 0x0C)
      insl(channels[channel].base  + reg - 0x06, buffer, quads);
   else if (reg < 0x0E)
      insl(channels[channel].ctrl  + reg - 0x0A, buffer, quads);
   else if (reg < 0x16)
      insl(channels[channel].bmide + reg - 0x0E, buffer, quads);
   asm("popw %es;");
   if (reg > 0x07 && reg < 0x0C)
      ide_write(channel, ATA_REG_CONTROL, channels[channel].nIEN);
}
unsigned char ide_read(unsigned char channel,unsigned char reg){
	unsigned char ret;
	if (reg > 0x07 && reg < 0x0C)
		ide_write(channel,ATA_REG_CONTROL,0x08 | channels[channel].nIEN); 
	if (reg < 0x08)
		ret = inportb(channels[channel].base +reg - 0x00);
	else if(reg < 0x0C)
		ret = inportb(channels[channel].base + reg - 0x06);
	else if (reg < 0x0E)
		ret = inportb(channels[channel].base + reg - 0x0A);
	else if (reg < 0x16)
		ret = inportb(channels[channel].bmide + reg - 0x0E);
	if(reg > 0x07 && reg < 0x0C)
		ide_write(channel,ATA_REG_CONTROL,channels[channel].nIEN);
	return ret;
}
void ide_write(unsigned char channel,unsigned char reg,unsigned char data){
	if (reg > 0x07  && reg < 0x0C)
		ide_write(channel,ATA_REG_CONTROL, 0x80 | channels[channel].nIEN);
	else if(reg < 0x08)
		outb(channels[channel].base + reg - 0x00,data);
	else if(reg < 0x0C)
		outb(channels[channel].base + reg - 0x06,data);
	else if(reg < 0x0E)
		outb(channels[channel].ctrl + reg - 0x0A,data);
	else if(reg < 0x16)
		outb(channels[channel].bmide + reg - 0x0E,data);
	if(reg > 0x07 && reg < 0x0C)
		ide_write(channel,ATA_REG_CONTROL,channels[channel].nIEN);
}
//Borrowed from os dev really tired will write my own in future.
unsigned char ide_polling(unsigned char channel, unsigned int advanced_check) {
   for(int i = 0; i < 4; i++)
      ide_read(channel, ATA_REG_ALTSTATUS);
   while (ide_read(channel, ATA_REG_STATUS) & ATA_SR_BSY)
      ; 
   if (advanced_check) {
      unsigned char state = ide_read(channel, ATA_REG_STATUS);
      if (state & ATA_SR_ERROR)
      	panic();
      if (state & ATA_SR_DF)
         return 1;
      if ((state & ATA_SR_DRQ) == 0)
         return 3; 
 
   }
 
   return 0;
 
}
//End Borrowed
void print_error(){
	kprintf("I/O Error");
	panic();
}

void ide_init(unsigned int BAR0, unsigned int BAR1, unsigned int BAR2, unsigned int BAR3,unsigned int BAR4){
	int j,k,cnt = 0;
	int channel;
	char *ide_buf;
	int i = 0;
	channels[ATA_PRIMARY].base = (BAR0 & 0xFFFFFFFC) + 0x1F0 * (!BAR0);
	channels[ATA_PRIMARY].ctrl = (BAR1 & 0xFFFFFFFC) + 0x3F6 * (!BAR1);
	channels[ATA_SECONDARY].base = (BAR2 & 0xFFFFFFFC) + 0x170 *(!BAR2);
	channels[ATA_SECONDARY].ctrl = (BAR3 & 0xFFFFFFFC) + 0x376 * (!BAR3);
	channels[ATA_PRIMARY].bmide = (BAR4 & 0xFFFFFFFC) + 0;
	channels[ATA_SECONDARY].bmide = (BAR4 & 0xFFFFFFFC) + 8;
	ide_write(ATA_PRIMARY,ATA_REG_CONTROL,2);
	ide_write(ATA_SECONDARY,ATA_REG_CONTROL,2); 
	ide_read(channel, ATA_REG_STATUS);
	for (i = 0; i < 2; i++)
      for (j = 0; j < 2; j++) {
 
         unsigned char err = 0, type = IDE_ATA, status;
         ide_devices[cnt].Reserved = 0;
         ide_write(i, ATA_REG_HDDEVSEL, 0xA0 | (j << 4));
         sleep(1);
         ide_write(i, ATA_REG_COMMAND, ATA_CMD_IDENT);
         sleep(1);
         if (ide_read(i, ATA_REG_STATUS) == 0) continue;
 
         while(1) {
            status = ide_read(i, ATA_REG_STATUS);
            if ((status & ATA_SR_ERROR)) {err = 1; break;} 
            if (!(status & ATA_SR_BSY) && (status & ATA_SR_DRQ)) break; 
         }
  
         if (err != 0) {
            unsigned char cl = ide_read(i, ATA_REG_LBA1);
            unsigned char ch = ide_read(i, ATA_REG_LBA2);
 
            if (cl == 0x14 && ch ==0xEB)
               type = IDE_ATAPI;
            else if (cl == 0x69 && ch == 0x96)
               type = IDE_ATAPI;
            else
               continue; 
 
            ide_write(i, ATA_REG_COMMAND, ATA_CMD_IDENT_PACK);
            sleep(1);
         }
	
         ide_read_buffer(i, ATA_REG_DATA, (unsigned int) ide_buf, 128);

         ide_devices[cnt].Reserved     = 1;
         ide_devices[cnt].Type         = type;
         ide_devices[cnt].Channel      = i;
         ide_devices[cnt].Drive        = j;
         ide_devices[cnt].Signature    = *((unsigned short *)(ide_buf + ATA_IDENT_DEVICE_T));
         ide_devices[cnt].Capabilities = *((unsigned short *)(ide_buf + ATA_IDENT_CAP));
         ide_devices[cnt].commandsets  = *((unsigned int *)(ide_buf + ATA_IDENT_CMDSETS));
 
         if (ide_devices[cnt].commandsets & (1 << 26))
            ide_devices[cnt].Size   = *((unsigned int *)(ide_buf + ATA_IDENT_MAX_LBA_EXT));
         else
            ide_devices[cnt].Size   = *((unsigned int *)(ide_buf + ATA_IDENT_MAX_LBA));
 
         for(k = 0; k < 40; k += 2) {
            ide_devices[cnt].Model[k] = ide_buf[ATA_IDENT_MODEL + k + 1];
            ide_devices[cnt].Model[k + 1] = ide_buf[ATA_IDENT_MODEL + k];}
         ide_devices[cnt].Model[40] = 0;
 
         cnt++;
      }
 
   for (i = 0; i < 4; i++)
      if (ide_devices[i].Reserved == 1) {
         kprintf(" Found %s Drive %dGB - %s\n",(const char *[]){"ATA", "ATAPI"}[ide_devices[i].Type],ide_devices[i].Size / 1024 / 1024 / 2,ide_devices[i].Model);
      }
}
int ide_atapi_read(unsigned char drive,unsigned int lba,unsigned char numsects,unsigned short selector,unsigned int edi){
	unsigned int channel = ide_devices[drive].Channel;
	unsigned int slavebit = ide_devices[drive].Drive;
	unsigned int bus = channels[channel].base;
	unsigned int words = 1024;
	unsigned char err;
	int i;
	ide_write(channel,ATA_REG_CONTROL,channels[channel].nIEN = ide_irq_invoked = 0x0);
	atapi_packet[0] = ATAPI_CMD_READ;
	atapi_packet[1] = 0x0;
	atapi_packet[2] = (lba >> 24) & 0xFF;
	atapi_packet[3] = (lba >> 16) & 0xFF;
	atapi_packet[4] = (lba >> 8) & 0xFF;
	atapi_packet[5] = (lba >> 0) & 0xFF;
	atapi_packet[6] = 0x00;
        atapi_packet[7] = 0x00;
        atapi_packet[8] = 0x00;
        atapi_packet[9] = numsects;
        atapi_packet[10] = 0x00;
        atapi_packet[11] = 0x00;
	ide_write(channel,ATA_REG_HDDEVSEL,slavebit << 4);
	i = 0;
	while(i < 4)
		i++;
	ide_read(channel,ATA_REG_ALTSTATUS);
	ide_write(channel, ATA_REG_FEATURES, 0);
	ide_write(channel,ATA_REG_LBA1,(words * 2) & 0xFF);
	ide_write(channel,ATA_REG_LBA2,(words * 2) >> 8);
	ide_write(channel,ATA_REG_COMMAND,ATA_CMD_PACKET);
	if(err = ide_polling(channel,1)) return err;
	asm("rep   outsw" : : "c"(6), "d"(bus), "S"(atapi_packet));
	i = 0;
	while (i < numsects){
		//wait_irq();
		if(err = ide_polling(channel,1)) return err;
		asm("pushw %es");
      		asm("mov %%ax, %%es"::"a"(selector));
      		asm("rep insw"::"c"(words), "d"(bus), "D"(edi));
		asm("popw %es");
		edi +=(words *2);
		i++;
	}
	//wait_irq();
	while (ide_read(channel, ATA_REG_STATUS) & (ATA_SR_BSY | ATA_SR_DRQ))
	      ;
	return 0;
}
unsigned char ide_ata_access(unsigned char direction, unsigned char drive, unsigned int lba, unsigned char numsects, unsigned short selector, unsigned int edi) {
	

   unsigned char lba_mode /* 0: CHS, 1:LBA28, 2: LBA48 */, dma /* 0: No DMA, 1: DMA */, cmd;
   unsigned char lba_io[6];
   unsigned int  channel      = ide_devices[drive].Channel; // Read the Channel.
   unsigned int  slavebit      = ide_devices[drive].Drive; // Read the Drive [Master/Slave]
   unsigned int  bus = channels[channel].base; // Bus Base, like 0x1F0 which is also data port.
   unsigned int  words      = 256; // Almost every ATA drive has a sector-size of 512-byte.
   unsigned short cyl, i;
   unsigned char head, sect, err;
   ide_write(channel, ATA_REG_CONTROL, channels[channel].nIEN = (ide_irq_invoked = 0x0) + 0x02);
   // (I) Select one from LBA28, LBA48 or CHS;
   if (lba >= 0x10000000) { // Sure Drive should support LBA in this case, or you are
                            // giving a wrong LBA.
      // LBA48:
      lba_mode  = 2;
      lba_io[0] = (lba & 0x000000FF) >> 0;
      lba_io[1] = (lba & 0x0000FF00) >> 8;
      lba_io[2] = (lba & 0x00FF0000) >> 16;
      lba_io[3] = (lba & 0xFF000000) >> 24;
      lba_io[4] = 0; // LBA28 is integer, so 32-bits are enough to access 2TB.
      lba_io[5] = 0; // LBA28 is integer, so 32-bits are enough to access 2TB.
      head      = 0; // Lower 4-bits of HDDEVSEL are not used here.
   } else if (ide_devices[drive].Capabilities & 0x200)  { // Drive supports LBA?
      // LBA28:
      lba_mode  = 1;
      lba_io[0] = (lba & 0x00000FF) >> 0;
      lba_io[1] = (lba & 0x000FF00) >> 8;
      lba_io[2] = (lba & 0x0FF0000) >> 16;
      lba_io[3] = 0; // These Registers are not used here.
      lba_io[4] = 0; // These Registers are not used here.
      lba_io[5] = 0; // These Registers are not used here.
      head      = (lba & 0xF000000) >> 24;
   } else {
      // CHS:
      lba_mode  = 0;
      sect      = (lba % 63) + 1;
      cyl       = (lba + 1  - sect) / (16 * 63);
      lba_io[0] = sect;
      lba_io[1] = (cyl >> 0) & 0xFF;
      lba_io[2] = (cyl >> 8) & 0xFF;
      lba_io[3] = 0;
      lba_io[4] = 0;
      lba_io[5] = 0;
      head      = (lba + 1  - sect) % (16 * 63) / (63); // Head number is written to HDDEVSEL lower 4-bits.
   }

   dma = 0;
	 while (ide_read(channel, ATA_REG_STATUS) & ATA_SR_BSY)
  if (lba_mode == 0)
      ide_write(channel, ATA_REG_HDDEVSEL, 0xA0 | (slavebit << 4) | head); // Drive & CHS.
   else
      ide_write(channel, ATA_REG_HDDEVSEL, 0xE0 | (slavebit << 4) | head); // Drive & LBA
   if (lba_mode == 2) {
      ide_write(channel, ATA_REG_SECCOUNT0,   0);
      ide_write(channel, ATA_REG_LBA3,   lba_io[3]);
      ide_write(channel, ATA_REG_LBA4,   lba_io[4]);
      ide_write(channel, ATA_REG_LBA5,   lba_io[5]);
   }
   ide_write(channel, ATA_REG_SECCOUNT0,numsects);
   ide_write(channel, ATA_REG_LBA0,   lba_io[0]);
   ide_write(channel, ATA_REG_LBA1,   lba_io[1]);
   ide_write(channel, ATA_REG_LBA2,   lba_io[2]);
   if (lba_mode == 0 && dma == 0 && direction == 0) cmd = ATA_CMD_READ_PIO;
   if (lba_mode == 1 && dma == 0 && direction == 0) cmd = ATA_CMD_READ_PIO;   
   if (lba_mode == 2 && dma == 0 && direction == 0) cmd = ATA_CMD_READ_PIO_EXIT;   
   if (lba_mode == 0 && dma == 1 && direction == 0) cmd = ATA_CMD_READ_DMA;
   if (lba_mode == 1 && dma == 1 && direction == 0) cmd = ATA_CMD_READ_DMA;
   if (lba_mode == 2 && dma == 1 && direction == 0) cmd = ATA_CMD_READ_DMA_EXIT;
   if (lba_mode == 0 && dma == 0 && direction == 1) cmd = ATA_CMD_WRITE_PIO;
   if (lba_mode == 1 && dma == 0 && direction == 1) cmd = ATA_CMD_WRITE_PIO;
   if (lba_mode == 2 && dma == 0 && direction == 1) cmd = ATA_CMD_WRITE_PIO_EXIT;
   if (lba_mode == 0 && dma == 1 && direction == 1) cmd = ATA_CMD_WRITE_DMA;
   if (lba_mode == 1 && dma == 1 && direction == 1) cmd = ATA_CMD_WRITE_DMA;
   if (lba_mode == 2 && dma == 1 && direction == 1) cmd = ATA_CMD_WRITE_DMA_EXIT;
   ide_write(channel, ATA_REG_COMMAND, cmd);               // Send the Command.
   if (dma)
      if (direction == 0);
         // DMA Read.
      else;
         // DMA Write.
   else
      if (direction == 0)
         // PIO Read.
      for (i = 0; i < numsects; i++) {
         if (err = ide_polling(channel, 1))
            return err; // Polling, set error and exit if there is.
         asm("pushw %es");
         asm("mov %%ax, %%es" : : "a"(selector));
         asm("rep insw" : : "c"(words), "d"(bus), "D"(edi)); // Receive Data.
         asm("popw %es");
         edi += (words*2);
      } else {
      // PIO Write.
         for (i = 0; i < numsects; i++) {
            ide_polling(channel, 0); // Polling.
            asm("pushw %ds");
            asm("mov %%ax, %%ds"::"a"(selector));
            asm("rep outsw"::"c"(words), "d"(bus), "S"(edi)); // Send Data
            asm("popw %ds");
            edi += (words*2);
         }
         ide_write(channel, ATA_REG_COMMAND, (char []) {   ATA_CMD_CACHE_FLUSH,ATA_CMD_CACHE_FLUSH,ATA_CMD_CACHE_FLUSH_EXIT}[lba_mode]);
	ide_polling(channel, 0); // Polling.
      }
 
   return 0; 

}
void ide_read_sectors(unsigned int drive,unsigned int lba,unsigned int edi, unsigned short es, unsigned char numsects){
	int package[1];
	int i = 0;
	if (drive > 3 || ide_devices[drive].Reserved == 0){
		package[0] = 0x1;
		kprintf("Invaild drive specification\n");
	}
	   else if (((lba + numsects) > ide_devices[drive].Size) && (ide_devices[drive].Type == IDE_ATA)){
		package[0] = 0x2;
		kprintf("Bad position\n");
	}
	else{
     	      unsigned char err;
    	      if (ide_devices[drive].Type == IDE_ATA)
	         err = ide_ata_access(ATA_READ, drive, lba, numsects, es, edi);
	      else if (ide_devices[drive].Type == IDE_ATAPI)
	         for (i = 0; i < numsects; i++){
	            err = ide_atapi_read(drive, lba + i, 1, es, edi + (i*2048));
	  	    //package[0] = ide_print_error(drive, err);
  		 }
	}
}
int wait(unsigned short s){
	while(inb(s + 0x206) & 0x80);
	return 0;
}
static inline void _outb(uint16_t port,uint8_t val){
	asm volatile("outb %0, %1" : : "a"(val),"Nd"(port));
}
int common(int drive, int numblock,int count){
	wait(0x1F0);
	_outb(0x1F1,0x00);
	_outb(0x1F2,count);
	_outb(0x1F3,(unsigned char)numblock);
	_outb(0x1F4,(unsigned char)numblock >> 8);
	_outb(0x1F5,(unsigned char)numblock >> 16);
	_outb(0x1F6,0xE0 |(drive << 4)|(numblock >> 24) & 0x0F);
	return 0;	
}
static inline uint16_t inw(uint32_t s){
	uint16_t ret;
	asm volatile("inw %%dx, %%ax": "=a"(ret):  "d"(s));
	return ret;
}
static inline void outw(int port,uint8_t val){
	asm volatile("outw %%ax, %%dx" : : "d"(port),"a"(val));
}
static inline uint8_t _inb(uint16_t port){
	uint8_t ret;
	asm volatile( "inb %1,%0" : "=a"(ret) :"Nd"(port));
	return ret;
}
int io_read(int drive,int numblock,int count,char *buf){
	uint16_t tmpword;
	int idx;
	int c;
	common(drive,numblock,count);
	_outb(0x1F7,0x20);
	wait(0x1F0);
	while(!(_inb(0x1F7) & 0x08));
	while(idx < (256 * count)){
		tmpword = inw(0x1F0);
		buf[idx * 2] = (unsigned char) tmpword;
		buf[idx * 2 + 1] = (unsigned char)(tmpword >> 8);
		++idx;
	}
	return count;
}
int io_getcnt(int drive){
	int ret;
	while(inw(0x1F0))
		ret++;
	return ret;
}
int io_write(int drive,int numblock,int count,char * buf){
	int idx;
	uint16_t tmpword;
	common(drive,numblock,count);
	_outb(0x1F7,0x30);
	wait(0x1F0);
	while(!(_inb(0x1F7) & 0x08));
	while(idx < count){
		tmpword = (buf[idx * 2 + 1] >> 8) | buf[idx * 2];
		outw(0x1F0,tmpword);
		++idx;
	}
	return count;
}/*
int _ide_read(int pos,int *buf,int size,int drive){
	int count = size;
	if(buffer ==  NULL)
		return -1;
	int offset = (int)pos;
	int bl_b,bl_e,blocks;
	bl_b = (offset / 612);
	bl_e = ((offset +count)/512);
	blocks = bl_end - bl_begin + 1;
	char *block_buff = malloc(blocks * 512);
	io_read(drive,blocks,block_buff);
	memcpy((char*)buf,((int)block_buff + ((int)offset % 512),count));
	return count;
}
*/
