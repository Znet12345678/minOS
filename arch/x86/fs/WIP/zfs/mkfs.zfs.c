#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int mkfszfs(char *filename){
	FILE *f;
	printf("Getting file size\n");
	if(!(f = fopen(filename,"r")))
		return -1;
	fseek(f,0,SEEK_END);
	const int i = ftell(f);
	printf("Size:%d bytes\n",i);
	fseek(f,0,SEEK_SET);
	fclose(f);
	if(!(f = fopen(filename,"wb")))
		return -1;
	printf("Zeroing file\n");
	for(int j = 0; j < i;j++){
		putc(0,f);
	}
	printf("Writing superblock\n");
	fseek(f,1024,SEEK_SET);
	putc(0,f);
	putc(0,f);
	putc(0,f);
	putc(0,f);
	putc((i / 512) >> 24,f);
	putc((i / 512) >> 16,f);
	putc((i / 512) >> 8 ,f);
	putc((i / 512)      ,f);
        putc((i / 512) >> 24,f);
        putc((i / 512) >> 16,f);
        putc((i / 512) >> 8 ,f);
        putc((i / 512)      ,f);

	/*int e;
	printf("Disk size: %d\n",i);
	int s = (i / 512) >> 16;
	if(s > 10000){
		printf("Failed to write superblock:disk too big!\n");
		return -1;
		putc(0x0F,f);
	}
	else if(s > 1000){
		putc(0x0E,f);
		putc(s/1000,f);
		 e = (i / 512) >> 8;
		if(e > 1000000){
			printf("Failed to write superblock:disk too big!\n");
			return -1;
		}
		else if(e > 100000){
			putc(0x0E,f);
			putc(e / 100000,f);
			putc(0,f);
		}
		else if(e > 10000){
			putc(0x0D,f);
			putc(e / 10000,f);
			putc(0,f);
		}
		else if(e > 1000){
			putc(0x0C,f);
			putc(e / 1000,f);
			putc(0,f);
		}
		else if(e > 100){
			putc(0x0B,f);
			putc(e / 100,f);
			putc(0,f);
		}
		else if(e > 0){
			putc(0x0A,f);
			putc(e,f);
			putc(0,f);
		}
		/*else if(e > 0){
			putc(0x09,f);
			putc(e,f);
			putc(0,f);
		}
		else{
			printf("Unkown error!\nfunc:mkfszfs(%s) section if(s > 1000){...} else{printf(this); return -1;}\n ",filename);
			return -1;
		}
	}
	else if(s > 100){
                putc(0x0D,f);
                putc(s/100,f);
                e = (i / 512) >> 8;
                if(e > 1000000){
                        printf("Failed to write superblock:disk too big!\n");
                        return -1;
                }
                else if(e > 100000){
                        putc(0x0E,f);
                        putc(e / 100000,f);
                        putc(0,f);
                }
                else if(e > 10000){
                        putc(0x0D,f);
                        putc(e / 10000,f);
                        putc(0,f);
                }
                else if(e > 1000){
                        putc(0x0C,f);
                        putc(e / 1000,f);
                        putc(0,f);
                }
                else if(e > 100){
                        putc(0x0B,f);
                        putc(e / 100,f);
                        putc(0,f);
                }
                else if(e > 0){
                        putc(0x0A,f);
                        putc(e,f);
                        putc(0,f);
                }
		/* else if(e > 0){
                        putc(0x09,f);
                        putc(e,f);
                        putc(0,f);
                }
                else{
                        printf("Unkown error!\nfunc:mkfszfs(%s) section if(s > 100){...} else{printf(this); return -1;}\n ",filename);
                        return -1;
                }
        }
	else if(s > 10){
		putc(0x0C,f);
                putc(s,f);
                e = (i / 512) >> 8;
                if(e > 1000000){
                        printf("Failed to write superblock:disk too big!\n");
                        return -1;
                }
                else if(e > 100000){
                        putc(0x0E,f);
                        putc(e / 100000,f);
                        putc(0,f);
                }
                else if(e > 10000){
                        putc(0x0D,f);
                        putc(e / 10000,f);
                        putc(0,f);
                }
                else if(e > 1000){
                        putc(0x0C,f);
                        putc(e / 1000,f);
                        putc(0,f);
                }
                else if(e > 100){
                        putc(0x0B,f);
                        putc(e / 100,f);
                        putc(0,f);
                }
		 else if(e > 0){
                        putc(0x0A,f);
                        putc(e,f);
                        putc(0,f);
                }
                /* else if(e > 0){
                        putc(0x09,f);
                        putc(e,f);
                        putc(0,f);
                }
                else{
                        printf("Unkown error!\nfunc:mkfszfs(%s) section if(s > 10){...} else{printf(this); return -1;}\n ",filename);
			printf("[s] %d [e] %d  [i/512] %d [i] %d\n",s,e,(i/512),i);
                        return -1;
                }
        }
	else if (s > 0){
		putc(0x0C,f);
                putc(s,f);
                e = (i / 512) >> 8;
                if(e > 1000000){
                        printf("Failed to write superblock:disk too big!\n");
                        return -1;
                }
                else if(e > 100000){
                        putc(0x0E,f);
                        putc(e / 100000,f);
                        putc(0,f);
                }
                else if(e > 10000){
                        putc(0x0D,f);
                        putc(e / 10000,f);
                        putc(0,f);
                }
		else if(e > 1000){
                        putc(0x0C,f);
                        putc(e / 1000,f);
                        putc(0,f);
                }
                else if(e > 100){
                        putc(0x0B,f);
                        putc(e / 100,f);
                        putc(0,f);
                }
                 else if(e > 0){
                        putc(0x0A,f);
                        putc(e,f);
                        putc(0,f);
                }
                else{
                        printf("Unkown error!\nfunc:mkfszfs(%s) section if(s > 1){...} else{printf(this); return -1;}\n ",filename);
                        return -1;
                }

	}
	else{
		
		//printf("Disk too small:%d sectors\n",(i / 512));
		 putc(0x0C,f);
                putc(s,f);
                e = (i / 512) >> 8;
                if(e > 1000000){
                        printf("Failed to write superblock:disk too big!\n");
                        return -1;
                }
                else if(e > 100000){
                        putc(0x0E,f);
                        putc(e / 100000,f);
                        putc(0,f);
                }
                else if(e > 10000){
                        putc(0x0D,f);
                        putc(e / 10000,f);
                        putc(0,f);
                }
		  else if(e > 1000){
                        putc(0x0C,f);
                        putc(e / 1000,f);
                        putc(0,f);
                }
                else if(e > 100){
                        putc(0x0B,f);
                        putc(e / 100,f);
                        putc(0,f);
                }
                 else if(e > 0){
                        putc(0x0A,f);
                        putc(e,f);
                        putc(0,f);
                }
                else{
                        printf("Unkown error!\nfunc:mkfszfs(%s) section if(s > 1){...} else{printf(this); return -1;}\n ",filename);
                        return -1;
                }


	}
	printf("[s] %d [e] %d\n",s,e);
	/*putc((i / 512) >> 16,f);
	putc((i / 512) >> 8),f);
	putc((i / 512,f);
	/*putc((i / 512) >> 16,f);
	putc(((i / 512) >> 8) / 100,f);
	if((((i / 512) >> 8) / 100) > 100){
		putc(3,f);
	}
	else if((((i / 512) >> 8) / 100) > 10){
		putc(2,f);
	}
	else if((((i / 512) >> 8) / 100) > 0){
		putc(1,f);
	}
	else
		putc(0,f);
	//putc(((i / 512) >> 8) / 10,f);
	putc(0,f);
	/*putc(((i / 512) % 10000) >> 16,f);
	putc(((i / 512) % 10000) >> 8,f);
	putc(((i / 512) % 10000),f);
	//putc((i / 512) >> 16,f);
	//putc(((i / 512) >> 8) / 100,f);
	int e = (i / 512) >> 8;
	if(e > 1000 && e < 10000){
                putc(3,f);
		putc(((i / 512) >> 8) / 1000
        }
        else if((((i / 512) >> 8) / 100) > 10){
                putc(2,f);
        }
        else if((((i / 512) >> 8) / 100) > 0){
                putc(1,f);
        }
        else
                putc(0,f);
	}*/
	putc(0,f);
	putc(5,f);
	putc(0,f);
	putc(6,f);
	//putc(0,f);
	//putc(6,f);
	putc(0,f);
	putc(0,f);
	putc(0,f);
	//putc(0,f);
	putc(0,f);
	putc(0,f);
	putc(0,f);
	putc(0,f);
	putc(1,f);
	putc(0,f);
	putc(3,f);
	printf("Finished writing superblock\n");
	fclose(f);
}
int main(int argc, char *argv[]){
	if(argc != 2)
		return -1;
	if(mkfszfs(argv[1]) < 0)
		return -1;
	return 0;
}
