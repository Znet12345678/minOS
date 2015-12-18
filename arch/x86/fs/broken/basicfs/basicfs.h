#ifndef __FAT_H
#define __FAT_H
typedef unsigned int device_type;
typedef unsigned char sector_t;
#define KBS 512
typedef struct fat_fs_12{
	unsigned char bootjump[3];
	unsigned char oem_name[8];
	unsigned short bps;
	unsigned char spc;
	unsigned short rsc;
	unsigned char tablecount;
	unsigned short root_ent_count;
	unsigned short ts16;
	unsigned short spt;
	unsigned short hsc;
	unsigned int hisc;
	unsigned int ts32;
	unsigned char es[54];
}fat_fs_12_t;
struct fat_bios_param_block{
	unsigned int fss;
	unsigned int fspc;
	unsigned int freserved;
	unsigned int fat_fats;
	unsigned int dirents;
	unsigned int fat_total_sect;
	unsigned int f16_state;
	unsigned int f16_vold_id;
	unsigned int f32_length;
	unsigned int f32_root_cluster;
	unsigned int f32_info_sector;
	unsigned int f32_state;
	unsigned int f32_vol_id;
};
static struct fat_floppy_defaults{
	unsigned nr_sectors;
	unsigned sectors_per_cluster;
	unsigned dirents;
	unsigned media;
	unsigned flen;
}floppy_defaults[] = {
{
	.nr_sectors = 160 * KBS,
	.sectors_per_cluster = 1,
	.dirents = 64,
	.media = 0xFE,
	.flen = 1,
},
{
	.nr_sectors = 180 * KBS,
	.sectors_per_cluster = 1,
	.dirents = 64,
	.media = 0xFC,
	.flen = 2,
},
{
	.nr_sectors = 320 * KBS,
	.sectors_per_cluster = 2,
	.dirents = 112,
	.media = 0xFF,
	.flen = 2,
},
{
	.nr_sectors = 368 * KBS,
	.sectors_per_cluster = 2,
	.dirents = 112,
	.media = 0xFD,
	.flen = 2, 	
},
};
struct lst_head{
	struct lst_head *next;
	struct lst_head *prev;
};
struct inode_base{
	struct super_block_base *i_sb;
	struct address_space *i_mapping;
	unsigned long  i_ino;
	union{
		const unsigned int i_nlink;
		unsigned int __i_nlink;
	};
	device_type i_rdev;
	int i_size;
	unsigned short i_bytes;
	unsigned int i_blkbits;
	unsigned long i_state;
	struct lst_head i_lru;
	struct lst_head i_sb_list;
	union{
		int n;
	};
	unsigned long i_version;
	struct addr_space_base *i_data;
	struct lst_head i_devices;
}inode;
struct rtreenode{
	unsigned int path;
	unsigned int count;
	union{
		struct{
			struct radix_tree_node *par;
			void *pd;
		};
	};
	struct lst_head priv_lst;
	void * slots[10];
	unsigned long tags[10];
}radix_tree_node;
struct rtreeroot{
	unsigned int height;
	struct radix_tree_node *rnode;
}radix_tree_root;
struct addr_space_base{
	struct inode_base *hst;
	struct rtreeroot pg_tree;
	unsigned int immap_write;
	struct rb_root immap;
	struct rw_semaphore immaprwsem;
	unsigned long nrpages;
	unsigned long nrshadows;
	struct lst_head *plst;
	unsigned long flags;
	void *pd;
}addr_space;

struct blkdev{
	device_type bd_dev;
	int bd_openers;
	struct inode_base * bd_inode;
	struct super_block_*base;
	struct lst_head bd_inodes;
	void * bd_claiming;	
	void * bd_holder;
	int bd_holders;
	int bd_write_holder;
	struct blkdev * bd_contains;
	unsigned bd_part_count;
	int bd_inval;
	struct gendisk * bd_disk;
	struct lst_head bd_lst;
}block_device;
struct buffer_head{
	struct buffer_head *next;
	struct buffer_head *prev;
};
static int fat_add_cluster(struct inode_base *inode);
static inline int _fgetblock(struct inode_base * ind,sector_t iblock,unsigned long max_blocks,struct buffer_head *bh_res,int create);
static int fgetblock(struct inode_base *imagenode,sector_t iblock, struct buffer_head *bh_res,int create);
static int fat_writepage(struct page *pg,struct writeback_control *wbc);
static int fat_writepages(struct addr_space_base * mapping,struct writeback_control wc);
static int fat_rdpg(struct file *f,struct page *pg);
static int fat_rdpgs(struct file *f,struct addr_space_base *mapping,struct lst_head *pgs,unsigned nr_pgs);
#endif
