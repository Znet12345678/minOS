#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ata.h>
#include "zfs.h"
struct zfs_superblock *read_superblock(struct zfs_superblock *ret){
	char *buf = malloc(1024);
	ata_read_master(buf,2,0);
	ret->allocblk = buf[0] << 24 | buf[1] << 16 | buf[2] << 8 | buf[3];
	ret->unallocblk = buf[4] << 24 | buf[5] << 16 | buf[6] << 8 | buf[7];
	ret->tblk = buf[8] << 24 | buf[9] << 16 | buf[10] << 8 | buf[11];
	ret->dataresv = buf[12] << 8 | buf[13];
	ret->rootfsblk = buf[14] << 8 | buf[15];
	ret->numoff = buf[16] << 24 | buf[17] << 16 | buf[18] << 8 | buf[19];
	ret->numofd = buf[20] << 24 | buf[21] << 16 | buf[22] << 8 | buf[23];
	ret->fds = buf[24] << 8 | buf[25];
	return ret; 
	/*int i = 0;
	if(buf[2] == 0){
		ret->allocblk = (buf[i] << 16 | buf[++i] << 8 | buf[++i]);
	}
	else if(buf[2] == 1){
	
	}
	//ret->allocblk = (buf[0] << 16) * 10000 | (buf[1] << 8) * 10000 | (buf[2]) * 10000 | buf[3] << 16 | buf[4] < 8 | buf[5];
	//ret->unallocblk = (buf[6] << 16) * 10000 |(buf[7] << 8) * 10000 | buf[8] * 10000 | buf[9] << 16 | buf[10] << 8 | buf[11];
	ret->tblk = buf[12] << 16 | buf[13] << 8 | buf[14];
	ret->dataresv = buf[15] << 8 | buf[16];
	ret->rootfsblk = buf[17] << 8 | buf[18];
	ret->numoff = buf[19] << 16 | buf[20] << 16 | buf[21] << 8 | buf[22];
	ret->numofd = buf[23] << 16 | buf[24] << 16 | buf[25] << 8 | buf[26];
	ret->fds = buf[27] << 8 | buf[28];
	return ret;*/
	int s =-1, e = -1;
	/*if(buf[0] == 0x0F){
		kprintf("Reading superblock has failed!\npanic();\n");
		panic();
	}
	//int s = -1, e = -1;
	else if(buf[0] == 0x0E){
		s = (buf[1] * 1000) << 16;
		if(buf[2] == 0x0F){
			kprintf("Reading superblock has failed!\npanic();\n");
	                panic();
		}
		else if (buf[2] == 0x0E){
			e = (buf[3] * 100000) << 8;
		}
		else if (buf[2] == 0x0D){
                        e = (buf[3] * 10000) << 8;
                }
		else if (buf[2] == 0x0C){
                        e = (buf[3] * 1000) << 8;
                }
		else if (buf[2] == 0x0B){
                        e = (buf[3] * 100) << 8;
                }
		else if (buf[2] == 0x0A){
                        e = (buf[3]) << 8;
                }
		//else if (buf[2] == 0x09){
                //        e = (buf[3]) << 8;
               // }
		else{
			kprintf("Unkown error!\n");
			panic();
		}
		

	}
	else if(buf[0] == 0x0D){
		 s = (buf[1] * 100) << 16;
                if(buf[2] == 0x0F){
                       kprintf("Reading superblock has failed!\npanic();\n");
                        panic();
                }
                else if (buf[2] == 0x0E){
                        e = (buf[3] * 100000) << 8;
                }
                else if (buf[2] == 0x0D){
                        e = (buf[3] * 10000) << 8;
                }
                else if (buf[2] == 0x0C){
                        e = (buf[3] * 1000) << 8;
                }
                else if (buf[2] == 0x0B){
                        e = (buf[3] * 100) << 8;
                }
 		else if (buf[2] == 0x0A){
                        e = (buf[3]) << 8;
                }
               // else if (buf[2] == 0x09){
                 //       e = (buf[3]) << 8;
               // }
                else{
                       kprintf("Unkown error!\n");
                        panic();
                }
	}
	else if(buf[0] == 0x0C){
                 s = (buf[1]) << 16;
                if(buf[2] == 0x0F){
                       kprintf("Reading superblock has failed!\npanic();\n");
                        panic();
                }
                else if (buf[2] == 0x0E){
                        e = (buf[3] * 100000) << 8;
                }
                else if (buf[2] == 0x0D){
                        e = (buf[3] * 10000) << 8;
                }
                else if (buf[2] == 0x0C){
                        e = (buf[3] * 1000) << 8;
                }
                else if (buf[2] == 0x0B){
                        e = (buf[3] * 100) << 8;
                }
                else if (buf[2] == 0x0A){
                        e = (buf[3]) << 8;
                }
	//	else if (buf[2] == 0x09){
            //            e = (buf[3]) << 8;
            ///    }
                else{
                       kprintf("Unkown error!\n");
                        panic();
                }

	}
	/*else if(buf[0] == 0x0B){
 		s = buf[1] << 16;
                if(buf[2] == 0x0F){
                       kprintf("Reading superblock has failed!\npanic();\n");
                        panic();
                }
                else if (buf[2] == 0x0E){
                        e = (buf[3] * 100000) << 8;
                }
                else if (buf[2] == 0x0D){
                        e = (buf[3] * 10000) << 8;
                }
                else if (buf[2] == 0x0C){
                        e = (buf[3] * 1000) << 8;
                }
                else if (buf[2] == 0x0B){
                        e = (buf[3] * 100) << 8;
                }
                else if (buf[2] == 0x0A){
                        e = (buf[3] * 10) << 8;
                }
                else if (buf[2] == 0x09){
                        e = (buf[3]) << 8;
                }
                else{
                       kprintf("Unkown error!\n");
			return -1;
		}
	}
	else if(buf[0] == 0)
		s = 0; e = 0;
	ret->allocblk = s  | e  |buf[4];
	if(buf[5] == 0x0F){
		kprintf("Reading superblock has failed!\n");
		panic();
	}
	else if(buf[5] == 0x0E){
		s = (buf[6] * 1000) << 16;
		if(buf[7] == 0x0F){
                       kprintf("Reading superblock has failed!\npanic();\n");
                        panic();
                }
                else if (buf[7] == 0x0E){
                        e = (buf[8] * 100000) << 8;
                }
                else if (buf[7] == 0x0D){
                        e = (buf[8] * 10000) << 8;
                }
                else if (buf[7] == 0x0C){
                        e = (buf[8] * 1000) << 8;
                }
                else if (buf[7] == 0x0B){
                        e = (buf[8] * 100) << 8;
                }
                else if (buf[7] == 0x0A){
                        e = (buf[8]) << 8;
                }
               // else if (buf[7] == 0x09){
                 //       e = (buf[8]) << 8;
               // }
                else{
                       kprintf("Unkown error!\n");
			panic();
                        return -1;
                }

	}
	else if(buf[5] == 0x0D){
                s = (buf[6] * 100) << 16;
                if(buf[7] == 0x0F){
                       kprintf("Reading superblock has failed!\npanic();\n");
                        panic();
                }
                else if (buf[7] == 0x0E){
                        e = (buf[8] * 100000) << 8;
                }
                else if (buf[7] == 0x0D){
                        e = (buf[8] * 10000) << 8;
                }
                else if (buf[7] == 0x0C){
                        e = (buf[8] * 1000) << 8;
                }
                else if (buf[7] == 0x0B){
                        e = (buf[8] * 100) << 8;
                }
                else if (buf[7] == 0x0A){
                        e = (buf[8]) << 8;
                }
                else if (buf[7] == 0x09){
                        e = (buf[8]) << 8;
                }
                else{
                       kprintf("Unkown error!\n");
                        return -1;
                }

        }
	else if(buf[5] == 0x0C){
                s = (buf[6]) << 16;
                if(buf[7] == 0x0F){
                       kprintf("Reading superblock has failed!\npanic();\n");
                        panic();
                }
                else if (buf[7] == 0x0E){
                        e = (buf[8] * 100000) << 8;
                }
                else if (buf[7] == 0x0D){
                        e = (buf[8] * 10000) << 8;
                }
                else if (buf[7] == 0x0C){
                        e = (buf[8] * 1000) << 8;
                }
                else if (buf[7] == 0x0B){
                        e = (buf[8] * 100) << 8;
                }
                else if (buf[7] == 0x0A){
                        e = (buf[8]) << 8;
                }
                else if (buf[7] == 0x09){
                        e = (buf[8]) << 8;
                }
                else{
                       kprintf("Unkown error!\n");
                        return -1;
                }

        }
	else if(buf[5] == 0x0B || buf[5] == 0x0A){
                s = (buf[6]) << 16;
                if(buf[7] == 0x0F){
                       kprintf("Reading superblock has failed!\npanic();\n");
                        panic();
                }
                else if (buf[7] == 0x0E){
                        e = (buf[8] * 100000) << 8;
                }
                else if (buf[7] == 0x0D){
                        e = (buf[8] * 10000) << 8;
                }
                else if (buf[7] == 0x0C){
                        e = (buf[8] * 1000) << 8;
                }
                else if (buf[7] == 0x0B){
                        e = (buf[8] * 100) << 8;
                }
                else if (buf[7] == 0x0A){
                        e = (buf[8] * 10) << 8;
                }
                else if (buf[7] == 0x09){
                        e = (buf[8]) << 8;
                }
                else{
                       kprintf("Unkown error!\n");
                        return -1;
                }

        }

	ret->unallocblk = s | e | buf[9];
	if(buf[10] == 0x0F){
		kprintf("Drive too big!\n");
		panic();
	}
	else if(buf[10] == 0x0E){
                s = (buf[11] * 1000) << 16;
                if(buf[12] == 0x0F){
                       kprintf("Reading superblock has failed!\npanic();\n");
                        panic();
                }
                else if (buf[12] == 0x0E){
                        e = (buf[13] * 100000) << 8;
                }
                else if (buf[12] == 0x0D){
                        e = (buf[13] * 10000) << 8;
                }
                else if (buf[12] == 0x0C){
                        e = (buf[13] * 1000) << 8;
                }
                else if (buf[12] == 0x0B){
                        e = (buf[13] * 100) << 8;
                }
                else if (buf[12] == 0x0A){
                        e = (buf[13]) << 8;
                }
                else if (buf[12] == 0x09){
                        e = (buf[13]) << 8;
                }
                else{
                       kprintf("Unkown error!\n");
                        panic();
                }

        }
	else if(buf[10] == 0x0D){
                s = (buf[11] * 100) << 16;
                if(buf[12] == 0x0F){
                       kprintf("Reading superblock has failed!\npanic();\n");
                        panic();
                }
                else if (buf[12] == 0x0E){
                        e = (buf[13] * 100000) << 8;
                }
                else if (buf[12] == 0x0D){
                        e = (buf[13] * 10000) << 8;
                }
                else if (buf[12] == 0x0C){
                        e = (buf[13] * 1000) << 8;
                }
                else if (buf[12] == 0x0B){
                        e = (buf[13] * 100) << 8;
                }
                else if (buf[12] == 0x0A){
                        e = (buf[13]) << 8;
                }
                else if (buf[12] == 0x09){
                        e = (buf[13]) << 8;
                }
                else{
                       kprintf("Unkown error!\n");
                        panic();

		}
	}
 	else if(buf[10] == 0x0C){
                s = (buf[11] ) << 16;
                if(buf[12] == 0x0F){
                       kprintf("Reading superblock has failed!\npanic();\n");
                        panic();
                }
                else if (buf[12] == 0x0E){
                        e = (buf[13] * 100000) << 8;
                }
                else if (buf[12] == 0x0D){
                        e = (buf[13] * 10000) << 8;
                }
                else if (buf[12] == 0x0C){
                        e = (buf[13] * 1000) << 8;
                }
                else if (buf[12] == 0x0B){
                        e = (buf[13] * 100) << 8;
                }
                else if (buf[12] == 0x0A){
                        e = (buf[13]) << 8;
                }
                else if (buf[12] == 0x09){
                        e = (buf[13]) << 8;
                }
                else{
                       kprintf("Unkown error!\n");
                        panic();

                }
        }
	 else if(buf[10] == 0x0B){
                s = (buf[11]) << 16;
                if(buf[12] == 0x0F){
                       kprintf("Reading superblock has failed!\npanic();\n");
                        panic();
                }
                else if (buf[12] == 0x0E){
                        e = (buf[13] * 100000) << 8;
                }
                else if (buf[12] == 0x0D){
                        e = (buf[13] * 10000) << 8;
                }
                else if (buf[12] == 0x0C){
                        e = (buf[13] * 1000) << 8;
                }
                else if (buf[12] == 0x0B){
                        e = (buf[13] * 100) << 8;
                }
                else if (buf[12] == 0x0A){
                        e = (buf[13] * 10) << 8;
                }
                else if (buf[12] == 0x09){
                        e = (buf[13]) << 8;
                }
                else{
                       kprintf("Unkown error!\n");
                        panic();

                }
        }
	ret->tblk = s | e | buf[14];
	ret->dataresv = buf[15] << 8 | buf[16];
	ret->rootfsblk = buf[17] << 8 | buf[18];
	ret->numoff = buf[19] << 16 | buf[20] << 8 | buf[21];
	ret->numofd = buf[22] << 16 | buf[23] << 8 | buf[24];
	ret->fds = buf[25] << 8 | buf[26];
	return ret;*/
}
struct file_struct *zfs_request_file(const char *filename,char *op){
	struct file_struct *ret = malloc(1024);
	int found = 0;
	if(strcmp(op,"r") == 0){
		ret->posx = 0;
		ret->posy = 0;
		ret->pos = 0;
		ret->filename = filename;
		ret->opperation = OP_READ;
		struct zfs_superblock *sblk = malloc(1024);
		read_superblock(sblk);
		int i = 0;
		int j = sblk->fds;
		int n = sblk->dataresv;
		//int found;
		while(i < n){
			char *buf = malloc(1024);
			ata_read_master(buf,j,0);
			struct data *data = malloc(1024);
			int k = 0;
			int a = 0;
			int b = 30;
			while(k < b){
				data->alloc = buf[a * k];
				data->islongname = buf[a * k + 1];
				if(data->alloc == 0){
					a++;k++;
					continue;
				}
				else if(data->islongname && strlen(filename) > 10){
					data->namelen = buf[a * k + 2];
					b-=(data->namelen / 10);
					data->name = malloc(1024);
					int c;
					for( c = 0; c < data->namelen;c++){
						data->name[c] = buf[a * k + 3 + c];
					}
					if(strcmp(data->name,filename) == 0){
						found = 1;
						ret->offset = a * k + 3 + c;
						ret->startingblock = buf[a * k  + data->namelen + 4] << 16 | buf[a * k + data->namelen + 5] << 8 | buf[a * k + data->namelen +6];
						ret->endingblock = buf[a * k + data->namelen + 7] << 16 | buf[a * k + data->namelen + 8] << 8 | buf[a * k + data->namelen + 9];
						ret->endingpos = buf[a * k + data->namelen + 11] << 8 | buf[a * k + data->namelen + 12];
						ret->blockpos = ret->startingblock;
						break;
					}


				}
				else if(strlen(filename) < 10 && data->islongname){
					a++;k++;
					continue;
				}
				else if(strlen(filename) < 10 && !(data->islongname)){
					data->name = malloc(1024);
					int c;
					for(c = 0; c < 10;c++){
						data->name[c] = buf[a * k + 3 + c];
					}
					if(strcmp(data->name,filename) == 0){
						found = 1;
						ret->offset = a * k + 13;
						ret->startingblock = buf[a * k + 14] << 16 | buf[a * k + 15] << 8 | buf[a * k + 16];
						ret->endingblock = buf[a * k + 17] << 16 | buf[a * k + 18] << 8 | buf[a * k + 19];
						ret->endingpos = buf[a * k + 20] << 8 | buf[a * k + 21];
						ret->blockpos = ret->startingblock;
						break;
					}
				}
				a++;
				k++;
			}
			i++;j++;
		}
	}
	if(found != 1){
		kprintf("Aborted:Couldn't find file\n");
		return -1;
	}
	/*char *fbuf = malloc(512 * (ret->endingblock - ret->startingblock));
	char *blk = malloc(1024);
	int d;
	int f = 0;
	for(d = ret->startingblock; d < ret->endingblock;d++){
		ata_read_master(blk,d,0);
		for(int e = 0; e < 512;e++,f++){
			fbuf[f] = blk[e];
		}
		blk = malloc(1024);
	}*/
	return ret;
}
int seek(struct file_struct *f,int n){
	f->pos = n % 512;
	f->blockpos = n / 512;
	f->tpos = n;
	return 1;
}
int fs_read(char *buf,struct file_struct *f,int n){
	int read = 0;
	char *blk = malloc(513);
	int d = f->blockpos;
	int _f = 0;
		/*if(f->endingpos == 512){
			for(d = f->startingblock; d < (f->endingblock + 1); d++){
				ata_read_master(blk,d,0);
				for(int e = 0; e < 512; e++,f++){
					buf[f] = blk[e];
				}
				f->pos+=512;
			}
			return ((f->endingblock - f->startingblock) * 512);
		}
		else{
			for(d = f->startingblock; d < (f->endingblock + 1); d++){
				ata_read_master(blk,d,0);
				if(d == f->endingblock){
					for(int g = 0; g < f->endingpos;g++,f++)
						buf[f] = blk[g];
					f->pos+=f->endingpos;
				}
				else{
					for(int g = 0; g < 512;g++,f++)
						buf[f] = blk[g]
					f->pos+=f->endingpos;
				}
			}
			return (((f->endingblock - f->startingblock) * 512) - f->endingpos);

		}*/
	//if((b->endingblock - b->startingblock) == n / 512){
		if(f->endingpos == 512){
			for(int i = (f->blockpos); i <= f->endingblock && read < n;i++){
				f->pos = f->tpos % 512;
				ata_read_master(blk,i,0);
				for(int j = f->pos; j < 512;j++,_f++){
					buf[_f] = blk[j];
					f->tpos++;
					f->pos++;
					read++;
				}
				//f->pos = 0;
				f->blockpos++;
				blk = malloc(1024);
			}
		}
		else{
			for(int i = f->blockpos / 512; i <=f->endingblock && read < n; i++){
				f->pos = f->tpos % 512;
				ata_read_master(blk,i,0);
				if(i == f->endingblock){
					for(int j = f->pos; j < f->endingpos;j++,_f++){
						buf[_f] = blk[j];
						read++;
						f->tpos++;
						f->pos++;
					}
					return read;
				}
				else{
					for(int j = f->pos ; j < 512;j++,_f++){
						buf[_f] = blk[j];
						read++;
						f->pos++;
					}
					return read;
				}
				f->blockpos++;
			}
		}
	//}
	//else if((f->endingblock - f->startingblock) > (n / 512)){
	//	int read = 0;
	//	for(int i = f->blockpos; i <= f->endingblock && read < n;i++){
	//		ata_read_master(buf,d,0);
	//		if(i == f->endingblock&& f->endingpos != 512){
	//			for(
	//		}
	//	}
	//}

}

