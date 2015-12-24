/*
*ZFS 
*Public domain as of December 24 2015
*You can use in your own projects
*/
#include "zfs.h"
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
int scan_for_sig(char *buf){
	int i = 0;
	while(i < 1024){
		if(buf[i] == 0x26){
			//kprintf("Started\n");
			int i1 = 0;
			if((buf[(i + 1)] == 0x01) && (buf[(i + 2)] == 0x03) && (buf[(i + 3)] == 0x08)){
				kprintf("[SIG_SCAN]:Found Valid ZFS Signature!\n");
				return (i+1);
			}
		}
		i++;
	}
	return 0;
}
int scan_for_esig(char *buf){
	int i = 0;
	while(i < 1024){
		//kprintf("%c",buf[i]);
		if(buf[i] == 0x23){
			//kprintf("EXEC\n");
			if((buf[(i + 1)] == 0x11) && (buf[(i + 2)] == 0x11) && (buf[(i + 3)] == 0x11)){
				kprintf("[ESIG_SCAN]:Found Full ZFS Disk Partition\n");
				return (i+1);
			}
		}
		i++;
	}
	return 0;
}
int zfs_scan(int force){
	int i = 0;
	//char buf[256];
	uint32_t address = 0x00;
	//while(i < 256){
	//	buf[i] = 0;
	//	i++;
		
	//}
	i = 0;
	int b;
	int ret = 0;
	uint16_t drive;// = ddrive();
	if(force == 1)
		drive = 0x02;
	else
		drive = 0x00;
	while(1){
		//kprintf("*");
		char *buf = malloc(1024);
		int im = 0;
		//while(im < 256){
			//kprintf("%c",buf[i]);
			//im++;
		//}
		if(ata_read_master(buf,i,drive) == -1)
			return -1;
		//kprintf(".");
		//kprintf("%s\n",buf);
		int i2 = 0;
		/*while(i2 < 256){
			//kprintf("%c",buf[i2]);
			i2++;
		}*/
		//panic();
		//kprintf("e\n");
	 	b = scan_for_sig(buf);
		if(b != 0)
			return ret;
		//kprintf("!");
		int i1 = 0;
		//while(i < 256){
		//	buf[i] = 0;
		//	i++;
		//}
		ret++;
		//buf = malloc(256);
		i++;
	}
//	//kprintf("_Exec\n");
	return i;	

}
int zfs_scanend(uint16_t drive,int offset){
	//kprintf("Exec\n");
	int i = offset;
	int b = 0;
//	char buf[256];
	//kprintf("exec\n");
	int address = offset;
	while(1){
		char *buf = malloc(1024);
		//kprintf("%s\n",buf);
		int i1 = 0;
		//while(i1 < 256){
		//	buf[i1] = 0;
		//	i1++;
		///}
		//kprintf("!");
		if(ata_read_master(buf,i,drive) == -1)
			return -1;
		//kprintf(".");
		b = scan_for_esig(buf);
		if(b != 0)
			return i;
		i1 = 0;
		//while(i1 < 256){
		//	buf[i1] = 0;
		//	i1++;
		//}
		address++;
		i++;
	}
	return address;
}
int scan_files(char *buf){
	int i = 0;
	int ret = 0;
	while(i < 256){
		if(buf[i] == 0x31 && buf[i + 1] == 0x32 && buf[i + 2] == 0x33)
			ret++;
		i++;
	}

	return ret;
}
int scan_dirs(char *buf){
	int i = 0;
	int ret = 0;
	while(i < 256){
		if(buf[i] == 0x03 && buf[i+1] == 0x01 && buf[i + 2] == 0x03)
			ret++;
		i++;
	}
	return ret;
}
int test_for_file(char *filename,char *buf){
	if(scan_files(buf) > 0){
		int i = 0;
		int i1 = 0;
		int ret = 0;
		while(i < 256){
			//kprintf("%c",buf[i]);
			if(i1 == strlen(filename))
				//if(buf[i + 1] == 0xFF && buf[i+2] == 0xBB)
					return (i+3);
			else if(buf[i] == filename[i1]){
				//kprintf(".");
				i1++;
			}
			else if(i1 > 0)
				i1 = 0;
			i++;
		}
		return -1;
	}
	else
		return -1;
}
int scan_EOF(char *buf){
	int i = 0;
	while(i < 256){
		if(buf[i] == 0x03 && buf[i + 1] == 0x03 && buf[i+2] == 0x03)
			return i ;
		i++;
	}
	return -1;
}
char *request_file(char *dir,char *file){
	if(strcmp(dir,"/") == 0){
		//kprintf("Exec\n");
		char *ret = malloc(10240);
		//kprintf("1\n");
		int ba = zfs_scan(0);
		kprintf("[REQUEST_FILE]:Found valid ZFS sig\n");
		//kprintf("2\n");
		int cont = 0;
		char buf[10240];
		//int be = zfs_scanend(0x00,ba);
		int be = zfs_scanend(0x00,ba);
		kprintf("[REQUEST_FILE]:Found End Boundaries\n");
		if(be < 0)
			panic();
		if(ba < 0)
			panic();
		//if(be > 512)
		//	panic();
		//kprintf("3\n");
		while(ba < be){
			///char *buf = malloc(1024);
			//kprintf("!");
			if(ata_read_master(buf,ba,0x00) < 0)
				panic();
			//kprintf(".");
			int bi = 0;
			/*while(bi < 256){
				//kprintf("%c",buf[bi]);
				bi++;
			}*/
			if(test_for_file(file,buf) > -1){
				int i = test_for_file(file,buf);
				//kprintf(">");
				int eof = scan_EOF(buf);
				///if(eof == -1)
				//	panic();
				if(eof != -1){
					int j = 0;
					while(i < (eof)){
						//kprintf("%c",buf[i]);
						kstrcat(ret,&buf[i]);
						//ret[j] = buf[i];
						j++;
						i++;
					}
				}
				else{
					while(i < (strlen(buf) - i)){
						kstrcat(ret,&buf[i]);
						i++;
					}
					cont = 1;
				}
			}
			else if(cont == 1){
				int i = 0;
				if(scan_EOF(buf) != -1){
					while(i < scan_EOF(buf)){
						kstrcat(ret,&buf[i]);
						i++;
					}
					cont = 0;
				}
				else{
					while(i < (strlen(buf) - i)){
						kstrcat(ret,&buf[i]);
						i++;
					}
				}
			}
			//kprintf(".");
			ba++;
		}
		//kprintf("%s\n",ret);
		kprintf("Looked for file %s%s\n",dir,file);
		return ret;
	}
}
zfs_mount(int offset,int end){
	int ba = zfs_scan(0);
	int be = zfs_scanend(0,ba);
	int contf = 0 ;
	while(ba < be){
		char *buf = malloc(1024);
		if(ata_read_master(buf,ba,0x00) == -1){
			kprintf("[ERR]Couldn't mount FILESYSTEMS\n");
			panic();
		}
		int numoffiles = scan_files(buf);
		int numofdirs = scan_dirs(buf);
		ba++;
	}
}
char *dirs(char *buf){
	int i = 0;
	char *ret = malloc(1024);
	while(i < strlen(buf)){
		if(buf[i] == 0x08 && buf[i + 1] == 'D' && buf[i + 2] == 0x04 && buf[i + 3] == 'I' && buf[i + 4] == 'R'){
			int i1 = i;
			while(i1 < (strlen(buf) - i)){
				if(buf[i1] == 'R' && buf[i1 + 1] == 'I' && buf[i1 + 2] == 0x04 && buf[i1 + 3] == 'D' && buf[i1 + 4] == 0x08)
					break;
				i1++;
			}
			while(i < i1){
				kstrcat(ret,&buf[i]);
				i++;
			}
			char br = 0x4F;
			kstrcat(ret,&br);
			i1 = 0;
			i+=4;
			continue;
		}
		i++;
	}
	return ret;
}
int cont_file(char *filename,char *buf){
	int i = 0;
	int i1 = 0;
	int k = 0;
	int j = 0;
	while(i < 256){
		//int i1 = 0;
	//	kprintf(".");
		while(j < ((strlen(filename)))){
			//kprintf(".");
			if(i1 == (strlen(filename))){
				//kprintf("(:");
				return (k);
			}
			else if(buf[k] == 0x06 && buf[k + 1] == filename[i1]){
				//kprintf("EXEC\n");
				i1++;
				k+=2;
				continue;
			}
			else{
				i1 = 0;
				break;
			}
			//k+=2;
			//k+=2;
			j++;
		}
		k = i;
		j = 0;
		//if(i1 > 0)
			//kprintf("MEH\n");
		if(i1 == (strlen(filename)))
			return (i + i1);
		i++;
	}
	return 0;
}
int read(char *filename,char *buf){
	int i = 0;
	int i1 = 0;
	int read = 0;
	int cont = 0;
	int k = 0;
	int start = zfs_scan(0);
	char *buf1 = malloc(10240);
	int end = zfs_scanend(0x00,start);
	while(start < end){
		char *tmpbuf = malloc(1024);
		if(ata_read_master(tmpbuf,start,0x00) < 0){
			kprintf("[READ] Failed to read file\n");
			return -1;
		}
		if(cont_file(filename,tmpbuf) > 0|| cont == 1){
			int j = 0;
			if(cont != 1)
				j = cont_file(filename,tmpbuf);
			else
				j = 0;
			if(j < 1 && cont != 1){
				kprintf("[ZFS_READ]I/O Error\n");
				return -1;
			}
			//int k = 0;
			int m = -1;
			while(j < 256){
				if(tmpbuf[j] == 0x06 && tmpbuf[j+1] == 0x07 && tmpbuf[j+2] == 0x08){
					m = (j);
					break;
				}
				j++;
			}
			if(m == -1)
				m = 256;
			if(cont != 1)
				j = cont_file(filename,tmpbuf);
			else
				j = 0;
			k = 0;
			int l = 0;
			while(l < 256){
				buf[l] = 0;
				l++;
			}
			while(j < m){
				//kstrcat(buf1,&tmpbuf[j]);
				buf[k - 1] = tmpbuf[j];
				//buf[k] = tmpbuf[j];
				//kprintf("%c",tmpbuf[j]);
				read++;
				k++;
				//kprintf(".");
				//kprintf("!");
				j++;
			}
			if(j == (256 - cont_file(filename,tmpbuf))){
				cont = 1;
				//kprintf("Exec\n");
			}
			else
				break;
		}
		else
			break;
		start++;
	}
	//buf = buf1;
	//kprintf("%s\n",buf1);
	return read;
}
void mount(int offset,int end){
	int i = offset;
	char *dir = "/";
	char *set = malloc(1024);
	while(i < end){
		char *buf = malloc(1024);
		if(ata_read_master(buf,i,0x00) == -1){
			kprintf("[ERR]Couldn't mount FS:I/O Error\n");
			panic();
		}
		if(strcmp(dir,"/") == 0){
			
		}
	}
}
