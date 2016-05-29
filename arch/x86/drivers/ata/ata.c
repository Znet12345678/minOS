/*
*minOS ata reader
*limited hardware support
*(c) 2015 Zachary James Schlotman
*/
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <stdint.h>

/*static inline void outw(uint16_t port,uint8_t val){
     __asm__ volatile ("outw %w0, %w1" : : "a"(val), "Nd"(port));
}
static inline void outsw(uint16_t port,void *val,unsigned long n){
	unsigned long cnt = 1;
	__asm__ volatile ("rep outsw" :  "+S"(val),"+c"(n) : "d"(port));
}
static inline uint16_t inw(uint32_t s){
        uint16_t ret;
        __asm__ volatile("inw %%dx, %%ax": "=a"(ret):  "d"(s));
        return ret;
}*/
int ide_indent(){
	int io = 0x01F0;
	int drive=0x00;
	outb(0x1F6,0xA0);
	outb(0x1F2,0);
	outb(0x1F3,0);
	outb(0x1F4,0);
	outb(0x1F5,0);
	outb(0x1F7,0xEC);
}
int ide_wait_for_write(){
    for(int i = 0; i < 4;i++){
        inb(0x1FC);
    }
    uint8_t stat = inb(0x1F7);
    while(stat & 0x80)
        ;
    stat = inb(0x1F7);
        if(!(stat & 0x08))
            return -1;

    return 0;
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
int ide_wait_for_read_silent(){
    int i = 0;
    while(i < 4){
        inb(0x1FC);
        i++;
    }
retry:;
    uint8_t status = inb(0x1F7);
    if(status & 0x80) goto retry;
retry2:status = inb(0x1F7);
    if(status & 0x01)
        return -1;
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
		panic();
		//return -1;
		//panic();
		//_panic();
		//return -1;
	//kprintf("@");
	int i = 0;
	while(i < 512){
		uint16_t data = inw(io);
		//kstrcat(buf,&(data));
		//buf[i] = 0x00;
		//char cdata = (char)data;
		//kstrcat(buf,&cdata);
		//buf[i] = (char)data;
		//buf[i * 2] = data
		//buf[i] = data;
		*(uint16_t *)(buf + i * 2) = data;
		//kprintf("%c",data);
		///kprintf("%c",buf[i]);
		//kprintf(".");
		i++;
	}
	return 1;
}
int ata_read_master_no(uint8_t *buf,uint16_t lba,unsigned int offset,unsigned int n){
	outb(0x1F6,(0xE0 | (uint8_t)((lba >> 24 & 0x0F))));
	outb(0x1F1,0);
	if(n < 512)
		outb(0x1F2,1);
	else
		outb(0x1F2,n/512);
	outb(0x1F3,(uint8_t) lba);
	outb(0x1F4,(uint8_t) (lba >> 8));
	outb(0x1F5,(uint8_t) (lba >> 16));
	outb(0x1F7,0x20);
	if(ide_wait_for_read(0x1F0) < 0)
		panic();
	int i = 0;
	while(i < offset){
		inb(0x1F0);
		i++;
	}
	while(i < n){
		uint16_t val = inb(0x1F0);
		*(uint16_t*)(buf + i*2) = val;
		i++;
	}
	return 0;
}
int ata_read_master_n(uint8_t *buf,uint16_t lba,unsigned int n){
        outb(0x1F6,(0xE0 | (uint8_t)((lba >> 24 & 0x0F))));
        outb(0x1F1,0);
        if(n < 512)
                outb(0x1F2,1);
        else
                outb(0x1F2,n/512);
        outb(0x1F3,(uint8_t) lba);
        outb(0x1F4,(uint8_t) (lba >> 8));
        outb(0x1F5,(uint8_t) (lba >> 16));
        outb(0x1F7,0x20);
        if(ide_wait_for_read(0x1F0) < 0)
                panic();
        int i = 0;
	while(i < n){
		uint16_t val = inb(0x1F0);
		*(uint16_t *)(buf + i * 2) = val;
		i++;
	}
	return 0;
}
int ata_write_master_no(uint8_t *buf,uint16_t lba,unsigned int offset,unsigned int n){
	int i = 0;
	outb(0x1F6,(0xe0 | (uint8_t)(lba >> 24 & 0x0f)));
	if(n < 512)
		outb(0x1F2,1);
	else
		outb(0x1F2,n/512);
	outb(0x1F3,(uint8_t)lba);
	outb(0x1F4,(uint8_t)(lba >> 8));
	outb(0x1F5,(uint8_t)(lba >> 16));
	outb(0x1F7,0x30);
	if(ide_wait_for_write() < 0){
		kprintf("I/O Error\n");
		panic();
	}
	char *__buf = malloc(1024);
	ata_read_master(__buf,lba,0);
	outsw(0x1F0,__buf,offset);
	outsw(0x1F0,buf,n);
	char _buf[513] = {[0 ... 512]0};
	outsw(0x1F0,_buf,512 - n);
	return 0;
}
int ata_write_master_n(uint8_t *buf,uint16_t lba,unsigned int n){
    int i = 0;
    uint16_t io = 0x1F0;
    uint8_t cmd = 0x30;
    uint8_t slavebit = 0;
    outb(0x1F6,(0xE0 | (uint8_t)((lba >> 24 & 0x0F))));
    outb(0x1F1,0);
    outb(0x1F2,1);
    outb(0x1F3,(uint8_t)lba);
    outb(0x1F4,(uint8_t)(lba >> 8));
    outb(0x1F5,(uint8_t)(lba >> 16));
    outb(0x1F7,0x30);
    if(ide_wait_for_write() < 0){
	kprintf("I/O Error!\n");
	panic();
    }
    int j = 0;
    outsw(0x1F0,buf,n);
    char _buf[513] = {[0 ... 512]0};
    outsw(0x1F0,_buf,512 - n);
    return 0;

}
int ata_write_master(uint8_t *buf,uint16_t _lba){
    uint16_t io;
    uint32_t lba = _lba;
    io = 0x1F0;
    uint8_t cmd = 0x30;
    uint8_t slavebit = 0x00;
    outb(io + 0x06,(cmd | (uint8_t)((lba >> 24 & 0x0F))));
    outb(io + 0x02,1);
    outb(io + 0x03,(uint8_t)lba);
    outb(io + 0x04,(uint8_t)((lba) >> 8));
    outb(io + 0x05,(uint8_t)((lba) >> 16));
    outb(io + 0x07,0x30);
    if(ide_wait_for_write() < 0){
	kprintf("I/O Error!\n");
	panic();
    }
    int i = 0;
    outsw(0x1F0,buf,512);
}
int ata_write_master_no_no_ow(uint8_t *buf,uint16_t _lba,unsigned int offset,unsigned int n){
	    uint16_t io;
    uint32_t lba = _lba;
    io = 0x1F0;
    uint8_t cmd = 0x30;
    uint8_t slavebit = 0x00;
    outb(io + 0x06,(cmd | (uint8_t)((lba >> 24 & 0x0F))));
    outb(io + 0x02,1);
    outb(io + 0x03,(uint8_t)lba);
    outb(io + 0x04,(uint8_t)((lba) >> 8));
    outb(io + 0x05,(uint8_t)((lba) >> 16));
    outb(io + 0x07,0x30);
    if(ide_wait_for_write() < 0){
	kprintf("I/O Error\n");
	panic();
    }
    int i = 0;
    char *_buf = malloc(1024);
    ata_read_master(_buf,_lba,0);
    outsw(0x1F0,_buf,offset);
    outsw(0x1F0,buf,n);
    return 0;
}
int ata_check_lba(uint32_t lba){
    uint16_t io;
    io = 0x1F0;
    uint8_t cmd = 0xE0;
    uint8_t slavebit = 0x00;
    outb(io + 0x06,(cmd | (uint8_t)((lba >> 24 & 0x0F))));
    outb(io + 1,0x00);
    outb(io + 0x02,1);
    outb(io + 0x03,(uint8_t)lba);
    outb(io + 0x04,(uint8_t)((lba) >> 8));
    outb(io + 0x05,(uint8_t)((lba) >> 16));
    outb(io + 0x07,0x20);
    uint16_t status;
    status = inb(0x1F7);
    if(status & 0x01)
        return -1;
    int i = 0;
    while(i < 256){
        uint16_t val = inw(0x1F0);
        i++;
    }
    return 0;
}
int zero_drive(){
    int i = 0;

    while(1){
        outb(0x1F0,0);
        outb(0x1F1,0);
        outb(0x1F2,0);
        outb(0x1F6,0);
        outb(0x1F7,0);
        t_displaylq();
        uint16_t io = 0x1F0;
        uint8_t cmd = 0x30;
        uint8_t slavebit = 0;
        outb(0x1F0 + 0x06,(0xE0 | (uint8_t)(((i >> 24) & 0x0F))));
        outb(0x1F1,0);
        outb(0x1F2,1);

        outb(0x1F3,(uint8_t)i);
        outb(0x1F4,(uint8_t)(i >> 8));
        outb(0x1F5,(uint8_t)(i >> 16));
        outb(0x1F7,0x30);
        int j = 0;
        uint16_t val = 0;
        while(j < 512){
            outw(0x1F0,0);
           // outw(0x1F7,0xE7);
            j++;
        }
        i++;
    }
    return 0;
}
int zero_part(int partnum){
    char *buf = malloc(513);
    int start;
    int end;
    ata_read_master(buf,0,0x00);
    if(partnum == 0)
        return zero_drive();
    if(partnum == 1){
        start = buf[454] << 24 | buf[455] << 16 | buf[456] << 8 | buf[457];
        end = start + (buf[458] << 24 | buf[459] << 16 | buf[460] << 8 | buf[461]);
    }
    else if(partnum == 2){
        start = buf[470] << 24 | buf[471] << 16 | buf[472] << 8 | buf[473];
        end = start + (buf[474] << 24 | buf[475] << 16 | buf[476] << 8 | buf[477]);
    }
    else if(partnum == 3){
        start = buf[486] << 24 | buf[487] << 16 | buf[488] << 8 | buf[489];
        end = start + (buf[490] << 24 | buf[491] << 16 | buf[492] << 8 | buf[493]);
    }
    else if(partnum == 4){
        start = buf[502] << 24  | buf[503] << 16 | buf[504] << 8 | buf[505];
        end = start + (buf[506] << 24 | buf[507] << 16 | buf[508] << 8 | buf[509]);
    }

    int io = 0x1F0;
    for(int i = 0; i < (end - start);i++){
        uint8_t cmd = 0x30;
        uint8_t slavebit = 0x00;
        outb(0x1F6,0x30);
        outb(io + 0x06,(cmd | (uint8_t)((i >> 24 & 0x0F))));
        outb(io + 1,0x00);
        outb(io + 0x02,1);
        outb(io + 0x03,(uint8_t)i);
        outb(io + 0x04,(uint8_t)((i) >> 8));
        outb(io + 0x05,(uint8_t)((i) >> 16));
        if(ide_wait_for_read(io) < 0)
            return -1;
        int i = 0;
        while(i < 512){
            outb(io,0);
        }
    }
}
struct partition{
    int boot;
    int starting_head;
    int starting_sector;
    int starting_cylinder;
    int id;
    int ending_head;
    int ending_sector;
    int ending_cylinder;
    uint32_t relative_sector;
    uint32_t tsp;
};
int ata_read_part(uint8_t *rbuf,uint16_t lba,int partnum){
    char *buf = malloc(513);
    int start;
    int end;
    ata_read_master(buf,0,0x00);
    if(partnum == 0)
        return ata_read_master(rbuf,lba,0);
    if(partnum == 1){
        start = buf[454] << 24 | buf[455] << 16 | buf[456] << 8 | buf[457];
        end = start + (buf[458] << 24 | buf[459] << 16 | buf[460] << 8 | buf[461]);
    }
    else if(partnum == 2){
        start = buf[470] << 24 | buf[471] << 16 | buf[472] << 8 | buf[473];
        end = start + (buf[474] << 24 | buf[475] << 16 | buf[476] << 8 | buf[477]);
    }
    else if(partnum == 3){
        start = buf[486] << 24 | buf[487] << 16 | buf[488] << 8 | buf[489];
        end = start + (buf[490] << 24 | buf[491] << 16 | buf[492] << 8 | buf[493]);
    }
    else if(partnum == 4){
        start = buf[502] << 24  | buf[503] << 16 | buf[504] << 8 | buf[505];
        end = start + (buf[506] << 24 | buf[507] << 16 | buf[508] << 8 | buf[509]);
    }
    if((start + lba) > end)
        return -1;
    return ata_read_master(rbuf,lba + start,0);
}
int ata_write_part(uint8_t *rbuf,uint16_t lba,int partnum){
    char *buf = malloc(513);
    int start;
    int end;
    ata_read_master(buf,0,0x00);
    if(partnum == 0)
        return ata_read_master(rbuf,lba,0);
    if(partnum == 1){
        start = buf[454] << 24 | buf[455] << 16 | buf[456] << 8 | buf[457];
        end = start + (buf[458] << 24 | buf[459] << 16 | buf[460] << 8 | buf[461]);
    }
    else if(partnum == 2){
        start = buf[470] << 24 | buf[471] << 16 | buf[472] << 8 | buf[473];
        end = start + (buf[474] << 24 | buf[475] << 16 | buf[476] << 8 | buf[477]);
    }
    else if(partnum == 3){
        start = buf[486] << 24 | buf[487] << 16 | buf[488] << 8 | buf[489];
        end = start + (buf[490] << 24 | buf[491] << 16 | buf[492] << 8 | buf[493]);
    }
    else if(partnum == 4){
        start = buf[502] << 24  | buf[503] << 16 | buf[504] << 8 | buf[505];
        end = start + (buf[506] << 24 | buf[507] << 16 | buf[508] << 8 | buf[509]);
    }
    if((start + lba) > end)
        return -1;
    return ata_write_master(rbuf,lba + start);
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
	if(ide_wait_for_read(io) != 1)
		panic();
	int i = 0;
	while(i < 256){
		uint16_t data = inw(io);
		*(uint16_t *)(buf + i * 2) = data;
		i++;
	}
}
