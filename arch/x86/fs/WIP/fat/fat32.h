#ifndef __FAT32_H
#define __FAT32_H
#include <stdint.h>
struct bpb{
	uint32_t jmp;
	uint32_t oem;
	uint32_t bytespersector;
	uint32_t sectorspercluster;
	uint32_t reserved;
	uint32_t numoffat;
	uint32_t numofdirent;
	uint32_t totsec;
	uint32_t mdt;
	uint32_t sectorspertrack;
	uint32_t heads;
	uint32_t hiddensectors;
	uint32_t largeammountofsectoronmedia;
};
struct Fat12_ExtendedBootRecord{
	int drive_num;
	int flags;
	int signature;
	char *volumeid;
	int sis;
	uint8_t *bootcode;
	int bootsig;	
};
struct Fat32_ExtendedBootRecord{
	int SectorsPerFat;
	int flags;
	int FAT_Version_Number;
	long cluster_number;
	int second_number;
	int backup;
	int *reserved;
	int DriveNum;
	int Signature;
	int VolumeID;
	char *VolumeLabelString;
	long *Sis;
	uint8_t *bootcode;
	int bootsig;
};
unsigned char *FAT_table;
unsigned int fat_offset;
unsigned int fat_sector;
unsigned int ent_offset;
unsigned short t_val;
enum FATRIBUTE{
	READ_ONLY = 0x01,
	HIDDEN = 0x02,
	SYSTEM = 0x04,
	VOLUME_ID = 0x08,
	DIRECTORY = 0x10,
	ARCHIVE = 0x20,
};
struct Fat_DirEnt{
	char *filename;
	int atr;
	int resv;
	int creationtime;
	int time;
	int date;
	int lad;
	int high;
	int lmt;
	int lmd;
	int low16;
	int size;
};
struct LFN{
	int order;
	int *first5;
	int Attr;
	int Longentrytype;
	int checksum;
	int *next6;
	int final2;

};
int fat32_mount(struct bpb boots,struct Fat32_ExtendedBootRecord ExtBootRecord,unsigned char *FAT);
void fat12_mount(struct bpb *boots,struct Fat12_ExtendedBootRecord *ExtBootRecord);
#endif
