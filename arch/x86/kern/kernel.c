/*
*Outdated kernel main. Used for functions and enums
*(c)2015 Zachary James Schlotman
*/
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <kernel/tty.h>
#include <kernel/vga.h>
#include <io.h>
enum INPUT_KEYS{
	A = 0x9E,
	B = 0xB0,
	C = 0xAE,
	D = 0xA0,
	E = 0x92,
	F = 0xA1,
	G = 0xA2,
	H = 0xA3,
	I = 0x97,
	J = 0xA4,
	K = 0xA5,
	L = 0xA6,
	M = 0xB2,
	N = 0xB1,
	O = 0x98,
	P = 0x99,
	Q = 0x90,
	R = 0x93,
	S = 0x9F,
	T = 0x94,
	U = 0x96,
	V = 0xAF,
	W = 0x91,
	X = 0xAD,
	Y = 0x95,
	Z = 0xAC,
	US = 0x0C,
	SPACE = 0x39,
	NL = 0x1C
};
void keyboard_irq();
char kgetc(){
	int i = 0;
	unsigned char sc;
		sc = inportb(0x60);
		if(sc == A){
			return 'a';
		}
		else if (sc == B){
			return 'b';
		}
		else if (sc == C){
                        return 'c';
                }

		else if (sc == D){
                        return 'd';
                }

		else if (sc == E){
                        return 'e';
                }

		else if (sc == F){
                        return 'f';
                }

		else if (sc == G){
                        return 'g';
                }

		else if (sc == H){
                        return 'h';
                }

		else if (sc == I){
                        return 'i';
                }

		else if (sc == J){
                        return 'j';
                }

		else if (sc == K){
                        return 'k';
                }

		else if (sc == L){
                        return 'l';
                }

		else if (sc == M){
                        return 'm';
                }

		else if (sc == N){
                        return 'n';
                }

		else if (sc == O){
                        return 'o';
                }

		else if (sc == P){
                        return 'p';
                }

		else if (sc == Q){
                        return 'q';
                }

		else if (sc == R){
                        return 'r';
                }

		else if (sc == S){
                        return 's';
                }

		else if (sc == T){
                        return 't';
                }

		else if (sc == U){
                        return 'u';
                }

		else if (sc == V){
                        return 'v';
                }

		else if (sc == W){
                        return 'w';
                }

		else if (sc == X){
                        return 'x';
                }

		else if (sc == Y){
                        return 'y';
                }

		else if (sc == Z){
                        return 'z';
                }
		else if(sc == NL){
			return '\n';
		}
		else if(sc == SPACE){
			return ' ';
		}
		else if(sc == 0x00){
			return '\001';
		}
		else if(sc == US)
			return '-';
		else{
			return '\001';
		return '\001';	
	}
}
void putstr(const char *str){

        for(int i = 0; i < strlen(str);i++){
                t_putc(str[i]);
        }

}
char *shell_gets(char *ret){
	char *g = malloc(1024);
	char c;
	char oldc;
	int i1 = 0;
	int i = strlen(g);
	while (1){
		c = kgetc();
		if(c == oldc){
			continue;
		}
		if(c == '\001'){
			continue;
		}
		oldc = c;
		t_putc(kgetc());
		if(c == '\n'){
			break;
		}
		if(inportb(0x60) == NL){
			break;
		}
		g[i] = c;
		i++;
	}
	ret = g;
	t_putc('\n');
	t_putc('>');
	return ret;
}
uint8_t lastkey = 0;
uint8_t *keycache = 0;
uint16_t key_loc = 0;
uint8_t __kbd_enabled = 0;

