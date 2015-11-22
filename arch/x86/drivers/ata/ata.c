#include <stdint.h>
static inline uint16_t inw(uint32_t s){
        uint16_t ret;
        asm volatile("inw %%dx, %%ax": "=a"(ret):  "d"(s));
        return ret;
}
ide_indent(){
	int io = 0x01F0;
	int drive=0x00;
	outb(0x1F6,0xA0);
	outb(0x1F2,0);
	outb(0x1F3,0);
	outb(0x1F4,0);
	outb(0x1F5,0);
	outb(0x1F7,0xEC);
}
int ide_wait_for_read(uint16_t io){
	int i = 0;
	while(i < 4){
		inb(io + 0x0C);
		i++;
	}
	retry:;
		uint8_t status = inportb(io + 0x07);
		//kprintf("!");
		if(status & 0x80) goto retry;
	retry2: status = inb(io + 0x07);
		//kprintf("+");
		if(status & 0x01){
			kprintf("I/O Error\n");
			//sleep(10000);
			return -1;
			//panic();
		}
		if(!(status & 0x08)) goto retry2;
		return 1;
}
int _ide_wait_for_read(int io,int drive){
        int i = 0;
        while(i < 4){
                inb(io + 0x0C);
                i++;
        }
        retry:;
                uint8_t status = inportb(io + 0x07);
                kprintf("Drive is busy\n");
		//return -1;
                if(status & 0x80) goto retry2;
        retry2: status = inportb(io + 0x07);
                if(status & 0x01){
                        //kprintf("I/O Error\n");
                        //sleep(10000);
                        return -1;
                        //panic();
                }
                if(!(status & 0x08)) goto retry2;
	        return 1;
}


unsigned int ddrive(){
	/*int io = 0x01F0;
	int i = 0;
	while(i < 4){
		inb(0x1FC);
		i++;
	}
	retry:;
		//kprintf("1\n");
		uint8_t status = inb(0x1F7);
		if(status & 0x80) goto retry;
	next1: status = inb(0x1F7);
		if(status & 0x01){
			//kprintf("I/O Error on disk 0!\n");
			goto retry2;
		}
		//kprintf("2\n");
		if(!(status & 0x08)) goto skip;
		//kprintf("Detected PRIMARY Drive\n");
		return 0x00;
	skip:
		i = 0;
		while(i < 4){
			inb(0x17C);
			i++;
		}
	retry2:;
		status = inb(0x177);
		if(status & 0x80)
			goto retry2;
		else
			goto next2;
	next2: status = inb(0x177);
		if(status & 0x01){
			//kprintf("I/O Error on Secondary ATA Drive!\n Panicing\n");
		}
		//kprintf("detected SECONDARY Drive;
		//kprintf("Sfa\n");
		if(!(status & 0x08)) goto retry;
		//kprintf("Detected secondary Drive\n");
		return 0x01;
		//if(_ide_wait_for_read(0x01F0,0x00) == 1) 
		//	return 0x00;
		//else
		//	return 0x01;*/
	int stat = inb(0x1F7);
	int stat1 = inb(0x177);
	if(!(stat & 0x01)){
		kprintf("Using PRIMARY Device\n");
		return 0x00;
	}
	else{
		kprintf("Using Secondary Device\n");
		return 0x01;
	}
}
int ata_read_master(uint8_t *buf,uint32_t _lba,uint16_t drive){
	uint16_t io;
	uint32_t lba = _lba;
	if(drive == 0x00)
		io = 0x1F0;
	else if(drive == 0x01)
		io = 0x170;
	else if(drive == 0x02)
		io = 0x4138;
	uint8_t cmd = 0xE0;
	uint8_t slavebit = 0x00;
	//kprintf("Sending LBA and CMD\n");
	outb(io + 0x06,(cmd | (uint8_t)((lba >> 24 & 0x0F))));
	outb(io + 1,0x00);
	outb(io + 0x02,1);
	outb(io + 0x03,(uint8_t)lba);
	outb(io + 0x04,(uint8_t)((lba) >> 8));
	outb(io + 0x05,(uint8_t)((lba) >> 16));
	outb(io + 0x07,0x20);
	//ide_wait_for_read();
	//ide_wait_for_read(io);
	if(ide_wait_for_read(io) < 0)
		return -1;
		//_panic();
		//return -1;
	//kprintf("@");
	int i = 0;
	while(i < 256){
		uint16_t data = inw(io);
		//kstrcat(buf,&(data));
		//buf[i] = 0x00;
		//char cdata = (char)data;
		//kstrcat(buf,&cdata);
		//buf[i] = (char)data;
		//buf[i * 2] = data
		*(uint16_t *)(buf + i * 2) = data;
		//kprintf("%c",data);
		///kprintf("%c",buf[i]);
		//kprintf(".");
		i++;
	}
	return 1;
}
int ata_read_cnt(uint8_t *buf,uint32_t lba,int cnt, uint16_t drive){
	int io;
	if(drive == 0x00)
		io = 0x01F0;
	else if(drive = 0x01)
		io = 0x170;
	uint8_t cmd = 0xE0;
	uint8_t slavebit = 0x00;
	outb(io + 0x06,(cmd | (uint8_t)((lba >> 24 & 0x0F))));
	outb(io + 1,0x00);
	outb(0x1F2,1);
	outb(0x1F3,(uint8_t)lba);
	outb(0x1F4,(uint8_t)((lba) >> 8));
	outb(0x1F5,(uint8_t)((lba) >> 16));
	outb(0x1F7,0x20);
	//ide_wait_for_read(io,drive);
	if(ide_wait_for_read(io) != 1)
		panic();
	int i = 0;
	while(i < 256){
		uint16_t data = inw(io);
		*(uint16_t *)(buf + i * 2) = data;
		i++;
	}
}
