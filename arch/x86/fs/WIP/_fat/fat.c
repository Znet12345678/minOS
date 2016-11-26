#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fat.h"
struct fat_bpb * parse_bpb(){
	struct fat_bpb *ret = malloc(sizeof(struct fat_bpb *) * sizeof(*ret));
	char *buf = malloc(1024);
	ata_read_master(buf,0,0);
	ret->bytes_per_sector = buf[11] << 8 | buf[12];
	ret->sectors_per_cluster = buf[13];
	ret->resv_sectors = buf[14] << 8 | buf[15];
	ret->num_of_fat = buf[16];
	ret->num_of_dir_ent = buf[17] << 8 | buf[18];
	ret->total_sectors = buf[19] << 8 | buf[20];
	ret->mdt = buf[21];
	ret->sectorsperfat = buf[22] << 8 | buf[23];
	ret->sectorspertrack = buf[24] << 8 | buf[25];
	ret->numberofheads = buf[26] << 8 | buf[27];
	ret->numberofhiddensectors = buf[28] << 24 | buf[29] << 16 | buf[30] << 8 |buf[31];
	ret->large_sectors = buf[32] << 24 | buf[33] << 16 | buf[34] << 8 | buf[35];
	return ret;
}
struct fat16_ebr *parse_fat16_ebr(){
	char *buf = malloc(513);
	ata_read_master(buf,0,0);
	struct fat16_ebr *ret = malloc(sizeof(struct fat16_ebr *) * sizeof(*ret));
	ret->drive_number = buf[36];
	ret->flags_nt = buf[37];
	ret->sig = buf[38];
	if(ret->sig != 0x28 && ret->sig != 0x29){
		kprintf("Invalid ebr!\n");
		panic();
	}
	ret->serial = buf[39] << 24 | buf[40] << 16 | buf[41] << 8 | buf[42];
	for(int i = 0; i < 11;i++){
		ret->label[i] = buf[i + 43];
	}
	kprintf("Opening volume:%s\n",ret->label);
	return ret;
}
struct fat32_ebr *parse_fat32_ebr(){
	char *buf = malloc(513);
	ata_read_master(buf,0,0);
	struct fat32_ebr *ret = malloc(sizeof(struct fat32_ebr *) * sizeof(*ret));
	ret->sectorsperfat = buf[36] << 24 | buf[37] << 16 | buf[38] << 8 | buf[39];
	ret->flags = buf[40] << 8 | buf[41];
	ret->fat_version = buf[42] << 8 | buf[43];
	ret->cluster_number = buf[44] << 24 | buf[45] << 16 | buf[46] << 8 | buf[47];
	ret->fsinfo_sector = buf[48] << 8 | buf[49];
	ret->backup_sector = buf[50] << 8 | buf[51];
	ret->drive_number = buf[64];
	ret->_flags = buf[65];
	ret->sig = buf[66];
	if(ret->sig != 0x28 && ret->sig != 0x29){
		kprintf("Invalid ebr!\n");
		panic();
	}
	ret->serial = buf[67] << 24 | buf[68] << 16 | buf[69] << 8 | buf[70];
	for(int i = 0; i < 11;i++){
		ret->label_str[i] = buf[i + 71];
	}
	kprintf("Opening volume:%s\n",ret->label_str);
	return ret;
}
struct info *fat_parse_info(){
	struct fat_bpb *boot_sector = parse_bpb();
	struct info *ret = malloc(sizeof(struct info *) * sizeof(*ret));
	ret->total_sectors = boot_sector->total_sectors;
	ret->fat_size = boot_sector->sectorsperfat;
	ret->root_dir_sectors = ((boot_sector->num_of_dir_ent * 32) + (boot_sector->bytes_per_sector - 1))/boot_sector->bytes_per_sector;
	ret->first_data_sector = boot_sector->resv_sectors + (boot_sector->num_of_fat * ret->fat_size) + ret->root_dir_sectors;
	ret->first_fat_sector = boot_sector->resv_sectors;
	ret->data_sectors = boot_sector->total_sectors - (boot_sector->resv_sectors + (boot_sector->num_of_fat * ret->fat_size) + ret->root_dir_sectors);
	ret->total_clusters = ret->data_sectors / boot_sector->sectors_per_cluster;
	return ret;
}
int fat_type(){
	struct info *inf = fat_parse_info();
	if(inf->total_clusters < 4085)
		return FAT12;
	else if(inf->total_clusters < 65525)
		return FAT16;
	else if(inf->total_clusters < 268435445)
		return FAT32;
	else
		return EXFAT;
}
int read_root(int type){
	struct info *inf = fat_parse_info();
	struct fat_dirent *dent = malloc(sizeof(struct fat_dirent *) * sizeof(*dent));
	struct fat_bpb *bpb = parse_bpb();
	int clusternum = 0;
	if(type < 0x02){
		while(1){
			kprintf("Reading Cluster number:%d\n",clusternum);
			int first_root_dir_sector = inf->first_data_sector - inf->root_dir_sectors;
			int first_sector_of_cluster = ((clusternum - 2) * bpb->sectors_per_cluster) + inf->first_data_sector;
			char *buf = malloc(1024);
			char *name = malloc(1024);
			ata_read_master(buf,first_sector_of_cluster,0);
			for(int i = 0; i < 16;i++){
				if(buf[i * 32] == 0){
					kprintf("Done!\n");
					return 1;
				}
				else if(buf[i * 32] == 0xE5)
					break;
				else{
					if(buf[i * 32 + 11] == 0x0F){
						for(int j = 0; j < 11;j++)
							dent->fname[j] = buf[i * 32 + j];
						dent->attr = buf[i * 32 + 11];
						dent->create_time = buf[i * 32 + 13];
						dent->time = buf[i * 32 + 14] << 8 | buf[i * 12 + 15];
						dent->date = buf[i * 32 + 16] << 8 | buf[i * 32 + 17];
						dent->lad = buf[i * 32 + 18] << 8 | buf[i * 32 + 19];
						dent->cluster_number_high = buf[i * 32 + 20] << 8 | buf[i * 32 + 21];
						dent->last_modify_time = buf[i * 32 + 22] << 8 | buf[i * 32 + 23];
						dent->last_modify_date = buf[i * 32 + 24] << 8 | buf[i * 32 + 25];
						dent->first_cluster_low = buf[i * 32 + 26] << 8 | buf[i * 32 + 27];
						dent->size_in_bytes = buf[i * 32 + 28] << 24 | buf[i * 32 + 29] << 16 | buf[i * 32 + 30] << 8 | buf[i * 32 + 31];
						kprintf("Parsed Entry:%s\n",dent->fname);
					}
				
				}

			}
			unsigned char FAT_table[512];
			unsigned int fat_offset = clusternum * 2;
			unsigned int fat_sector = inf->first_fat_sector + (fat_offset / 512);
			unsigned int ent_offset = fat_offset % 512;
			ata_read_master(FAT_table,fat_sector,0);
			unsigned short table_value = *(unsigned short*)&FAT_table[ent_offset];
			if(table_value >= 0xFFF8)
				return 1;
			else if(table_value == 0xFFF7)
				kprintf("Bad Cluster!\n");
			else
				clusternum = table_value;
		}
	}
}

