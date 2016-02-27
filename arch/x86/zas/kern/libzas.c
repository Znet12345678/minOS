#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int chainloader(int blocknum){
	char *buf = malloc(1024);
	ata_read_master(buf,blocknum,0);
	if(buf[0] == 0x0A){
		kprintf("Corrupted file!\n");
	}
	else if(buf[0] == 0x0F){
		kprintf("Found all code within first block\n");
		int *header = malloc(1024);
		kprintf("Reading program header\n");
		for(int i = 0; i < 100; i++){
			header[i] = buf[i];
		}
		kprintf("Read header\n");
		kprintf("Determaning arch\n");
		if(header[1] == 0){
			kprintf("Arch:Unsepcified\n");
			return -1;
		}
		else if(header[1] == 1){
			kprintf("Arch:i386\n");
			kprintf("Determaning executable type");
			if(header[2] == 0){
				kprintf("Exec type:Unspecified/Generic");
			}
			else if(header[2] == 1){
				kprintf("Exec type:zExec v1.0\n");
				kprintf("Determaning size of executable code\n");
				int size = header[3] >> 8 | header[4];
				if(size > 412){
					kprintf("Invalid binary killing!\n");
					return -1;
				}
				kprintf("Executing,brace yourself!\n");
				int inst = 100;
				int si[100] = {-1};
				unsigned int ui[100] = {0x0F};
				while(inst < 512){
					if(buf[inst] == 0x0A){
						kprintf("%c",buf[++i]);
					}
					else if(buf[inst] == 0x0B)[
						int v = 0;
						while(si[v] != -1){
							v++;
						}
						if(v == 100){
							kprintf("Execption:Too many variables allocated in program,killing\n");
							return -1;
						}
						si[v] = buf[++i];
					}
					else if(buf[inst] == 0x0C){
						int v = 0;
						while(si[v] != -1){
							v++;
						}
						si[v - 1] = -1;
					}
					
					else if(buf[inst] == 0x0E){
						
					}
				}
			}
			else if(header[2] == 2){
				kprintf("Exec type:zBin\n");
			}
		}
		else if(header[1] == 2){
			kprintf("Arch:x86_64\n");
			kprintf("Cannot execute killing process\n");
			return -1;
		}
		else if(header[1] == 3){
			kprintf("Arch:arm\n");
			kprintf("Killing\n");
			return -1;
		}
		else if(header[1] == 4){
			kprintf("Arch:Generic\n");
			kprintf("WIP\n");
			return 0;
		}
		else{
			kprintf("Not valid binary!\n");
			return -1;
		}
	}
	else{
		kprintf("Program allocates more than 1 block");
	}
}
