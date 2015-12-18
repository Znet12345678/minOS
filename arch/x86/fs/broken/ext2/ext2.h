#ifndef __Z_EXT2_H
#define __Z_EXT2_H
struct ext2_superblock{
	int ninode;
	int nblock;
	int nsblock;
	int nunallocb;
	int nunalloci;
	int supernum;
	int leftshiftbs;
	int leftshiftfs;
	int numofblockpg;
	int numoffpbg;
	int numofinpbg;
	int lastmount;
	int lastwrite;
	short fsckpass;
	short fsckallow;
	int sig;
	int state;
	int erroropp;
	int minorpor;
	int ptimefsck;
	int inter;
	int osid;
	int mpv;
	int uid;
	int gid;
};
enum fs_states{
	FS_CLEAN = 1,
	FS_ERR = 2,
};
enum fs_err_meth{
	FS_ERR_IGNORE = 1,
	FS_ERR_RO = 2,
	KERNPANIC = 3,
};
enum OSID{
	LINUX = 0,
	GNU_HURD = 1,
	MASIX = 2,
	FREEBSD = 3,
	OTHER = 4,
};
/*Skipped for now*/
struct ext_superblock{
	int nrinode;
	unsigned short inlen;
	short bgroup;
};
/*End skipped*/
struct inode{
	int perms;
	int uid;
	int l32s;
	int lat;
	int ct;
	int lmt;
	int dt;
	int gid;
	int hl;
	int ds;
	int flags;
	int ossvn1;
	int pnt0;
	int pnt1;
        int pnt2;
        int pnt3;
        int pnt4;
        int pnt5;
        int pnt6;
        int pnt7;
        int pnt8;
        int pnt9;
        int pnt10;
        int pnt11;
	int sing_indbpnt;
	int doub_indbpnt;
	int trip_indbpnt;
	int generation_n;
	int eab;
	int u32s;
	int baddress;
	int ossvn2;
};
enum inode_type{
	FIFO = 0x1000,
	CHARDEV = 0x2000,
	DIR = 0x4000,
	BDEV = 0x6000,
	RF = 0x8000,
	SIML = 0xA000,
	UNIXSOCK = 0xC000,
};
enum inode_perms{
	OEXEC = 0x001,
	OWRIT = 0x002,
	OREAD = 0x004,
	GEXEC = 0x008,
	GWRIT = 0x010,
	GREAD = 0x020,
	UEXEC = 0x040,
	UWRIT = 0x080,
	UREAD = 0x100,
	STICK = 0x200,
	S_GID = 0x400,
	S_UID = 0x800,
};
enum INODE_FLAGS{
	sec_del = 0x00000001,
	keepcpy = 0x00000002,
	compres = 0x00000004,
	updates = 0x00000008,
	immutef = 0x00000010,
	appendo = 0x00000020,
	dumpcmd = 0x00000040,
	lastacc = 0x00000080,
	hashind = 0x00010000,
	afs_dir = 0x00020000,
	jor_dat = 0x00040000,
};
struct linux_ossvn2{
	short fragment_num;
	short fragment_size;
	int resv;
	int high16buid;
	int high16bgid;
	int resv2;
};
/*Skipping other OS's as of now. Aren't I a hypocrite*/
struct fs_dirent{
	int inode;
	int len;
	int lsb;
	int type;
	char *namechar;
};
enum DIR_TYPE{
	UNKO = 0,
	REGU = 1,
	DIRE = 2,
	CHAR = 3,
	BOLK = 4,
	_FIFO = 5,
	SOCK = 6,
	SYML = 7,
};
struct block_group{
	int ba;
	int ba2;
	int is;
	int ub;
	int ui;
	int dir;
};
#endif
