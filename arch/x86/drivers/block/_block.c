#include "block.h"
int block_read(int dev,long *pos,int cnt,char *buf){
	int blk= *pos/1024;
	int offs = *pos% 1024;
}
