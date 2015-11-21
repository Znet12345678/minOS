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
				//kprintf("Found Valid ZFS Signature!\n");
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
		if(buf[i] == 0xAA){
			kprintf("EXEC\n");
			if((buf[(i + 1)] == 0x11) && (buf[(i + 2)] == 0x01) && (buf[(i + 3)] == 0x01)){
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
	int address = 0;
	while(1){
		char *buf = malloc(512);
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
		if(buf[i] == 0xFF && buf[i + 1] == 0x00 && buf[i + 2] == 0xFF)
			ret++;
		i++;
	}

	return ret;
}
int scan_dirs(char *buf){
	int i = 0;
	int ret = 0;
	while(i < 256){
		if(buf[i] == 0xEE && buf[i+1] == 0x01 && buf[i + 2] == 0xFF)
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
				if(buf[i + 1] == 0xFF && buf[i+2] == 0xBB)
					return (i+3);
			else if(buf[i] == filename[i1])
				i1++;
			else
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
		if(buf[i] == 0xFF && buf[i + 1] == 0xFF && buf[i+2] == 0xAA)
			return i;
		i++;
	}
	return -1;
}
char *request_file(char *dir,char *file){
	if(strcmp(dir,"/") == 0){
		//kprintf("Exec\n");
		char ret[1024];
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
				kprintf(">");
				int eof = scan_EOF(buf);
				if(eof != -1){
					while(i < eof){
						kprintf(")");
						kstrcat(ret,&buf[i]);
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
		kprintf("%s\n",ret);
		kprintf("Looked for file %s/%s\n",dir,file);
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
		if(numoffiles == 0 && contf == 1){
			
		}
		ba++;
	}
}
