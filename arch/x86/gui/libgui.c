#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <kernel/vga.h>
void putpixel(unsigned char *screen,int x,int y,int color){
	//memset((char *)screen,color,(320 * 200));
	//unsigned pos = y * 320 + x * 80;
	//memset(screen, + (y *320 + 80) +x,160);
	int pos = x + y * 320;
	//screen[pos] = color & 255;
	screen[pos] = (color >> 8) & 255;
	//screen[pos + 2] = (color >> 16) & 255;
}

/*int draw_line(int len, int i,int pos){
	if (i == 0){
		for(int _i = 0; _i < len;_i++){
			putpixel((unsigned char *)0xA0000,(pos + (_i * 320)),1);
		}
	}
	else if(i == 1){
		for(int _i = 0; _i < len;_i++){
			putpixel((unsigned char *)0xA0000,(pos + _i),1);
		}
	}
	else if(i == 2){
		int j = 0;
		for(int _i = 0; _i < len; _i++){
			putpixel((unsigned char *)0xA000,(pos + (_i * 320) + j),1);
			j++;
		}		
	}
}*/
void gt_putc(char c, int color,int x,int y){
	/*if(c == 'a' || c == 'A' && pos == 0){
		putpixel((unsigned char *)0xA0000,(pos * 4) + 1,color);
		for(int i = 1; i < 3;i++){
			putpixel((unsigned char *)0xA0000,((pos * 4 + 1) * (320 * i)),color);
			putpixel((unsigned char *)0xA0000,((pos * 4 + 1) * (320 * i)) + 2,color);		
		}
		for(int i = 0; i < 3;i++){
			putpixel((unsigned char *)0xA0000,(pos * 4 + 320 * 4 + i),color);
		}
		for(int i = 3 ; i < 6;i++){
			putpixel((unsigned char *)0xA0000,((pos * 4 + 1) * (320 * i)),color);
                        putpixel((unsigned char *)0xA0000,((pos * 4+ 1) * (320 * i)) + 2,color);
		}
	}
	else if(c == 'a' || c == 'A' && pos != 0){
		putpixel((unsigned char *)0xA0000,(pos * 4),color);
                for(int i = 1; i < 4;i++){
                        putpixel((unsigned char *)0xA0000,((pos * 4) + (320 * i)),color);
                        putpixel((unsigned char *)0xA0000,((pos * 4) + (320 * i)) + 2,color);
                }
                for(int i = 0; i < 3;i++){
                        putpixel((unsigned char *)0xA0000,((pos * 4) + (320 * 4) + i),color);
                }
                for(int i = 6; i < 6;i++){
                        putpixel((unsigned char *)0xA0000,((pos * 4) + (320 * i)),color);
                        putpixel((unsigned char *)0xA0000,((pos * 4) + (320 * i)) + 2,color);
                }
	}*/
	if(c == 'a' || c == 'A'){
		putpixel((unsigned char *)0xA0000,(x * 7) + 1,(y * 7),color);
		putpixel((unsigned char *)0xA0000,(x * 7),(y * 7) + 1,color);
		putpixel((unsigned char *)0xA0000,(x * 7) + 2,(y * 7) + 1,color);
		putpixel((unsigned char *)0xA0000,(x * 7),(y * 7) + 2,color);
                putpixel((unsigned char *)0xA0000,(x * 7) + 2,(y * 7) + 2,color);
		putpixel((unsigned char *)0xA0000,(x * 7),(y * 7) + 3,color);
                putpixel((unsigned char *)0xA0000,(x * 7) + 1,(y * 7) + 3,color);
		putpixel((unsigned char *)0xA0000,(x * 7) + 2,(y * 7) + 3,color);
                putpixel((unsigned char *)0xA0000,(x * 7),(y * 7) + 4,color);
		putpixel((unsigned char *)0xA0000,(x * 7) + 2,(y * 7) + 4,color);
		putpixel((unsigned char *)0xA0000,(x * 7),(y * 7) + 5,color);
		putpixel((unsigned char *)0xA0000,(x * 7) + 2,y * 7 + 5,color);
	}
	else if(c == 'b' || c == 'B'){
		putpixel((unsigned char *)0xA0000,(x * 7),(y * 7),color);
		putpixel((unsigned char *)0xA0000,(x * 7) + 1,(y * 7),color);
		putpixel((unsigned char *)0xA0000,(x * 7) + 2,(y * 7),color);
		putpixel((unsigned char *)0xA0000,(x * 7) + 3,(y * 7),color);
		putpixel((unsigned char *)0xA0000,(x * 7),(y * 7) + 1,color);
		putpixel((unsigned char *)0xA0000,x * 7 + 3,(y * 7) + 1,color);
		putpixel((unsigned char *)0xA0000,x * 7,(y * 7) + 2,color);
		putpixel((unsigned char *)0xA0000,x * 7 + 3,y * 7 + 2,color);
		putpixel((unsigned char *)0xA0000,x * 7,y * 7 + 3,color);
		putpixel((unsigned char *)0xA0000,x * 7 + 2,y * 7 + 3,color);
		putpixel((unsigned char *)0xA0000,x * 7,y * 7 + 4,color);
		putpixel((unsigned char *)0xA0000,x * 7 + 3,y * 7 + 4,color);
		putpixel((unsigned char *)0xA0000,x * 7, y * 7 + 5,color);
		putpixel((unsigned char *)0xA0000,x * 7 + 1,y * 7 + 5,color);
		putpixel((unsigned char *)0xA0000,x * 7 + 2,y * 7 + 5,color);
		putpixel((unsigned char *)0xA0000,x * 7 + 3,y * 7 + 5,color);
	}
	else if(c == 'c' || c == 'C'){
                putpixel((unsigned char *)0xA0000,(x * 7),(y * 7),color);
                putpixel((unsigned char *)0xA0000,(x * 7) + 1,(y * 7),color);
                putpixel((unsigned char *)0xA0000,(x * 7) + 2,(y * 7),color);
                putpixel((unsigned char *)0xA0000,(x * 7) + 3,(y * 7),color);
                putpixel((unsigned char *)0xA0000,(x * 7),(y * 7) + 1,color);
                putpixel((unsigned char *)0xA0000,x * 7,(y * 7) + 2,color);
                putpixel((unsigned char *)0xA0000,x * 7,y * 7 + 3,color);
                putpixel((unsigned char *)0xA0000,x * 7,y * 7 + 4,color);
                putpixel((unsigned char *)0xA0000,x * 7, y * 7 + 5,color);
                putpixel((unsigned char *)0xA0000,x * 7 + 1,y * 7 + 5,color);
                putpixel((unsigned char *)0xA0000,x * 7 + 2,y * 7 + 5,color);
                putpixel((unsigned char *)0xA0000,x * 7 + 3,y * 7 + 5,color);
	}
	else if(c == 'd' || c == 'D'){
		putpixel((unsigned char *)0xA0000,x * 7,y * 7,color);
		putpixel((unsigned char *)0xA0000,x * 7 + 1,y * 7,color);
		putpixel((unsigned char *)0xA0000,x * 7,y * 7 + 1,color);
		putpixel((unsigned char *)0xA0000,x * 7 + 2, y * 7 + 1,color);
		putpixel((unsigned char *)0xA0000,x * 7,y * 7 + 2,color);
		putpixel((unsigned char *)0xA0000,x * 7 + 2,y * 7 + 2,color);
		putpixel((unsigned char *)0xA0000,x * 7,y * 7 + 3,color);
		putpixel((unsigned char *)0xA0000,x * 7 + 2,y * 7 + 3,color);
		putpixel((unsigned char *)0xA0000,x * 7,y * 7 + 4,color);
		putpixel((unsigned char *)0xA0000,x * 7 + 2,y * 7 +  4,color);
		putpixel((unsigned char *)0xA0000,x * 7,y * 7 + 5,color);
		putpixel((unsigned char *)0xA0000,x * 7 + 1,y * 7 + 5,color);
	}
	else if(c == 'e' || c == 'E'){

	}

}
void init_gui(){
	unsigned char *screen = (unsigned char *)0xA0000;
	int red = 255;
	int blue = 0;
	int green = 0;
	int color = (0x0255 << 8);
	//memset((char *)0xA0000,1,(320 * 200));
	//putpixel(screen,321,1);
	gt_putc('a',0x7800,0,0);
	//gt_putc('a',0x7800,0,0);
	gt_putc('a',0x7800,0,1);
	gt_putc('b',0x7800,1,1);
	gt_putc('a',0x7800,0,2);
	gt_putc('b',0x7800,1,2);
	gt_putc('c',0x7800,2,2);
	gt_putc('a',0x7800,0,3);
	gt_putc('b',0x7800,1,3);
	gt_putc('c',0x7800,2,3);
	gt_putc('d',0x7800,3,3);
	//for(int i = 0; i < 50;i++)
	//	putpixel(screen,i * 320,1);
	//fo/r(int i = 0; i < 50;i++)
	//	putpixel(screen,i,1);
	
}
