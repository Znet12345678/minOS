/*
* (C) 2015 Zach Schlotman
* ZOS/minOS Memory allocator
* ZOS/minOS Project
* liballoc
*/
struct page{
	unsigned long size;
	unsigned int startmemory;
	unsigned int endmemory;
	char data[1];
	struct page *next;
	int pos; 
};

int allocated[(1024 * 1024)];
void malloc_init(){
	int i = 0;
	int startmem = 0xC0000000;
	while(startmem < 0xFFFFFFFF){
		if(startmem){
			//allocated[i] = startmem;
			i++;
		}
		startmem++;
	}
}
struct page *findpage(struct page *pa,int esize){
	int size = 0;
	int *_startmem =(int*)0x01000000;
	int *endmem = 0x01000001;
	int startmem = *_startmem;
	int maxmem = *endmem;
	if(startmem == 0 || maxmem == 0){
		//kprintf("[MALLOC][WRN]Using unsafe memory allocation!\n");
		startmem = 0xC0000000;
		maxmem = 0xFFFFFFFF;
	}
	int i = 0;
	int currentmem = *_startmem;
	struct page *pg;
	size = 0;
	//kprintf("MALLOC:searching\n");
	while(1){
		//kprintf("!");
		//kprintf("MALLOC:searching\n");
		if(size == esize){
			//kprintf(">");
			break;
		}
		else if(allocated[i] != currentmem){
			//kprintf(".");
			if(startmem != currentmem){
				//currentmem++;
			}
			currentmem++;
			size++;
			//printf("Hmm\n");
			//allocated[i] = currentmem;
			allocated[i] = currentmem;
			i++;
			continue;
		}
		else if(currentmem == maxmem){
			return -1;
		}
		else{
			//kprintf("|");
			//i++;
			size = 0;
			currentmem++;
			//continue; 
		}
		i++;
	}
	struct page np;
	np.size = size;
	np.startmemory = startmem;
	np.endmemory = currentmem;
	pg = &np;
	pa = pg;
	return pg;
}
struct partialpage{
	struct page *next;
	unsigned long *size;
	unsigned int *startmem;
	unsigned int *endmem;
};
struct combpg{
	struct partialpage *ppg;
	unsigned long size;
	unsigned int *astartmem;
	unsigned int *aendmem;
};
void *malloc(int ssize){
	int  size = 0;
	int i = 0;
	int totalsize = 0;
	struct page *pg;
	struct partialpage *ppg;
	//unsigned int omem = 0x00007E00;
	//char ret[size];
	/*while(1){
		findpage(pg);
		if(pg->size >= size)
			return &(pg);
		if(totalsize >= size){

		}
		totalsize+=pg->size;
		ppg->startmem[i] = pg->startmem;
		ppg->endmem[i] = pg->endmem;
		ppg->size[i] = pg->size;
	}*/
	while(1){
		char ret[ssize];
		pg = findpage(pg,ssize);
		//kprintf(".");
		if(pg->size >= ssize){
			struct page tmppg;
			tmppg = *pg;
			tmppg.data[0] = pg->startmemory;
			tmppg.data[1] = pg->endmemory;
			unsigned int start = pg->startmemory;
			int i = pg->pos;
			while(start < pg->endmemory){
				ret[i] = start;
				ret[i] = 0;
				start++;
				i++;
			}
			//kprintf("MALLOC:found!\n");
			return (void*)ret;
		}
		else{
			unsigned int startmem = pg->startmemory;
			struct page tmppg;
			tmppg = *pg;
			int i = pg->pos;
			while(startmem < pg->endmemory){
				size = (size - 1);
				ret[i] = startmem;
				ret[i] = 0;
				tmppg.pos++;
				i++;
				startmem++;

			}
			pg->pos = (tmppg.pos);
			//kprintf("MALLOC:found partial\n");
		}
	}
}
