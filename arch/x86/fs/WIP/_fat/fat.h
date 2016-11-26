#ifndef __Z_FAT_H
#define __Z_FAT_H
#include <stdint.h>
#define FAT12 0x00
#define FAT16 0x01
#define FAT32 0x02
#define EXFAT 0x03
#define ERROR -1
struct info{
	int total_sectors;
	int fat_size;
	int root_dir_sectors;
	int first_data_sector;
	int first_fat_sector;
	int data_sectors;
	int total_clusters;
};
struct fat_bpb{
	uint32_t bytes_per_sector;
	uint32_t sectors_per_cluster;
	uint32_t resv_sectors;
	uint32_t num_of_fat;
	uint32_t num_of_dir_ent;
	uint32_t total_sectors;
	uint32_t mdt;
	uint32_t sectorsperfat;
	uint32_t sectorspertrack;
	uint32_t numberofheads;
	uint32_t numberofhiddensectors;
	uint32_t large_sectors;
};
struct fat16_ebr{
	short drive_number;
	short flags_nt;
	short sig;
	uint32_t serial;
	char label[11];
	uint16_t identifier_string[8];
};
struct fat32_ebr{
	uint32_t sectorsperfat;
	int flags;
	int fat_version;
	uint32_t cluster_number;
	int fsinfo_sector;
	int backup_sector;
	int resv[12];
	short drive_number;
	short _flags;
	short sig;
	uint32_t serial;
	char label_str[11];
	uint32_t system_ident[8];
};
#define READ_ONLY 1
#define HIDDEN 2
#define SYSTEM 4
#define VOLUME_ID 8
#define DIRECTORY 16
#define ARCHIVE 32
struct fat_dirent{
	char fname[11];
	int attr;
	int create_time;
	int time;
	int date;
	int lad;
	int cluster_number_high;
	int last_modify_time;
	int last_modify_date;
	int first_cluster_low;
	int size_in_bytes;
};
struct info *fat_parse_info();
struct fat_bpb *parse_bpb();
struct fat16_ebr *parse_fat16_ebr();
struct fat32_ebr *parse_fat32_ebr();
int fat_type();
int read_root(int type);
#endif
