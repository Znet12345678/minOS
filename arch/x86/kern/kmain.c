/*
* (C) 2015 Zachary James Schlotman
* Kernel Main
* minOS_kern
*/
#include <stdio.h>
#include "module.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <kernel/tty.h>
#include <kernel/vga.h>
#include "../mem/mm.h"
#include "../lib/panic.h"
#include "../fs/WIP/fat/fat32.h"
#include "../fs/WIP/inffs/inffs.h"
typedef struct __attribute__ ((packed)) {
    unsigned short di, si, bp, sp, bx, dx, cx, ax;
    unsigned short gs, fs, es, ds, eflags;
} regs16_t;
//#include "../fs/broken/zfs/zfs.h"
#include "../fs/broken/zfs/zfs.h"
#include "../fs/broken/ext2/ext2.h"
//#include "../fs/fat32/dosfs.h"
#include "../fs/WIP/minfs/minfs.h"
unsigned long __strlen(const char *s1){
	int len = 0;
	while(s1[len] != 0)
		len++;
	return len;
}
void dev_kmain(){
	debug("KERNEL","hang");
	while(1) { };
}
void test_init(){
	kprintf("{[TESTM-INIT] Module Successfully loaded}\n");
	_kill();
}
void test_main(){
	kprintf("{[TESTM-MAIN] Module Successfully loaded}\n");
	_kill();
}
int char2int(char c){
	if(c == 'a')
		return 0;
	else if(c == 'b')
		return 1;
	else if(c == 'c')
		return 2;
	else if(c == 'd')
		return 3;
	else if(c == 'e')
		return 4;
     else if(c == 'f')
    return 5;

     else if(c == 'g')
    return 6;

     else if(c == 'h')
    return 7;

     else if(c == 'i')
    return 8;

     else if(c == 'j')
    return 9;

     else if(c == 'k')
    return 10;

     else if(c == 'l')
    return 11;

     else if(c == 'm')
    return 12;

     else if(c == 'n')
    return 13;

     else if(c == 'o')
    return 14;

     else if(c == 'p')
    return 15;

     else if(c == 'q')
    return 16;

     else if(c == 'r')
    return 17;

     else if(c == 's')
    return 18;

     else if(c == 't')
    return 19;

     else if(c == 'u')
    return 20;

     else if(c == 'v')
    return 21;

     else if(c == 'w')
    return 22;

     else if(c == 'x')
    return 23;

     else if(c == 'y')
    return 24;

     else if(c == 'z')
    return 25;
	else if(c == '1')
		return 26;
	else if(c == '2')
    return 27;

	else if(c == '3')
    return 28;

	else if(c == '4')
    return 29;

	else if(c == '5')
    return 30;

	else if(c == '6')
    return 31;

	else if(c == '7')
    return 32;

	else if(c == '8')
    return 33;

	else if(c == '9')
    return 34;

	else if(c == '0')
    return 35;
	else
		return -1;


}
int int2str(int i){
	int c = 0;
	char *buf = malloc(80);
	int n;
	int t;
	int inc;
	int bi =  i;
	while(bi > 0){
		t++;
		bi/=10;
	}
	while(i > 0){
		n = (i % 10);
		if(n == 0)
			buf[t - inc] = '0';
		else if(n == 1)
			buf[t - inc] = '1';
		else if(n == 2)
			buf[t - inc] = '2';
		else if(n == 3)
			buf[t - inc] = '3';
		else if(n == 4)
			buf[t - inc] = '4';
		else if(n == 5)
			buf[t - inc] = '5';
		else if(n == 6)
			buf[t - inc] = '6';
		else if(n == 7)
			buf[t - inc] = '7';
		else if(n == 8)
			buf[t - inc] = '8';
		else if(n == 9)
			buf[t - inc] = '9';
		inc++;	
		i/=10;
	}
}
int nstrcmp(const char *s1,const char *s2){
	int i = 0;
	if(strlen(s1) != strlen(s2))
		return -2;
	while(i < strlen(s1)){
		if(s1[i] != s2[i])
			return (i+1);
		i++;
	}
	return 0;
}
void dump_args(char *reason){	
	#ifdef DEBUG
	kprintf("Drive Selection:");
	int drive = -1;
	if(drive == 0x00)
		kprintf("0/PRIMARY\n");
	else if(drive == 0x01)
		kprintf("0/SECONDARY\n");
	else
		kprintf("Unkown\n");
	kprintf("I/O Port:");
	if(drive == 0x00)
		kprintf("0x1FX\n");
	else if(drive == 0x01)
		kprintf("0x17X\n");
	else
		kprintf("Unkown\n");
	//kprintf("ZFS Offset\n");
	//int offset = zfs_scan(drive);
	kprintf("File System:\n");
	kprintf("Not yet defined\n");
	kprintf("Memory allocator:Built-In\n");
	kprintf("Modules: \n");
	kprintf("Not Defined\n");
	kprintf("minOS kernel is in alpha\n");
	kprintf("Reason for panic: %s\n",reason);
	#endif
}

