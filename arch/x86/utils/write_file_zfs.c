#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <zfs.h>
#include <fcntl.h>
struct zfs_superblock *parse_superblock(char *fname,struct zfs_superblock *sblk);
int get_end(const char *fname){
	FILE *f;
	if(!(f = fopen(fname,"rb"))){
		printf("Couldn't open %s for reading",fname);
		return -1;
	}
	fseek(f,0,SEEK_END);
	int ret = ftell(f);
	fseek(f,0,SEEK_SET);
	//fclose(f);
	//if(fclose(f) < 0){
	//	printf("Error closing file!\n");
	//	return -1;
	//}
	//fseek(f,0,SEEK_SET);
	return ret;
}
int zero_out(const char *fname){
	FILE *f;
	if(!(f = fopen(fname,"r+b"))){
		printf("Couldn't open %s for writing",fname);
	}
	int end = get_end(fname);
	for(int i = 0; i < end;i++)
		fputc(0,f);
	fclose(f);
	return 1;
}
int find_datablk(struct zfs_superblock sblk,const char *fname){
	//int fds = sblk.fds;
	FILE *f;
	if(!(f = fopen(fname,"rb"))){
		printf("Couldn't open file:%s for reading\n",fname);
		return -1;
	}
	printf("[sblk.fds] %d\n",sblk.fds);
	fseek(f,sblk.fds * 512,SEEK_SET);
	int i = 0;
	int c = 0;
	int islong;
	int namelen;
	int isalloc = 0x0F;
	int found = 0;
	while(isalloc != EOF){
		//printf(".");
		isalloc = fgetc(f);
		if(isalloc == 0){
			found = 1;
			//printf(".\n");
			break;
		}
		islong = fgetc(f);
		if(islong == 1){
			namelen = getc(f);
			i+=(namelen + 12);
			fseek(f,sblk.fds * 512 + i,SEEK_SET);
		}
		else{
			i+=21;
			fseek(f,sblk.fds * 512 + i,SEEK_SET);
		}
	}
	if(found == 0){
		printf("Couldn't find unallocated block!\n");
		return -1;
	}
	//if(fclose(f) < 0){
	//	printf("Error closing file!\n");
	//	return -1;
	//}
	//printf(".\n");
	return i;
}
int write_datablk(struct zfs_superblock sblk,struct data *d,const char *fname,int loc){
	FILE *f;
	//printf("Allocating memory\n");
	/*printf("Allocating %d bytes\n",get_end(fname));
	char *buf = malloc(get_end(fname) + 10);
	printf("Reading buffer\n");
	if(!(read_buf(buf,fname)))
		return -1;
	*/
	if(!(f = fopen(fname,"r+b"))){
		printf("Couldnt open:%s for writing\n",fname);
		return -1;
	}

	//printf("Writing buffer\n");
	//write_buf(buf,fname);
	fseek(f,sblk.fds * 512 + loc,SEEK_SET);
	fputc(1,f);
	fputc(d->islongname,f);
	if(d->islongname)
		fputc(d->namelen,f);
	else
		fputc(0,f);
	if(d->islongname)
		for(int i = 0; i < d->namelen;i++)
			fputc(d->name[i],f);
	else{
		for(int i = 0; i < strlen(fname);i++)
			fputc(d->name[i],f);
		for(int i = 0; i < 10 - strlen(fname);i++)
			fputc(0,f);
	}
	fputc(d->startingblock >> 16,f);
	fputc(d->startingblock >> 8,f);
	fputc(d->startingblock,f);
	fputc(d->endingblock >> 16,f);
	fputc(d->endingblock >> 8,f);
	fputc(d->endingblock,f);
	fputc(d->endingpos >> 8,f);
	fputc(d->endingpos,f);
	//fclose(f);
	return 1;
}
int write_file(const char *buf,struct data *d,const char *fname){
	int pos = d->startingblock * 512;
	int end = d->endingblock * 512;
	FILE *f;
	if(!(f = fopen(fname,"r+b"))){
		printf("Couldn't open %s for writing",fname);
		return -1;
	}
	int j = 0;
	fseek(f,pos,SEEK_SET);
	while(pos < end){
		fputc(buf[j],f);
		pos++;
		j++;

	}
	fclose(f);
	return 1;
}
int read_buf(char *buf,const char *name){
	FILE *f;
	if(!(f = fopen(name,"rb"))){
		printf("Couldn't open %s for reading\n",name);
		return -1;
	}
	int c;
	int i = 0;
	while((c = fgetc(f)) != EOF){
		buf[i] = c;
		i++;
	}
	buf[i] = 0x0F;
        buf[i + 1] = 'E';
        buf[i + 2] = 0x0F;
        buf[i + 3] = 'O';
        buf[i + 4] = 0x0F;
        buf[i + 5] = 'F';
        buf[i + 6] = 0x0F;
	//if(fclose(f) < 0){
	//	printf("Error closing file!\n");
	//	return -1;
	//}
	return 1;
}
int write_buf(char *buf,const  char * name){
	FILE *f;
	if(!(f = fopen(name,"r+b"))){
		printf("Couldn't open %s for writing!\n",name);
		return -1;
	}
	int c;
	int i = 0;
	while(buf[i] != 0x0F && buf[i + 1] != 'E' && buf[i + 2] != 0x0F && buf[i + 3] != 'O' && buf[i + 4] != 0x0F && buf[i + 5] != 'F' && buf[i + 6] != 0x0F){
		fputc(buf[i],f);
		i++;
	}
	fclose(f);
	return 1;
}
int read_file(char *buf,struct data *d,const char *fname){
	int c;
	FILE *f;
	if(!(f = fopen(fname,"rb"))){
		printf("Couldn't open %s for reading!\n",fname);
		return -1;
	}
	int i = 0;
	while((c = fgetc(f)) != EOF){
		buf[i] = c;
		i++;
	}
	buf[i] = 0x0F;
	buf[i + 1] = 'E';
	buf[i + 2] = 0x0F;
	buf[i + 3] = 'O';
	buf[i + 4] = 0x0F;
	buf[i + 5] = 'F';
	buf[i + 6] = 0x0F;
	fclose(f);
	return 1;
}
int *find_unalloc_block(const char *filename,int numofblock,struct zfs_superblock superblk){
	//while(1) { }
	int start_blk = superblk.fds;
	printf("[filename] %s [numofblock] %d [start_blk] %d\n",filename,numofblock,start_blk);
	int i = 0;
	FILE *f;
	if(!(f = fopen(filename,"rb"))){
		printf("Couldnt open %s for reading", filename);
		return -1;
	}
	printf("Seeking\n");
	fseek(f,start_blk * 512,SEEK_SET);
	printf("Initialising variables\n");
	int needed = numofblock * 512;
	int got = 0;
	int c = 0xFF;
	int start;
	int end;
	int ret[2] = {-1,-1};
//	ret[0] = -1;
//	ret[1] = -1;
	int orig = start_blk * 512;
	int pos = start_blk * 512;
	while((c = fgetc(f)) != EOF){
		//printf(".");
		if(got == needed && c == 0){
			end = pos / 512;
			ret[1] = end;
			return ret;
		}
		else if(c == 0 && (pos % 512) == 0){
			if(ret[0] == -1)
				ret[0] = pos;
			got++;
			pos++;
		}
		else if(c == 0){
			got++;
		}
		else{
			got = 0;
			ret[0] = -1;
			ret[1] = -1;
		}
	}
	printf("Couldn't find enough freespace on drive!\n");
	if(fclose(f) < 0){
		printf("Error closing file!\n");
		return -1;
	}
	return -1;
}
struct data *parse_file(char *buf,const char *filename,char *_filename){
	struct zfs_superblock *sblk = malloc(sizeof(struct zfs_superblock *));
	parse_superblock(filename,sblk);
	int end = 0;
	while(1){
		if(buf[end] == 0x0F && buf[end + 1] == 'E' && buf[end + 2] == 0x0F && buf[end + 3] == 'O' && buf[end + 4] == 0x0F && buf[end + 5] == 'F' && buf[end + 6] == 0x0F)
			break;
		end++;
	}
	end--;
	printf("[end] %d [sblk.fds] %d\n",end,sblk->fds);
	struct data *ret = malloc(sizeof(struct data *));
	int *se = malloc(80);
	if((end % 512) == 0)
		se = find_unalloc_block(filename,end,*sblk);
	else
		se = find_unalloc_block(filename,end,*sblk);
	if(!(se)){
		printf("Error finding unallocated block!\n");
		return -1;
	}
	printf("[se(0)] %d [se(1)] %d\n",se[0],se[1]);
	ret->alloc = 1;
	ret->startingblock = se[0];
	ret->endingblock = se[1];
	if(strlen(_filename) > 10)
		ret->islongname = 1;
	else
		ret->islongname = 0;
	if(ret->islongname)
		ret->namelen = strlen(filename);
	else
		ret->namelen = 0;
	ret->name = _filename;
	ret->type = TYPE_FILE;
	ret->blockpos = ret->startingblock;
	return ret;
}
struct zfs_superblock *parse_superblock(char *name,struct zfs_superblock *ret){
	//struct zfs_superblock *ret = malloc(sizeof(struct zfs_superblock *));
	FILE *f = fopen(name,"r+b");
	if(!(f))
		return -1;
	char *buf = malloc(2048);
	//fread(buf,1050,1,f);
	int c;
	for(int i = 0;i < 1050 && c != EOF;i++){
		c = fgetc(f);
		buf[i] = c;
	}
	//fread(f,buf,1050);
	ret->allocblk = buf[1024] << 24 | buf[1025] << 16 | buf[1026] << 8 | buf[1027];
	ret->unallocblk = buf[1028] << 24 | buf[1029] << 16 | buf[1030] << 8 | buf[1031];
	ret->tblk = ret->allocblk + ret->unallocblk;
	ret->dataresv = buf[1036] << 8 | buf[1037];
	ret->rootfsblk = buf[1038] << 8 | buf[1039];
	ret->numoff = buf[1040] << 24 | buf[1041] << 16 | buf[1042] << 8 | buf[1043];
	ret->numofd = buf[1044] << 24 | buf[1045] << 16 | buf[1046] << 8 | buf[1047];
	ret->fds = buf[1048] << 8 | buf[1049];
	free(buf);
	return ret;
	/*ret->allocblk = (buf[1024] << 16) * 10000 | (buf[1025] << 8) * 10000 | buf[1026] * 10000 | buf[1027] << 16 | buf[1028] << 8 | buf[1029];
	ret->unallocblk = (buf[1030] << 16) * 10000 | (buf[1031] << 8) * 10000 | buf[1032] * 10000 | buf[1033] << 16 | buf[1034] << 8 | buf[1035];
	ret->tblk = ret->allocblk + ret->unallocblk;
	ret->dataresv = buf[1036] << 16 | buf[1037] << 8 | buf[1038];
	ret->rootfsblk = buf[1039] << 8 | buf[1040];
	ret->numoff = buf[1041] << 16 | buf[1042] << 16 | buf[1043] << 8 | buf[1044];
	ret->numofd = buf[1045] << 16 | buf[1046] << 16 | buf[1047] << 8 | buf[1048];
	ret->fds = buf[1049] << 8 | buf[1050];
	/*int e,s;
	if(buf[1024] == 0x0F){
		printf("Error reading superblock:drive too big\n");
		return -1;
	}
	else if(buf[1024] = 0x0E){
		s = (buf[1025] * 1000) << 16;
		if(buf[1026] == 0x0F){
			printf("Error reading superblock:drive too big\n");
			return -1;
		}
		else if(buf[1026] == 0x0E){
			e = (buf[1027] * 100000) << 8;
		}
	 	else if(buf[1026] == 0x0D){
                        e = (buf[1027] * 10000) << 8;
                }
		else if(buf[1026] == 0x0C){
                        e = (buf[1027] * 1000) << 8;
                }
		else if(buf[1026] == 0x0B){
                        e = (buf[1027] * 100) << 8;
                }
		else if(buf[1026] == 0x0A){
			e = buf[1027] << 8;
		}
	}
	 else if(buf[1024] = 0x0D){
                s = (buf[1025] * 100) << 16;
                if(buf[1026] == 0x0F){
                        printf("Error reading superblock:drive too big\n");
                        return -1;
                }
                else if(buf[1026] == 0x0E){
                        e = (buf[1027] * 100000) << 8;
                }
                else if(buf[1026] == 0x0D){
                        e = (buf[1027] * 10000) << 8;
                }
                else if(buf[1026] == 0x0C){
                        e = (buf[1027] * 1000) << 8;
                }
                else if(buf[1026] == 0x0B){
                        e = (buf[1027] * 100) << 8;
                }
		else if(buf[1026] == 0x0A){
                        e = buf[1027] << 8;
                }
        }
	else if(buf[1024] == 0x0C){
		s = buf[1025] << 16;
                if(buf[1026] == 0x0F){
                        printf("Error reading superblock:drive too big\n");
                        return -1;
                }
                else if(buf[1026] == 0x0E){
                        e = (buf[1027] * 100000) << 8;
                }
                else if(buf[1026] == 0x0D){
                        e = (buf[1027] * 10000) << 8;
                }
                else if(buf[1026] == 0x0C){
                        e = (buf[1027] * 1000) << 8;
                }
                else if(buf[1026] == 0x0B){
                        e = (buf[1027] * 100) << 8;
                }
                else if(buf[1026] == 0x0A){
                        e = buf[1027] << 8;
                }

	}
	ret->allocblk = s | e | buf[1028];
	*/
	return ret;
}
void usage(const char *name){
	printf("%s diskimage file\n",name);
}
int main(int argc, char* argv[]){
	if(argc != 3){
		usage(argv[0]);
		return -1;
	}
	FILE *f;
	if(!(f = fopen(argv[1],"r"))){
		printf("Error opening file:%s\n",argv[1]);
		return -1;
	}
	fclose(f);
	if(!(f = fopen(argv[2],"r"))){
		printf("Error opening file:%s\n",argv[2]);
	}
	char *buf = malloc(get_end(argv[1]));
	printf("Reading file to buf\n");
	if(!(read_buf(buf,argv[1]))){
		printf("Error reading to buffer!\n");
		return -1;
	}
	printf("Erasing %s\n",argv[1]);
	if(!(zero_out(argv[1]))){
		printf("Error erasing %s\n",argv[1]);
	}
	printf("Rewriting\n");
	if(!(write_buf(buf,argv[1]))){
		printf("Error restoring %s\n",argv[1]);
	}
	printf("freeing memory\n");
	free(buf);
	printf("Reading buffer\n");
	buf = malloc(get_end(argv[1]));
	read_buf(buf,argv[1]);
	printf("Parsing superblock\n");
	struct zfs_superblock *sblk = malloc(sizeof(struct zfs_superblock *));
	parse_superblock(argv[1],sblk);
	if(!(sblk))
		return -1;
	printf("Dumping: [allocblk] %d [unallocblk] %d [tblk]   %d\n         [dataresv] %d [rootfsblk]  %d [numoff] %d\n         [numofd]   %d [fds]        %d\n",sblk->allocblk,sblk->unallocblk,sblk->tblk,sblk->dataresv,sblk->rootfsblk,sblk->numoff,sblk->numofd,sblk->fds);
	printf("Finding datablock\n");
	int db = find_datablk(*sblk,argv[1]);
	if(db < 0){
		printf("Error finding datablock!\n");
		return -1;
	}
	printf("freeing buffer\n");
	free(buf);
	printf("Allocating memory\n");
	buf = malloc(get_end(argv[2]));
	if(!(buf)){
		printf("Error allocating %d bytes of memory!\n",get_end(argv[2]));
	}
	printf("Reading buffer\n");
	if(!(read_buf(buf,argv[2]))){
		printf("Error reading buffer!\n");
		return -1;;
	}
	printf("Parsing file\n");
	struct data *d = parse_file(buf,argv[1],argv[2]);
	if(!(d)){
		printf("Error parsing file!\n");
		return -1;
	}
	printf("Dumping: [alloc]           %d   [islongname]   %d   [namelen]   %d   [name]     %s\n         [type]            %d   [offset]       %d   [endingpos] %d   [blockpos] %d\n         [startingblock]   %d   [endingblock]  %d\n"
	,d->alloc,d->islongname,d->namelen,d->name,d->type,d->offset,d->endingpos,d->blockpos,d->startingblock,d->endingblock);
	printf("Writing datablock\n");
	if(!(write_datablk(*sblk,d,argv[1],db))){
		printf("Error writing datablock!\n");
		return -1;
	}
}


