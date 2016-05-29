/*
*(C)2015 Zachary James Schlotman
*minOS kernel Loader
*minOS kernel
*Used to append args to kernel
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <kernel/tty.h>
#include <kernel/vga.h>
void kernel_loader_init(){
	t_init();
}
void *fmalloc(unsigned long s){
	char ret[s];
	return (void *)ret;
}
char *kgets(){
	char args[80];
	char oldc = '\n';
	char c;
	int i = 0;

	while(1){
		outb(0x60,0x00);
		///c = kgetc(c);
		//if(c == '\n');
		//	break;
		//c = kgetc();
		if(!(inportb(0x64) & 1)){
			//c = kgetc();
			oldc = c;
			continue;
		}
		c = kgetc();
	//	if(c == oldc)
	//		continue;
		if(c == '\001')
			continue;
		//oldc = c;
		//if(c == oldc)
		//	continue;
//		c = kgetc();
		oldc = c;
		//c = kgetc();
		if(c == '\n')
			break;
		//if(inportb(0x60) == 0x1C)
		//	break;
		t_putc(c);
		args[i] = c;
		//kstrcat(args,&c);
		i++;
		
	}
	args[i] = 0x00;
	 i = 0;
	return args;
}
int countsp(char *s){
	int i = 0;
	int ret = 0;
	while(i < strlen(s)){
		if(s[i] == ' ')
			ret++;
		i++;
	}
	return ret;
}
void kernel_loader_main(){
	//malloc_init();
	/*int i = 0;
	while(i < 4){
		int i1 = 0;
		while(i1 < 25){
			t_cputc(' ',COLOUR_BLUE);
			++i1;
		}
		i++;
	}
	i = 0;
	while(i < 25){
		t_cputc(' ',COLOUR_WHITE);
		i++;
	}
	i = 0;
	while(i < 23){
		t_cputc(' ',COLOUR_BLUE);
		i++;	
	}
	t_cputc(' ',COLOUR_WHITE);
	t_cputc(' ',COLOUR_BLUE);*/
	/*kprintf("x86 Simple Kernel\n");
	kprintf("(c) 2015 Zachary James Schlotman\n");
	kprintf("Libc dist by newlib\n");
	kprintf("%d\n",i);
	kprintf("Libk (c) 2015 Zachary James Schlotman\n");*/
	/**kprintf("Znet Operating System Open Source\n(c)2015 Zachary James Schlotman\n\n\n");
	kprintf("Please Enter Any Arguments to pass to kernel\n");
	kprintf("$>");*/
	kprintf("MINOS libzOS kernel\n");
	kprintf("Please set boot options in the following format:\n");
	kprintf("[ ] means optional * * means required\n");
	kprintf("[-v] [-r] [-d] offset=#ofblocks\n");
	kprintf("-v is verbose -r is release -d is development\n");
	kprintf("___________________________________________________________________________\n%)");
	char *s = malloc(1024);
	s = kgets();
	if(strcmp(s,"-v") == 0)
		verbose_kmain();
	else if(strcmp(s,"-r") == 0)
		release_kmain();
	else if(strcmp(s,"-d") == 0)
		dev_kmain();
	/*#ifdef RELEASE
	release_kmain();
	#endif
	#ifdef DEBUG
	verbose_kmain(NULL);
	#endif
	#ifdef DEVELOPER
	dev_kmain();
	#endif
//	verbose_kmain(NULL);
	//kprintf("Defaulting arguments!\n");
	//verbose_kmain(NULL);
	//if(strcmp(s,"-v") == 0)
	//	_verbose_kmain(s);
	//if(strncmp(s,"-g",2) == 0)
	//	graphical_kmain(s);
	//else
	//	verbose_kmain(s);
	//int hd = (int)0x00000475;
	/*if(strcmp(s,"s") == 0)
		zsh();
	else if(strcmp(s,"c") == 0)
		calc();
	else if(strcmp(s,"hlt") == 0)
		outb(0x92,0);
	else
		kernel_main(countsp(s),s);*/
}
void calc(){
	while(1){
		kprintf("1)");
		char s[80];
		kstrcpy(s,kgets());
		int i1 = atoi(s);
		char s1[80];
		kprintf("2)");
		kstrcpy(s1,kgets());
		int i2 = atoi(s);
		char s2[80];
		kprintf("opperation)");
		kstrcpy(s2,kgets());
		int ret;
		if(strcmp(s2,"add") == 0)
			ret = (i1 + i2);
		else if(strcmp(s2,"sub") == 0)
			ret = (i1 - i2);
		else if(strcmp(s2,"mult") == 0)
			ret = (i1 * i2);
		else if(strcmp(s2,"div") == 0)
			ret = (i1 / i2);
		else if(strcmp(s2,"fact") == 0){
			ret = 1;
			for(int i = 0; i < i1;i++){
				ret*=i;
			}
		}
		else{
			kprintf("Invaild opperation enter: add/sub/mult/div/fact\n");
		}
	}
}
