#include <syscalls.h>
#include <minfs.h>
int mount(char *mntpnt,int drive){
	debug("MOUNT","Parsing minfs SuperBlock");
	struct minfs_superblock garbage;
	struct minfs_superblock *superblk = parse_superblk(0,garbage);
		
}
