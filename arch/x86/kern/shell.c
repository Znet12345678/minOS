#include <stdio.h>
#include <string.h>
void *_fmalloc(unsigned long s){
        char ret[s];
        return (void *)ret;
}
char *_kgets(){
        char *args =fmalloc(80);
        char oldc = '\n';
        char c;
        int i = 0;
        while(1){
                c = kgetc();
                if(c == oldc)
                        continue;
                if(c == '\001')
                        continue;
                oldc = kgetc();
                if(c == '\n')
                        break;
                if(inportb(0x60) == 0x1C)
                        break;
                t_putc(c);
                args[i] = c;
                i++;

        }
         i = 0;
        return args;
}
void call(char *func,char *args){
		//asm("push %esp, offset %P0" : : "m"(args));
		asm("call %P0" : : "m"(func));
		asm("pop %esp");
}
void zsh(){
	t_init();
	kprintf("zOS precompiled shell\n");
	while(1){
		//char *s = malloc(1024);
		char s[80];
		kprintf("#");
		kstrcpy(s,_kgets());	
		char args[80];
		int i = 0;
		int b = 0;
		while(s[i] != 0){
			if(s[i] == ' ')
				b = 1;
			if(b == 1)
				kstrcat(args,&s[i]);
			i++;
		}
		call(s,args);
	}
}