int _verbose_kmain(char *arg){
	debug("KERNEL","Version 0.3-alpha");
	debug("KERNEL","Verbose mode");
	//debug("KERNEL","Testing hard drive");
	int io = 0x1F0;
	debug("KERNEL",arg);
	debug("KERNEL","(c) 2016 Zachary James Schlotman");
	debug("KERNEL","Please reboot with no boot arguments");
	debug("KERNEL","verbose_panic()");
	verbose_panic(arg,"KERNEL","_verbose_kmain");
}
void kernel_main_safe(){
	debug("KERNEL","Version 0.3-alpha");
	kprintf("**************SAFE BOOT**************\n");
	debug("KERNEL","Hang");
	while(1){};
}
int release_kmain(){
	t_init();
	debug("KERNEL","Version 0.3-alpha");
	kprintf("******************************RELEASE BUILD******************************\n");
	debug("KERNEL","Early kernel,setting things up");
	debug("KERNEL","Resetting Drives");
 /*   outb(0x1F0,0);
    outb(0x1F1,0);
	outb(0x1F2,0);
	outb(0x1F3,0);
	outb(0x1F4,0);
	outb(0x1F5,0);
    outb(0x1F6,0);
    outb(0x1F7,0);*/
	char *bufs[1024] = {malloc(1024)};
	char *buf = malloc(1024);
	int a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z;
	//debug("KERNEL","Using primary I/O port\n");
	int io = 0x1F0;
	//debug("KERNEL","Setting up file systems");
	//ata_read_master(buf,0,0);
	//struct minfs_superblock *superblk = parse_superblk(0,);
	//mount("/",0x00);
	//debug("KERNEL","Done");
	/*struct bpb boots;
	boots.jmp = buf[0] << 16 | buf[1] << 8 | buf[2];
	boots.bytespersector = buf[11] << 8 | buf[12];
	boots.sectorspercluster = buf[13];
	boots.reserved  = buf[14] << 8 | buf[15];
	boots.numoffat = buf[16];
	boots.numofdirent = buf[17] << 8 | buf[18];
	boots.totsec = buf[19] << 8 | buf[20];
	boots.mdt = buf[21];
	boots.sectorspertrack = buf[24] << 8 | buf[25];
	boots.heads = buf[26] << 8 | buf[27];
	boots.hiddensectors = buf[28] << 32 | buf[29] << 16 | buf[30] << 8 | buf[31];
	char *ehg = malloc(1024);
	ata_read_master(ehg,boots.hiddensectors,0);
	//while(1){ }
	boots.largeammountofsectoronmedia = 0;
	struct Fat32_ExtendedBootRecord ebr;
	ebr.SectorsPerFat = buf[36] << 32 | buf[37] << 16 | buf[38] << 8 | buf[39];
	ebr.flags =buf[40] << 8 | buf[41];
	ebr.cluster_number = buf[44] << 32 | buf[45] << 16 | buf[46] << 8 | buf[47];
	ebr.second_number = buf[48] << 8 | buf[49];
	ebr.backup = buf[50] << 8 | buf[51];
	ebr.DriveNum = buf[52];
	ebr.Signature = buf[53];
	char *fat = malloc(1024);
	fat32_mount(boots,ebr,fat);*/
	//debug("KERNEL","INITIALIZING GUI BRASE YOURSELVES");
	//initgui();
	//regs16_t regs;
	//regs.ax = 0x0013;
	//int32(0x10,&regs);
	//init_gui();
	//kprintf("Initializing memory management\n");
	//kprintf("Writing file to ramdisk\n");
	//const char *wbuf = "Welcome to minOS\n";
	//write_rd_file("Welcome",wbuf,strlen(wbuf),0x00100000);
	//struct rd_file *welcome_f = read_rd_file_full("Welcome",0x00100000);
	//kprintf("Welcome says %s\n",welcome_f->raw);
	//t_init();
	if(!(__IS_INFFS())){
		kprintf("Formating drive");
		__INFFS_MKFS_FULLDISK();
		kprintf("\n");
		kprintf("Press enter to restart\n");
		kgets();
		t_init();
		release_kmain();
	}
	debug("INFFS","Opening test file");

	struct __INFFS_FILE tmp;
	struct __INFFS_FILE *f_i = __INFFS_FULLDISK_FS_FOPEN("/test",__INFFS_FOPP_WRITE,&tmp);
	//while(1)
	//	;
	if(!(f_i)){
		kprintf("Error opening file for writing!\n");
		panic();
	}

	debug("INFFS","Writing test file");
	char tbuf[1024] = {'T','e','s','t'};
	if(__INFFS_FULLDISK_FS_FWRITE(&tmp,tbuf,strlen(tbuf)) < 0){
		kprintf("Error writing file!\n");
		panic();
	}
	debug("KERNEL","Done");
	while(1){
		kprintf("\n");
		kprintf("[nobody@minos_kernel]");
		char *s = malloc(1024);
		s = kgets();
		//kprintf("\n%s.\n",s);
		shell_process(s);
		//kprintf("\n%s\n",s);
	}
	//panic();
}
int verbose_kmain(char *arg){
	//t_init();
	int sel = 0;
	t_init();
	/*for(int i = 0; i < 240;i++){
		putcolour(COLOUR_BLUE);
	}
	for(int i = 0;i < 20;i++){
		putcolour(COLOUR_BLUE);
		//kprintf("->Boot")
	}
	kprintf("->Boot");
	for(int i = 0; i < 74;i++){
		putcolour(COLOUR_BLUE);
	}
	kprintf(" hang");
	for(int i = 0;i < 54;i++)
		putcolour(COLOUR_BLUE);
	for(int i = 0;i < (80*6);i++)
		putcolour(COLOUR_BLUE);
	char c = inportb(0x64);
	while(1){
	a1:while(inportb(0x64) == c) { };
	c = inportb(0x60);
	if(c == 0x1C)
		break;
	if(c != 0x48 && c != 0x50 && c != 0x1C)
		goto a1;

	a2:if(c != 0x1C){
		t_init();
		if(sel == 0)
			sel = 1;
		else
			sel = 0;
		if(sel == 1){
			for(int i = 0; i < 260;i++){
				putcolour(COLOUR_BLUE);
			}
			kprintf("  Boot");
			for(int i = 0; i < 74;i++)
				putcolour(COLOUR_BLUE);
			kprintf("->hang");
			for(int i = 0; i < (54 + (80 * 6));i++){
				putcolour(COLOUR_BLUE);
			}
		}
		else{
			t_init();
                	if(sel == 0)
                	        sel = 1;
                	else
                      	 	 sel = 0;
                	if(sel == 1){
                        	for(int i = 0; i < 260;i++){
                        	        putcolour(COLOUR_BLUE);
                	        }
                	        kprintf("->Boot");
            	            for(int i = 0; i < 74;i++)
                	                putcolour(COLOUR_BLUE);
        	                kprintf("  hang");
	                        for(int i = 0; i < (54 + (80 * 6));i++){
                	                putcolour(COLOUR_BLUE);
	                        }
        	        }
		
		}
	}
	}
	if(sel == 1){
		kprintf("Hanging\n");
		while(1) { };
	}*/
	debug("KERNEL","Version 0.3-alpha");
	kprintf("(c) 2015 Zachary James Schlotman\n");
	//int i = atoi("4");
	//if(i == 4)
	//	kprintf("Yeah!\n");
	//i = atoi("123");
	//if(i == 123)
	//	kprintf("YEAH!\n");
	//ide_init(0x1F0,0x3f6,0x170,0x376,0x000);
	int io = 0x1F0;
	char *modules[MAX_MODULES];
     outb(io + 0x02,0);
     outb(io + 0x03,0);
     outb(io + 0x04,0);
     outb(io + 0x05,0);
	//ide_init(0x1F0,0x3f6,0x170,0x376,0x000);
	debug("KERNEL",arg);
	kprintf("minOS libzOS kernel\n");
	//debug("DRIVERS","init");
	//kprintf("[WRN]:Not implemented\n");
	//kprintf("Searching for usable disks\n");
	debug("DSKSCAN","*Scanning Primary");
	int i = 0;
	while(i < 4){
		inb(io + 0x0C);
		i++;
	}
	i = 0;
	while(i < 4){
		uint8_t status = inb(io + 0x07);
		if(!(status & 0x80)){
			debug("DSKSCAN","Stage 1 Success");
			break;
		}
		//kprintf("	[WRN]Attempt failed for Primary drive\n");
		i++;
	}
	if(i < 4){
		i = 0;
		int err = -1;
		while(1){
			uint8_t status = inb(0x1F7);
			if(status & 0x01){
				debug("DSKSCAN","ERR");
				kprintf("Primary Drive error moving on\n");
				err = 1;
				break;
			}
			if(1){
				debug("DSKSCAN_PRIMARY","SUCC");
				kprintf("Primary drive in good shape!\n");
				err = 0;
				break;
			}
		//	kprintf("[WRN] Primary drive failed a test\n");
			i++;
		}
		if(err == 0){
			kprintf("Using Primary I/O address\n");
			io = 0x1F0;
		}
		else{
			kprintf("Trying Secondary I/O port\n");
			io = 0x170;
			i = 0;
			while(i < 4){
				inb(io + 0x0C);
				i++;
			}
			i = 0;
			while(i < 4){
				uint8_t status = inb(io + 0x07);
				if(!(status & 0x80))
					break;
		//		kprintf(" [WRN]Attempt failed for secondary drive\n");
				i++;
			}
			if(i < 4){
				i = 0;
				while(i < 400){
					uint8_t status = inb(io + 0x07);
					if(status & 0x01){
						debug("DSKSCAN","ERR");
						kprintf(" [ERR]I/O Error on secondary drive!\n");
						//kprintf("Panicing\n");
						goto a;
						//panic();
					}
					if(1)
						break;
					i++;
				}
				if(i == 400){
					//debug("DSKSCAN","ERR");
		//			kprintf(" [ERR]No usable drives found!\n");
					//debug("KERNEL","PANIC");
					b:io = 0x3F0;
					i = 0;
					while(i < 4){
						inb(io + 0x0C);
						i++;
					}
					i = 0;
					while(i < 4){
						uint8_t status = inb(io + 0x07);
						if(!(status & 0x80))
							break;
						i++;
					}
					if(i == 4){
						debug("DSKSCAN","ERR");
						panic();
					}
					i = 0;
					while(i < 4){
						uint8_t status = inb(io + 0x07);
						if(status & 0x01)
							__panic("I/O ERROR");
						i++;
					}


				}
				else{
		//			kprintf("Secondary drive is working!\n");
					io = 0x170;
				}
			}
			else{
				debug("DSKSCAN","ERR");
		//		kprintf(" [ERR] No usable drives found!\n");
				//debug("KERNEL","PANIC");
				goto b;
				//__panic("No Usable Drives");

			}
		}
	}
	else{
		kprintf(" [WRN] Problem with primary ATA device\n");
		int i = 0;
		io = 0x170;
		while(i < 4){
			inb(io + 0x0C);
			i++;
		}
		i = 0;
		while(i < 4){
			uint8_t status = inb(io + 0x07);
			if(!(status & 0x80))
				break;
		//	kprintf("     [WRN]Attempt failed for secondary drive\n");
			i++;
		}
		i = 0;
		while(i < 4){
			uint8_t status = inb(io + 0x07);
			if(status & 0x01){
				debug("DSKSCAN","ERR");
		//		kprintf("     [ERR] I/O Error on secondary drive\n");
				//panic();
				goto a;
			}
			if(1)
				break;
			i++;
		}
		if(i == 4){
		//	kprintf(" [WRN] secondary Drive doesn't work\n");
		//	kprintf(" [INF] Searching port 0x3F6\n");
			io = 0x3F6;
			i = 0;
			while(i < 4){
				inb(io + 0x07);
				i++;
			}
			i = 0;
			while(i < 4){
				uint8_t status = inb(io + 0x07);
				if(!(status & 0x80))
					break;
				kprintf(" [WRN] IDE FAILED TEST\n");
				i++;
			}
			if(i == 4){
				a:kprintf(" [WRN] 0x3F6 Unusable searching final address\n");
				io = 0x376;
				i = 0;
				while(i < 4){
					inb(io + 0x0C);
					i++;
				}
				i  =0;
				while(i < 4){
					uint8_t stat = inb(io + 0x07);
					if(!(stat & 0x80))
						break;
					//kprintf(" [WRN] IDE FAILED TEST\n");
					i++;
				}
				if(i == 4){
					debug("DSKSCAN","ERR");
					kprintf(" [ERR]No usable drives found!\n");
					goto b;
					//debug("KERNEL","PANIC");
					//__panic("No Usable Drives\n");
				}
				i = 0;
				while(i < 4){
					int stat = inb(io + 0x07);
					if(stat & 0x01){
						kprintf("DSKSCAN","ERR");
						kprintf(" [ERR] I/O Error\n");
						//debug("KERNEL","I/O Error");
						//__panic("Fatal I/O Error");
						goto b;
					}
					i++;
				}

			}
			else{
				kprintf(" [INF] 0x3F6 Passed 1st stage\n");
				i = 0;
				int err = 0;
				while(i < 4){
					uint8_t stat = inb(io + 0x07);
					if(stat & 0x01){
						//kprintf(" [WRN] I/O Error\n");
						err = 1;
						break;
					}
					i++;
				}
				if(err == 1){
					kprintf(" [WRN] I/O Error\n");
					kprintf(" [INF] Using port 0x376\n");
					io = 0x376;
					i = 0;
					while(i < 4){
						inb(io + 0x0C);
						i++;
					}
					i = 0;
					while(i < 4){
						uint8_t stat = inb(io + 0x07);
						if(!(stat & 0x80))
							break;
						kprintf(" [WRN] I/O Not ready!\n");
						i++;
					}
					if(i == 4)
						goto b;
						//__panic("No drives found\n");
					i = 0;
					while(i < 4){
						uint8_t stat = inb(io + 0x7);
						if(stat & 0x01){
							kprintf(" [ERR] I/O Error\n");
							goto b;
						//	debug("KERNEL","I/O ERROR");
						//	__panic("I/O Error");
						}
						i++;
					}
				}
				
			}
		}
		else{
			kprintf(" Secondary Drive works!\n");
			io = 0x170;
		}
	}
	//debug("Sleeping...");
	//for(int i = 0; i < 400000;i++){

	//}	
	//kprintf("Loading disk partitions\n");
	//panic();
	int offset = 0;
	//int offset = zfs_scan(0);
	if(offset  == -1){
		kprintf("[NFE]I/O ERROR on main I/O Port\n");
		int offset = zfs_scan(1);
		if(offset == -1){
			kprintf("[FER]I/O ERROR on secondar I/O Port\n");
			panic();
		}
	}
	//kprintf("Mounting filesystem\n");
	//kprintf("Done\n");
//	char *s = malloc(10240);
	struct ext2_superblock *sb;
	//sb = parse_sblk(0);
	//kstrcat(s,request_file("/","hi"));
	//kprintf("%s\n",s);
//	kprintf("%s",request_file("/","hi"));
	//kprintf("Mounting File Systems\n");
	//if(read("/init",s) < 1)
	//	panic();
	//kprintf("%s\n",s);
	//if(sb->ninode == 65536)
	//	kprintf("!");
//	kprintf("%d\n",sb->ninode);
//	kprintf("Done\n");
	//struct block_group *bg;
	//bg = read_bg();
	//struct inode *in = read_inode(2,sb,bg);
	//kstrcat(s,request_file("/","init"));
	//kprintf("%s\n",s);
	/*PVOLINFO volinfo;
	uint8_t *buf = malloc(1024);
	uint8_t *sec = malloc(1024);
	uint32_t ss = DFS_GetPtnStart(512,buf,0,NULL,NULL,sec);
	if(ss == 0xffffffff)
		panic();
	uint8_t *buf1 = malloc(1024);
	DFS_GetVolInfo(512,buf,ss,volinfo);
	PFILEINFO fileinfo;
	if(DFS_OpenFile(volinfo,"/test",DFS_READ,buf1,fileinfo)!= DFS_OK)
		panic();
	char *buffer = malloc(1024);
	DFS_ReadFile(fileinfo,NULL,buffer,sec,5);*/
	//kprintf("[START] Mounting FileSystems\n");
	debug("KERNEL","Parsing Superblock");
	kprintf("	*Parsing Superblock\n");
	//struct minfs_superblock *superblk = parse_superblk(0,NULL);
	debug("KERNEL","mount_p1");
	char *buffer = malloc(102400);
//	mount_p1(buffer,0,superblk);
//	//struct minfs_superblock *superblk = parse_superblk(0);
	//if(superblk->blocksize != 512)
	//	panic();
	//kprintf("	*Reading Initial inode\n");
	//struct inode *_inode;
	//_inode = read_inode(0,superblk->starting_inode,superblk);
	//kprintf("	*Reading Initial Block\n");
	//struct block *_block;
	//_block = read_blk(0,superblk->starting_block,_inode,superblk);
	//kprintf("[FINALIZING] Mounting FileSystems\n");
	//kprintf("[KERNEL] Initializing modules\n");
	//mod_init(modules);
	//kprintf("[KERNEL] Done initializing modules\n");
	//kprintf("[KERNEL] regerstring test module\n");
	int pos = 0;
	//register_module("test",pos);
	//kprintf("[FATAL ERROR]UNDEFINED!Nothing to do.\nDropping into panic shell\n");
	//call_module("test",modules);
	kprintf("Done\n");
	kprintf("Nothing to do\n");
	debug("KERNEL","Mounting File Systems");
//	if(superblk->blocksize != 512)
//		panic();
	//	kprintf("Aw\n");
	char *buf = malloc(102400);
//	mount_p1(buf,0x00,superblk);
	while(1){ }
	//__panic("Nothing to do");
	//panic("Nothing to do");
//	panic();
}
int graphical_kmain(char *arg){
	t_init();
	/*kprintf("   __________________\n");
	kprintf("      /\n");
	kprintf("    /\n");
	kprintf("  		      /\n");
	kprintf(" 		    /\n");
	kprintf(" 		   /\n");
	kprintf("		  /\n");
	kprintf("		 /\n");
	kprintf("		      /\n");
	kprintf("		     /\n");
	kprintf("		    /\n");
	kprintf("		      /\n");
	kprintf("		     /\n");
	kprintf("		    /\n");
	kprintf("		   /\n");
	kprintf("		  /\n");
	kprintf("		 /\n");*/
	/*kprintf("/\n");
	kprintf("  /\n");
	kprintf(" /\n");
	kprintf("/\n");
	kprintf("  /\n");
	kprintf(" /\n");
	kprintf("/\n");*/
	kprintf("   __________________\n");
     kprintf("      /\n");
     kprintf("    /\n");
     kprintf("      /\n");
     kprintf("     /\n");
     kprintf("    /\n");
     kprintf("         /\n");
     kprintf("        /\n");
     kprintf("       /\n");
     kprintf("      /\n");
     kprintf("        /\n");
     kprintf("       /\n");
     kprintf("      /\n");
     kprintf("     /\n");
     kprintf("    /\n");
     kprintf("   /\n");
     kprintf("        /\n");
	kprintf("       _________________\n");
	kprintf("Begining startup\n");
	kprintf(" =");
	int port = 0x1F0;
	/*while(1){
		int stat = inb(port + 0x07);
		if(!(stat & 0x01) && !(stat & 0x80) && (stat !=0))
			break;
		port++;
	}*/
	int stat = inb(port + 0x07);
	if((stat & 0x01) || (stat & 0x80))
		port = 0x170;
	 stat = inb(port + 0x07);
	if((stat & 0x01) || (stat & 0x80))
		port = 1;
	if(port != 1)
		kprintf("=");
	else
		kprintf("!");
	int sig = zfs_scan(0);
	kprintf("=======================================================");
	//kprintf("%c\n",port);
	//.if(port < 0x170)
	//	kprintf("aw\n");
	//i/f(port == 0x1F7)
	//	kprintf("==\n");
	//else if(port < 0x1F7)
	//	kprintf("<\n");
	//else
	//	kprintf(">\n");
	kprintf("=");
	//kprintf("		______________\n");
}
void kernel_main(int a,char *b){
	if(strcmp(b,"s") == 0)
		zsh();
	t_init();
	kprintf("Detecting Hard Drives\n");
	ide_init(0x1F0,0x3f6,0x170,0x376,0x000);
	uint16_t drive;
	if(strcmp(b,"fa") == 0)
		drive = 0x02;
	else
		drive = ddrive();
	kprintf("Detecting Keyboards\n");
	outb(0x60,0xF2);
	kprintf("Initializing Devices\n");
	outb(0x60,0xED);
	outb(0x60,0xEE);
	int io = 0x4138;
	outb(io + 0x02,0);
	outb(io + 0x03,0);
	outb(io + 0x04,0);
	outb(io + 0x05,0);
	//outb(0x1F0 + 0x07,0xEC);
	kprintf("Sent identify to Primary IDE Device\n");
	//uint8_t stat = inportb(0x1F0 + 0x07);
	kprintf("Allocating memory for variables\n");
	char cmdbuf;
	kprintf("Testing Disk Drivers\n");
	char buf[80];
	//ata_read_master(buf,0,drive);
	//kprintf("%s\n",buf);
	kprintf("Scanning disk for ZosFS Signature");
	int offset;
	if(strcmp(b,"fa") == 0)
		offset = zfs_scan(1);
	else
		offset = zfs_scan(0);
	kprintf("Scanning for end of partition\n");
	//int endoffset = zfs_scanend(0);
	//kprintf("%s\n",request_file("/","hi"));
	//panic();
	kprintf("Mounting Root FileSystem\n");
//	zfs_mount(offset,endoffset);
	kprintf("Passing control to init Script\n");
	exec_script("/init.initsh");
}
void kernel_main_old(int a,char *b){
	t_init();
	kprintf("Loading early kernel.\n");
	ide_init(0x1F0, 0x3F6, 0x170, 0x376, 0x000);
	int i = 0;
	int commandnum = 4;
	//char *mtest = malloc(80);
	//kstrcpy(mtest,"test");
	//kprintf("%s\n",mtest);
	char *commands[] = {"ls","help","memlist","echo"};
	kprintf("\nSimple kernel x86\n");
	kprintf("Arguments: %s\n",b);
	kprintf("Initial Runlevel K\n");
	kprintf("Modprobe:");
	//char *str = malloc(1024);
	//kstrcpy(str,b);
	//kprintf("%s\n",str);
	kprintf("Failed!\n");
	kprintf("Begin mount\n");
	//if(strcmp(str,"HLT") == 0){
	//	kprintf("Halting CPU\n");
		//halt();
		
	//}
	if(b[0] == 'p' && b[1] == 'a' && b[2] == 0){
		
	}
	kprintf("Dropping into a shell\n");
	char *str = malloc(80);
	kprintf("$");
	char oldc;
	//kprintf("%s\n",str);
	i = 0;
	while(1){
		//shell_gets(str);
		char c = kgetc();
		if(c == '\001')
			continue;
		if(c == oldc)
			continue;
		oldc = c;
		t_putc(c);
		if(c != '\n'){
			str[i] = c;
			i++;
		}
		if(c != '\n')
			continue;
		if(nstrcmp(str,"ls") == 0){
			kprintf("Mount not implemented\n");
		}
		else if(nstrcmp(str,"help") == 0){
			i = 0;
   while (i < commandnum){
        kprintf("%s\n",commands[i]);
        i++;
   }
		}
		else if(nstrcmp(str,"memlist") == 0){
			i = 0;
			while(i < 524288){
				char c = (char)0x00000001;
				kprintf("%c",c);
				c++;
				i++;
			}
		}
		else if(nstrcmp(str,"hlt") == 0){
			kprintf("CPU Halted\n");
			halt();
		}
		else if(nstrcmp(str,"read") == 0){
			i = 0;
			//ide_atapi_read(1,1,1,0,0);
			char *buffer = malloc(1024);
			io_read(0,0,1,buffer);
			kprintf("%s\n",buffer);
			//kprintf("%c\n",ic);
		}
		else if(nstrcmp(str,"echo") == 0){
			kprintf("%s\n",str);
		}
		else{
			kprintf("Command not found\n");
		}
		kprintf("$");
		str = malloc(80);
		str[0] = '\0';
		i = 0;
		c = 0;
		for(int i = 0; i < 80; i++){
			str[i] = '\0';
		}		
	}
}
