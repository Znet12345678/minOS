#include "ext2.h"
#include <stdlib.h>
long hex2dec(unsigned const char *hex){
	long ret = 0;
	int i = 0;
	while(hex[i] != 0){
		//if(hex[i] >= 0x00 && hex[i] <= 0x09)
		//	ret+=(10 * i) * hex[i];
	}
	//kprintf("\n");
	return ret;
}
char *strsep(char *buf,int offset,int num){
	char *ret = malloc(1024);
	int j = 0;
	int i = offset;
	int end = (offset + num);
	int i1 = 0;
	while(i1 < num){
		///kstrcat(ret,&buf[i]);
		ret[i1] = buf[i];
		i++;
		i1++;
	}
	return ret;
}
int get_partition(partnum){
	if(partnum > 4)
		return -1;
	//int i = (12 * partnum);
	int i = 0;
	if(partnum == 1)
		i = 190;
	else if(partnum == 2)
		i = 206;
	else if(partnum == 3)
		i = 222;
	else
		i = 190;
	int ret = 0;
	char *buf = malloc(1024);
	ata_read_master(buf,1,0x00);
	ret = buf[(i + 2)];
	return ret;
}
int _intlen(int i){
	int ret = 0;
	while(i){
		ret++;
		i/=10;
	}
	return ret;
}
int _hex2int(char c){
	if(c == '0')
		return 0;
	else if(c == '1')
		return 1;
	else if(c == '2')
		return 2;
	else if(c == '3')
		return 3;
        else if(c == '4')
                return 4;
        else if(c == '5')
                return 5;
        else if(c == '6')
                return 6;
        else if(c == '7')
                return 7;
        else if(c == '8')
                return 8;
        else if(c == '9')
                return 9;
        else if(c == 'A')
                return 10;
        else if(c == 'B')
                return 11;
        else if(c == 'C')
                return 12;
        else if(c == 'D')
                return 13;
        else if(c == 'E')
                return 14;
        else if(c == 'F')
                return 15;


}
int hex2int(char c){
	int i = c;
	
}
int comb(const char *str,int n){
	int i = 0;
	int ret = 0;
	while(i < n){
		//if(str[i] == 0x01)
		//	kprintf("(:");
		/*int j = str[i];
		int k = 0;
		int m = 0;
		if(j < 10)
			j*=10;
		else
			while(j > 0){
				k+=(10 ^ (_intlen(j) - m)) * j % 10;
				m++;
				j/=10;
			}
		//kprintf("%d",j);
		//if(j == 1)
		//	kprintf("(:");*/
		i++;
	}
	
	//ret = (char)ret;
	ret = (char)str
	int ret = 0;
	int i = 0;
	char *s = malloc(1024);
	/*while(i < n){
		
		//kstrcat(s,&((char*)buf[i]));
		n++;
	}*/
	
	return ret;
	//kprintf("\n");
	//return ret;
}
struct ext2_superblock *parse_sblk(int partnum){
	int i = get_partition(partnum);
	if(i > 0)
		kprintf("[EXT2_SUPERBLOCK]Found partition!\n");
	else
		i = 0;
	struct ext2_superblock *ret;
	struct ext2_superblock retnp;
	char *buf = malloc(1024);
	int i1 = 0;
	//char *tmpbuf = malloc(4);
	/*if(i != 0)
		ata_read_master(buf,((i * 4)/256),0x00);
	else{
		kprintf("[WRN]: Looking for superblock at offset 1024\n");
		ata_read_master(buf,4,0x00);
	}*/
	ata_read_master(buf,2,0x00);
	const char *cmp = strsep(buf,0,4);
	//if(cmp[0] == 0x58 || cmp[0] == 0x64)
	//	kprintf("(:");

	//kprintf("%s\n",strsep(buf,0,4));
	retnp.ninode = comb(strsep(buf,0,4),4);
//	if(cmp[0] == 0x0 )
//		kprintf("YEAH!\n");
	/*int n = 0;
	while(n < 4){
		if(cmp[n] == 0x10 || cmp[n] == 0x01)
			kprintf("(:");
		//kprintf("%c",buf[n]);
		n++;
	}*/
//	kprintf("%s\n",buf);
        retnp.nblock = comb(strsep(buf,4,4),4);
        retnp.nsblock = comb(strsep(buf,8,4),4);
        retnp.nunallocb = comb(strsep(buf,12,4),4);
        retnp.nunalloci = comb(strsep(buf,16,4),4);
        retnp.supernum = comb(strsep(buf,20,4),4);
        retnp.leftshiftbs = comb(strsep(buf,24,4),4);
        retnp.leftshiftfs = comb(strsep(buf,28,4),4);
        retnp.numofblockpg= comb(strsep(buf,32,4),4);
     //   retnp.numofffpbg= comb(strsep(buf,36,4));
        retnp.numoffpbg = comb(strsep(buf,36,4),4);
        retnp.numofinpbg = comb(strsep(buf,40,4),4);
        retnp.lastmount = comb(strsep(buf,44,4),4);
        retnp.lastwrite = comb(strsep(buf,48,4),4);
        retnp.fsckpass = comb(strsep(buf,52,2),2);
        retnp.fsckallow = comb(strsep(buf,54,2),2);
        retnp.sig = comb(strsep(buf,56,2),2);
        retnp.state = comb(strsep(buf,58,2),2);
        retnp.erroropp = comb(strsep(buf,60,2),2);
        retnp.minorpor = comb(strsep(buf,52,2),2);
        retnp.ptimefsck = comb(strsep(buf,64,4),4);
        retnp.inter = comb(strsep(buf,68,4),4);
        retnp.osid = comb(strsep(buf,72,4),4);
	retnp.mpv = comb(strsep(buf,76,4),4);
        retnp.uid = comb(strsep(buf,80,2),2);
	retnp.gid = comb(strsep(buf,82,2),2);
	ret = &retnp;
	return ret;
	i1 = 0;


}
