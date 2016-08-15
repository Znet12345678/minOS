#ifndef __Z_FAT_H
#define __Z_FAT_H
#include <stdint.h>
struct fat16_bpb{
	uint64_t bytes_per_sector;
	uint64_t sectors_per_cluster;
	uint64_t resv_sectors;
	uint64_t num_of_fat;
	uint64_t num_of_dir_ent;
	uint64_t total_sectors;
	uint64_t mdt;
	uint64_t sectorsperfat;
	uint64_t sectorspertrack;
	uint64_t numberofheads;
	uint64_t numberofhiddensectors;
	uint64_t large_sectors;
};
struct fat16_bpb * parse_bpb();
#endif
