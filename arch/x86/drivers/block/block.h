#ifndef __Z_BDEV_H
#define __Z_BDEV_H
struct block_buf_head{
	char *data;
	unsigned short b_dev;
	unsigned short b_num;
	unsigned short b_dirt;
	unsigned short b_count;
	unsigned short lock;
	struct block_buf_head *next;
	struct block_buf_head *prev;
	struct block_buf_head *fnext;
	struct block_buf_head *fprev;
};
int block_read(int dev,long *pos,int cnt,char *buf);
int block_write(int dev,long *pos,int cnt,char *buf);
#endif
