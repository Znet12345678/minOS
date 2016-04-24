//
//  expfs.h
//  
//
//  Created by Zach Schlotman on 4/24/16.
//
//

#ifndef ____expfs__
#define ____expfs__
#define TYPE_DIR 0
#define TYPE_FILE 1
#define TYPE_DEV 2
struct expfs_dirent{
    int nf;/*Number Of Files*/
    int size/*Size of directory and containing files*/
    char *name;/*Name of directory*/
    int offset;/*Offset lba*/
};
struct expfs_infoblk{
    int size;/*Size of infoblk*/
    char *name;/*Name*/
    int offset;/*offset lba*/
    int type;/*File,directory or device file*/
    int len;/*Length of file*/
};
struct expfs_FILE{
    int size;
    char *name;
    int pos_blk;/*Block position*/
    int pos_byte;/*Byte Position*/
    int end_blk;/*Ending block*/
    int end_byte;/*Ending byte*/
};
int create_dir(struct expfs_dirent *dent);
int create_file(struct expfs_FILE *fent);
int mount(int partnum);
#endif /* defined(____expfs__) */
