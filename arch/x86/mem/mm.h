#ifndef __MEMORY_MANAGER_H
#define __MEMORY_MANAGER_H
#define RD_OPP_RW 0
#define RD_OPP_RO 1
#define RD_OPP_WO 2
#define RD_OPP_RW_DEV 3
#define RD_OPP_RO_DEV 4
#define RD_OPP_WO_DEV 5
struct rd_superblk{
	int numoffiles;
	int sizeofrd;
};
struct rd_file{
	int alloc;
	int pos;
    int islongname;
    int namelen;
	char *name;
    int f_size;
    int *raw;
    int size;
    int opp;
};
struct rd_file *read_rd_file_full(const char *name,int startmem);
int write_rd_file(const char *name,const int *cont,int size,int startmem);
#endif
