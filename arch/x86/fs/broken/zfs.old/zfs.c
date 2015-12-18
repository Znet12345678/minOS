/*
*Znet File System Prototype
*Not for actual use
*(c)2015 Zachary James Schlotman
*WIP
*/
#include "zfs.h"
#include <stdlib.h>
int atoic(char s){
	if(s == '0')
		return 0;
	else if(s == '1')
		return 1;
	else if(s == '2')
		return 2;
	else if(s == '3')
		return 3;
	else if(s == '4')
		return 4;
	else if(s == '5')
		return 5;
	else if(s == '6')
		return 6;
	else if(s == '7')
		return 7;
	else if(s == '8')
		return 8;
	else if(s == '9')
		return 9;
	else
		return -1;
}
void assemble_fs(char *rfs){
	struct zfs_block *blks;
	struct zfs_file *files;
	struct zfs_dir *dirs;
	struct zfs_block _blks;
	struct zfs_file _files;
	struct zfs_dir _dirs;
	int i = 0;
	int i1 = 0;
	int i2 = 0;
	int sigcnt = 0;
	int bb = 0;
	int rootfs = 0;
	int ind = 0;
	while(1){
		if(rfs[i] == root_sig[0]){
			i2 = i;
			while(i1 < 17){
				if(rfs[i2] == root_sig[i1])
					sigcnt++;
				
				else{
					bb = 1;
				}
				i2++;
				i1++;
			}
			if(bb != 1){
				rootfs = 1;
			}
		}
		else if(rootfs == 1){
			if(rfs[i] == dir_sig){
				struct zfs_dir tmpdir;
				tmpdir.sig = dir_sig;
			 	i1 = i;
				while(atoic(rfs[i1]) != -1)
					i1++;
				int diff = (i1 - i);
				i1 = 0;
				i2 = i;
				char s[diff];
				while(i1 < diff){
					s[i1] = rfs[i2];
					i1++;
					i2++;
				}
				int len = atoi(s);
				tmpdir.path_len = len;
				i1 = 0;
				char *path = malloc(1024);
				while(i1 < len){
					kstrcat(path,&rfs[i2]);
					i2++;
					i1++;
				}
				tmpdir.path = path;
				int i3 = i2;
				while(1){
					struct zfs_file tmpf;
					if(rfs[i3] == f_sig[0] && rfs[i3 + 1] == f_sig[1]){
						
					}
					i3++;
				}
				
			}
		}
		else
			break;	
		i++;
	}
}
void get_fs_info(struct zfs_file *files,struct zfs_dir *dirs){
	struct zfs_file _files = *(files);
	struct zfs_dir _dirs = *(dirs);
	struct zfs_block *block;
	
}
mount_zfs(){
	struct zfs_file *files;
	struct zfs_dir *dirs;
	get_fs_info(files,dirs);
}
