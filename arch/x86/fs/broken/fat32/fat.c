#include <stdlib.h>
#include <string.h>
int fat32_init(struct fat32_bootsect *bs,struct fat32_ebr *_ebr){
	char *buf = malloc(1024);
	ata_read_master(buf,0,0);
	struct fat32_bootsect _bs;
	_bs.bps = _comb(strsep(buf,11,2),0);
	_bs.npc = (int)buf[13];
	_bs.rs = _comb(strsep(buf,14,2),0);
	_bs.fats = (int)buf[16];
	_bs.ndentr = _comb(strsep(buf,17,2),0);
	_bs.ts = _comb(strsep(buf,19,2),2);
	_bs.mdt = (int)buf[21];
	_bs.spf = _comb(strsep(buf,22,2),0);
	_bs.spt = _comb(strsep(buf,24,2),0);
	_bs.hs = _comb(strsep(buf,26,2),0);
	_bs.lba = comb(strsep(buf,28,4),0);
	_bs.lasm = comb(strsep(buf,32,4),0);
	bs = &_bs;
	struct fat32_ebr ebr;
	ebr.spf = _comb(strsep(buf,36,4),0);
	ebr.flags comb(strsep(buf,40,4),0);
	ebr.vn = _comb(strsep(buf,42,2),0);
	ebr.crd = comb(strsep(buf,44,4),0);
	_ebr = &ebr;
	return 0;
}
int mount(struct fat32_bootsect *bs,struct fat32_ebr *ebr){
	int start = ((ebr->crd - 2) * bs->spf);
	char *buf = malloc(1024);
	read(buf,start,0);
	if(buf[0] == 0)
		return 0;
	else{
		if(buf[0] == 0xE5)
			return 0;
		else{
			if(buf[11] == 0x0F){
				char *tmpbuf = malloc(1024);
				strcpy(tmpbuf,strsep(buf,0,11));
			}
			else{
				
			}
		}
	}
}
