#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
/*
*Header:
*next mem pntr
*h.size
*h.free?
*/
int free(void *v){
}
struct header{
	int *nxt;
	int size;
	int free;
};
void init_mem(){
	int *mem = (int*)0x01000000;
	*mem = 0x7F;
}
int *__find_next_free_head(int *curr){
	int *dup = curr;
	while(1){
		struct header h;
		
		h.nxt = *dup;
		*dup++;
		h.size = *dup;
		*dup++;
		h.free = *dup;
		*dup++;
		for(int i = 0; i < h.size;i++)
			*dup++;
		if(*dup == 0)
			return dup;
	}
}
int init_memblk(int *pntr,struct header init){
	*pntr = init.nxt;
	*pntr++;
	*pntr = init.size;
	*pntr++;
	*pntr = init.free;
	*pntr++;
	int *dup = pntr;
	for(int i = 0; i < init.size; i++){
		*pntr = 0;
		*pntr++;
	}
}
void *malloc(size_t n){
	//kprintf("kmalloc(%d)\n",n);
	char *ret;
	int *mem = (int*)0x01000000;
	int *orig;
	int allocated = 0;
	while(allocated < n){
		if(*mem == 0x7F || *mem == 0){
			struct header init;
			init.size = n;
			int *nxt = (int*)(0x01000000 + n);
			init.nxt = nxt;
			init.free = 0;
			init_memblk(mem,init);
			*mem++;
			for(int i = 0; i < n; i++){
				*ret = *mem;
				*ret++;
				*mem++;
				allocated++;
			}
			struct header nxth;
			nxth.size = 0;
			nxth.free = 0;
			nxth.nxt = 0;
			init_memblk(mem,nxth);
		}
		else{
			*mem++;
			int size = *mem;
			*mem++;
			int free = *mem;
			*mem++;
			if(free == 1){
				for(int i = 0; i < size;i++){
					*ret = *mem;
					*ret++;
					*mem++;
					allocated++;
				}
			}else{
				for(int i = 0; i < size;i++)
					*mem++;
			}
		}
	}
}
void *_kmalloc(size_t n){
	kprintf("[DEBUG]malloc(%d)\n",n);
	int allocated = 0;
	int *ret;
	int *mem = (int*)0x01000000;
	int *orig;
	while(allocated < n){
		orig = mem;
		struct header h;
		h.nxt = *mem;
		*mem++;
		h.size = *mem;
		*mem++;
		h.free = *mem;
		*mem++;
		if(h.nxt == 0 && h.size == 0 && h.free == 1){
			int *struct_start = mem;
			for(int i = 0; i <= n;i++)
				*struct_start++;
			if(struct_start == 0){
				*struct_start = 0;
				*struct_start++;
				*struct_start = 0;
				*struct_start++;
				*struct_start = 1;
			}
			*mem = struct_start;
			*mem++;
			*mem = n;
			*mem++;
			*mem = 0;
			*mem++;
			for(int i = 0; i < n;i++){
				*ret = *mem;
				*mem++;
				*ret++;
				allocated++;
			}
		}
		else if(h.free == 1 && h.nxt == 0){
			*orig = __find_next_free_head(orig);
			*orig++;
			*orig = n;
			*orig++;
			*orig = 0;
			*orig++;
			if(n < h.size){
				for(int i = 0; i < n;i++){
					*ret = *mem;
					*mem++;
					*ret++;
					allocated++;
				}
			}
			else{
				for(int i = 0; i < h.size;i++){
					*ret = *mem;
					*mem++;
					*ret++;
					allocated++;
				}
			}
			int *struct_start = mem;
			if(*struct_start == 0){
				*struct_start = 0;
				*struct_start++;
				*struct_start = 0;
				*struct_start++;
				*struct_start = 1;
				*struct_start++;
			}
		}else{
			for(int i = 0; i < h.size;i++)
				*mem++;
		}

	}
	return (void *)ret;
}
