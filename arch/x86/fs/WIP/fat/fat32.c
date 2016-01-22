#include "fat32.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
int fat32_mount(struct bpb boots,struct Fat32_ExtendedBootRecord ExtBootRecord,unsigned char *FAT){
    t_init();
    debug("FAT32_MOUNT","Setting up values");
    //while(1) { };
 //   kprintf("ROOT_CLUSTER_32 [OK]");
    uint32_t root_cluster_32 = ExtBootRecord.cluster_number;
    kprintf("ROOT_CLUSTER_32 [OK]\n");
    for(int i = 0; i < 1000000; i++) {inb(0x1FC); }
    //while(1) { };
	uint32_t total_sec = boots.largeammountofsectoronmedia;
    kprintf("TOTAL_SEC [OK]\n");
    for(int i = 0; i < 1000000; i++) {inb(0x1FC); }
    //while(1) { };
	uint32_t fat_size  = ExtBootRecord.SectorsPerFat;
    kprintf("FAT_SIZE [OK]\n");
    for(int i = 0; i < 1000000; i++) {inb(0x1FC); }
   // while(1) { };
    uint32_t root_dir_sec = 0;// = ((boots.numofdirent * 32) + (boots.bytespersector - 1)) /boots.bytespersector;
    kprintf("ROOT_DIR_SEC [OK]\n");
    for(int i = 0; i < 1000000; i++) {inb(0x1FC); }
    //while(1) { };
	uint32_t first_dat_sec = boots.reserved + (boots.numoffat * fat_size) + root_dir_sec;
    kprintf("FIRST_DAT_SEC [OK]\n");
    for(int i = 0; i < 1000000; i++) {inb(0x1FC); }
    uint32_t first_fat_sector = boots.reserved;
    kprintf("FIRST_FAT_SECTOR [OK]\n");
    //while(1) { };
	uint32_t data_sectors = boots.largeammountofsectoronmedia - (boots.reserved + (boots.numoffat * fat_size) + root_dir_sec);
    kprintf("DATA_SECTORS [OK]\n");
    for(int i = 0; i < 1000000; i++) {inb(0x1FC); }
    uint32_t total_clusters;// = data_sectors/boots.sectorspercluster;
    kprintf("TOTAL_CLUSTERS [OK]\n");
    //while(1) { };
    char *buf = malloc(1024);
	uint32_t root_sector = ((root_cluster_32 - 2) * boots.sectorspercluster) + first_dat_sec + boots.hiddensectors;
	debug("FAT32_MOUNT","Reading Root Sector");
    if(root_sector < 0){
        debug("FAT32_MOUNT","Root sector is less than 0");
        while(1) { };
//        panic();
    }
   // while(1) { }
	ata_read_master(buf,root_sector,0);
	if(buf[0] == 0){
		debug("FAT_MOUNT","Empty root directory");
		return 0;
	}
	else if(buf[0] == 0xE5){
		debug("FAT_MOUNT","Unused entry");
	}
	else if(buf[11] == 0x0F){
		
	}
	else{
		struct Fat_DirEnt ent;
		ent.filename = malloc(1024);
		for(int i = 0; i < 11;i++){
			ent.filename[i] = buf[i];
		}
		int atr = buf[11];
		ent.atr = atr;
		int size = buf[28] << 16 | buf[29] << 8 | buf[30];
	}
	
}
