/*
*kprintf function
*libio
*(c) 2015 zachary james schlotman
*/
#include <stdio.h>
#include <string.h>
#include <kernel/tty.h>
#include <stdlib.h>
#include <kernel/vga.h>
#include <stdarg.h>
#include <stdbool.h>
void kputs(const char *str){
	kprintf("%s\n",str);
}
void kputc(int ic){
	char c = (char)ic;
	t_write(&c,sizeof(c));
}
static void print(const char *str,ksize_t len){
	int i = 0;
	while(i < len){
		t_putc((int)((const unsigned char *)str)[i]);
		i++;
	}
}
int intlen(int n){
	int ret = 0;
	while(n > 0){
	//	ret++;
		n/=10;
		ret++;
	}
	return ret;
}
void kprintf(const char *format,...){
	va_list args;
	va_start(args,format);
	ksize_t amount;
	bool bad = false;
	while(* format != '\0'){
		if(*format != '%'){
			print_c:
			amount = 1;
			while(format[amount] && format[amount] != '%')
				amount++;
			print(format,amount);
			format+=amount;
			continue;
		}
		const char *begin = format;
		if(*(++(format)) == '%')
			goto print_c;
		if(bad){
			badconv:
				bad = true;
				format = begin;
				goto print_c;
		}
		if(*format == 'c'){
			format++;
			char c = (char)va_arg(args,int);
			print(&c,sizeof(c));
		}
		else if(*format == 's'){
			format++;
			const char *str = (const char *)va_arg(args,const char *);
			print(str,strlen(str));
		}
		else if(*format == 'd'){
			format++;
			int j = (int)va_arg(args,int);
			if(j == 0)
				t_putc('0');
			if(j < 0){
				t_putc('-');
				j*=-1;
			}
			char buf[1024] = {[0 ... 1023]0};
			//char *buf = malloc(intlen(buf));
			//char buf[1024] = {[0 ... 1023]0};
			//char buf[1024] = {[0 ... 1023]0};
			int i = intlen(j) - 1;
			while(j > 0){
				int _buf = (j%10);
				if(_buf == 0)
					buf[i] = '0';
				else if(_buf == 1)
					buf[i] =  '1';
	                        else if(_buf == 2)
                                        buf[i] = '2';
                                else if(_buf == 3)
                                        buf[i] = '3';
                                else if(_buf == 4)
                                        buf[i] = '4';
                                else if(_buf == 5)
                                        buf[i] = '5';
                                else if(_buf == 6)
                                        buf[i] = '6';
                                else if(_buf == 7)
                                        buf[i] = '7';
                                else if(_buf == 8)
                                        buf[i] = '8';
                                else if(_buf == 9)
                                        buf[i] = '9';

				i--;
				j/=10;
			}
			i = 0;
			while(i < strlen(buf)){
				t_putc(buf[i]);
				i++;
			}
			/*while(buf > 0){
				int buf1 = (buf%10);
				if(buf1 == 0)
					ret[intlen(buf) - (i + 1)] = '0';
				else if(buf1 == 1)
					ret[intlen(buf) - (i + 1)] = '1';
				else if(buf1 == 2)
					ret[intlen(buf) - (i + 1)] = '2';
				else if(buf1 == 3)
                                        ret[intlen(buf) - (i + 1)] = '3';
				else if(buf1 == 4)
                                        ret[intlen(buf) - (i + 1)] = '4';
				else if(buf1 == 5)
                                        ret[intlen(buf) - (i + 1)] = '5';
				else if(buf1 == 6)
                                        ret[intlen(buf) - (i + 1)] = '6';
				else if(buf1 == 7)
                                        ret[intlen(buf) - (i + 1)] = '7';
				else if(buf1 == 8)
                                        ret[intlen(buf) - (i + 1)] = '8';
				else if(buf1 == 9)
                                        ret[intlen(buf) - (i + 1)] = '9';
				else
					ret[intlen(buf) - (i + 1)] = 'E';
				buf/=10;
				i++;
			}
			i = 0;
			while(i < intlen(buf)){
				t_putc(ret[i]);
				i++;
			}
			/*char *ret = malloc(1024);
			//ret[1] = '\0';
			int i = 0;
			int n = 1;
			int buf1;
			while(n < intlen(buf)){
				buf1 = (buf % 10);
				if(buf1 == 0)
					ret[(intlen(buf) - n)] = '0';
				else if(buf1 == 1)
					ret[(intlen(buf) - n)] = '1';	
				else if(buf1 == 2)
					ret[(intlen(buf) - n)] = '2';
				else if(buf1 == 3)
					ret[(intlen(buf) - n)] = '3';
                                else if(buf1 == 4)
                                        ret[(intlen(buf) - n)] = '4';
                                else if(buf1 == 5)
                                        ret[(intlen(buf) - n)] = '5';
                                else if(buf1 == 6)
                                        ret[(intlen(buf) - n)] = '6';
                                else if(buf1 == 7)
                                        ret[(intlen(buf) - n)] = '7';
                                else if(buf1 == 8)
                                        ret[(intlen(buf) - n)] = '8';
                                else if(buf1 == 9)
                                        ret[(intlen(buf) - n)] = '9';
				else
					ret[(intlen(buf) - n)] = '\0';
				//kprintf("Exec\n");
				buf/=10;
				n++;
			}
			i = 0;
			while(i < strlen(ret)){
				t_putc(ret[i]);
				i++;
			}*/
			
		}
		else
			goto badconv;
		
	}
	va_end(args);
	//place_cursor();
}
void debug(char *proccess,char *output){
	kprintf("[%s](debug):%s\n",proccess,output);
}
