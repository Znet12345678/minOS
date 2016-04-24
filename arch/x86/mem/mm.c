/*
*minOS Memory Manager
*This is to serve as an update to the previous memory manager
*(c) 2016 Zachary James Schlotman
*/
#include <stdlib.h>
#include <stdio.h>
#include "mm.h"
int zero_memory(int start,int end){
	int *pnt = (int *)start;
	int curmem = start;
	while(curmem < end){
		*pnt = 0;
		curmem++;
		*pnt++;
	}
	return 0;	
}
int write_ramdisk(int start,int size){
	int *pnt = (int *)start;
	int memend = start + size;
	zero_memory(start,memend);
	*pnt = 0x1F;
	*pnt++;
	*pnt = 'r';
	*pnt++;
	*pnt = 'F';
	*pnt++;
	*pnt = 'S';
	*pnt++;
	return 0;
}
struct rd_page{
	int startmem;
	int endmem;
};
struct rd_page *find_rd_page(int startmem,int size,int endmem){
	struct rd_page *ret = malloc(sizeof(struct rd_page *));
	int found = 0;
	int f;
    int *val = malloc(3);
	int currmem = startmem;
	int *pntr = (int *)startmem;
	while(currmem < endmem){
        if(found == size){
            ret->endmem = currmem + 1;
            return ret;
        }
        else if(found == 0 && *pntr == 0){
            ret->startmem = currmem + 1;
            found++;
            *pntr++;
            currmem++;
            continue;
        }
        else if(found == 0 && *pntr != 0){
            ret->startmem = -1;
            *pntr++;
            currmem++;
            continue;
        }
        else if(*pntr == 0){
            found++;
            *pntr = 1;
            *pntr++;
            currmem++;
            continue;
        }
        else{
            int i = 0;
            while(i < found){
                *pntr = 0;
                *pntr--;
                i++;
            }
            pntr = (int*)currmem;
            found = 0;
            continue;
        }
	}
	return ret;
}
void write_mem(int *pntr,const char *buf,int size){
	int i = 0;
	while(i < size){
		*pntr = buf[i];
		*pntr++;
		i++;
	}

}
int check_for_file(const char *name,int startmem){
    int *mem = (int*)startmem;
    while(1){
        int alloc = *mem;
        if(alloc == 0)
            return 0;
        *mem++;
        int pos = *mem;
        *mem++;
        int islongname = *mem;
        if(islongname){
            *mem++;
            int namelen = *mem;
            *mem++;
            int i = 0;
            char *_name = malloc(namelen + 1);
            while(i < namelen){
                _name[i] = *mem;
                *mem++;
                i++;
            }
            if(strcmp(_name,name) == 0)
                return 1;
            int f_size = *mem;
            i = 0;
            while(i < f_size){
                *mem++;
                i++;
            }
            *mem++;
            continue;
        }
        else{
            *mem++;
            int namelen = *mem;
            *mem++;
            int i = 0;
            char *_name = malloc(namelen + 1);
            while(i < namelen){
                _name[i] = *mem;
                *mem++;
                i++;
            }
            if(strcmp(_name,name) == 0)
                return 1;
            int f_size = *mem;
            i = 0;
            while(i < f_size){
                *mem++;
                i++;
            }
            *mem++;
            continue;
        }
    }
}
//THERE IS SOMETHING WRONG WITH THIS FUNCTION
int _check_for_file(const char *name,int startmem){
    int *mem = (int *)startmem;
    while(1){
        int isalloc;
        isalloc = *mem;
        if(isalloc == 0)
            return 0;
        *mem++;
        int pos;
        pos = *mem;
        *mem++;
        char *_name = malloc(1024);
        int islongname = *mem;
        if(islongname == 0){
            *mem++;
            int namelen = *mem;
            if(strlen(name) == namelen){
                int i = 0;
                *mem++;
                while(i <namelen){
                    _name[i] = *mem;
                    *mem++;
                    i++;
                }
                i = 0;
                while(i < 10 - namelen){
                    _name[i] = *mem;
                    *mem++;
                    i++;
                }
                if(strcmp(name,_name) == 0)
                    return 1;
                int f_size;
                f_size = *mem;
                i = 0;
                while(i < (f_size + 2)){
                    *mem++;
                    i++;
                }
                continue;
            }
            int i = 0;
            while(i < 11){
                *mem++;
                i++;
            }
            int f_size;
            f_size = *mem;
            i = 0;
            while(i < (f_size + 2)){
                *mem++;
                i++;
            }
            continue;
        }
        else{
            *mem++;
            int namelen = *mem;
            if(strlen(name) == namelen){
                int i = 0;
                *mem++;
                while(i < namelen){
                    _name[i] = *mem;
                    *mem++;
                    i++;
                }
                if(strcmp(_name,name) == 0){
                    return 1;
                }
                int f_size;
                f_size = *mem;
                i = 0;
                while(i < (f_size + 2)){
                    *mem++;
                    i++;
                }
                continue;
            }
            int i = 0;
            while(i < namelen + 1){
                *mem++;
                i++;
            }
            int f_size;
            f_size = *mem;
            i = 0;
            while(i < (f_size + 2)){
                *mem++;
                i++;
            }
            continue;
        }
        *mem++;
    }
    return 0;
}
int write_rd_file(const char *name,const int *cont,int size,int startmem){
    kprintf("[START]write_rd_file\n");
	struct rd_page *pg = find_rd_page(startmem, size,startmem + 524288);

    if(!(pg)){
        kprintf("Failed to find page\n");
        return -1;
    }
    if(check_for_file(name,startmem + 4) != 0){
        kprintf("This file already exists,please choose a different name\n");
        return -1;
    }
	int j = 0;
    int k = 0;
	int i = pg->startmem;
	int endmem = pg->startmem + size;
    int *mem = (int*)pg->startmem;
    *mem = 1;
    *mem++;
    *mem = 0;
    *mem++;
    if(strlen(name) <= 10){
        *mem = 0;
        *mem++;
        *mem = strlen(name);
        *mem++;
        while(k < strlen(name)){
            *mem = name[k];
           
            *mem++;
            k++;
        }
        k = 0;
        while(k < (10 - strlen(name))){
            *mem = 0;
            *mem++;
            k++;
        }
    }
    else{
        *mem = 1;
        *mem++;
        *mem = strlen(name);
        *mem++;
        k = 0;
        while(k < strlen(name)){
            *mem = name[k];
            *mem++;
            k++;
        }
    }
    *mem = size;
    *mem++;
	while(i < size){
		*mem = cont[j];
		*mem++;
        j++;
		i++;
	}
    if(strlen(name) < 10){
        *mem = size + 18;
        *mem++;
    }
    else{
        *mem = size + strlen(name) + 8;
        *mem++;
    }
    kprintf("[DONE][SUCC]write_rd_file\n");
	return 0;
}
struct rd_file *read_rd_file_full(const char *name,int startmem){
    kprintf("[START]read_rd_file_full\n");
    struct rd_page *pg = malloc(sizeof(struct rd_page *));
	struct rd_file *f = malloc(sizeof(struct rd_file *));
    struct rd_file *ret = malloc(sizeof(struct rd_file *));
    int *mem = (int*)startmem + 4;
    char *_name = malloc(80);
    int islongname,pos,isalloc,f_size,namelen,size,opp;
    while(1){
        isalloc = *mem;
        //kprintf(".");
        if(isalloc == 0){
            kprintf("[FAIL]read_rd_file_full\n");
            return (struct rd_file *)-1;
        }
        *mem++;
        pos = *mem;
        *mem++;
        islongname = *mem;
        *mem++;
        namelen = *mem;
        *mem++;
        if(islongname == 0){
            int i = 0;
            //kprintf(".");
            while(i < 10){
                _name[i] = *mem;
                *mem++;
                i++;
            }
            //kprintf("File name:%s\n",_name);
            if(strcmp(name,_name) == 0)
                break;
            //kprintf("Ignoring filename:%s\n",_name);
            f_size = *mem;
            i = 0;
            while(i < (f_size + 1)){
                *mem++;
                i++;
            }
            size = *mem;
            *mem++;
        }
        else{
            int i = 0;
            while(i < namelen){
                _name[i] = *mem;
                *mem++;
                i++;
            }
            if(strcmp(name,_name) == 0)
                break;
            //kprintf("Ignoring filename:%s\n",_name);
            f_size = *mem;
            i = 0;
            while(i < (f_size + 1)){
                *mem++;
                i++;
            }
            size = *mem;
            *mem++;
        }
    }
    kprintf("%c",*mem);
    *mem++;
    kprintf("%c",*mem);
    ret->alloc = 1;
    ret->pos = -1;
    ret->islongname = islongname;
    ret->namelen = namelen;
    ret->name = _name;
    ret->f_size = f_size;
   // if(f_size == 0)
     //   panic();
    int i = 0;
    ret->raw = malloc(f_size);
    while(i < f_size){
        ret->raw[i] = *mem;
        kprintf(".");
        *mem++;
        i++;
    }
    kprintf("[DONE][SUCC]read_rd_file_full\n");
    return ret;
}
struct rd_file *get_file(int fid,int startmem){
    
}
void kmem_init(){
	kprintf("[KMEM] Start\n");
	kprintf("Setting kernel memory bounds\n");
	int *mem = (int*)0x01000000;
	*mem = 0xC0000000;
	*mem++;
	*mem = 0xC2000000;
	kprintf("Zeroing kernel memory\n");
	if(zero_memory(0xC0000000,0xC2000000) < 0)
		panic();
	kprintf("Creating 512KB ramdisk\n");
	if(write_ramdisk(0x00100000,524288) < 0)
		panic();
	kprintf("[KMEM] Done\n");
}
struct mpage{
	int startmem;
	int endmem;
	char data[2];
};
