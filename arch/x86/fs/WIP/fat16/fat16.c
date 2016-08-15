#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fat16.h"
struct fat16_bpb * parse_bpb(){
	struct fat16_bpb *ret = malloc(sizeof(struct fat16_bpb *));
	char *buf = malloc(1024);
	ata_read_master(buf,0,0);
	ret->bytes_per_sector = buf[11] << 8 | buf[12];
	ret->sectors_per_cluster = buf[13];
	kprintf("%d\n",ret->sectors_per_cluster);
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
