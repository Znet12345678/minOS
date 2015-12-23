#include <string.h>
#include <stdio.h>
#include "module.h"

int mod_init(char *modules[]){
	kprintf("[MOD] Initializing modules...this may take some time (and memory) brace yourself\n");
	char *_modules[MAX_MODULES] = {malloc(1024)};
	modules = _modules;
}
int scan(char *name,char **modules,int max){
	int i = 0;
	while (i < max){
		if(strcmp(modules[i],name) == 0)
			return i;
		i++;
	}
	return 0;
}
void _call(char *name){
	 asm volatile("call %%eax" : :"a"(name));
}
int call_module(char *name,char **modules){
	if(scan(name,modules,MAX_MODULES) != 0){
		char init[80];
		char main[80];
		kstrcpy(init,name);
		kstrcpy(main,name);
		kstrcat(init,"_init");
		kstrcat(main,"_main");
		kprintf("[MOD] JMP %s %s\n",init,main);
		_call(init);
		_call(main);
	}
	else{
		return -1;
	}
}
int register_module(char * name,int pos){
	modules[pos] = name;
	pos++;
	return pos;
}
