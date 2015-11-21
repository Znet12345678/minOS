#include <string.h>
int combi(int *p,unsigned long size){
	int inc = 0;
	int i = 0;
	int pow;
	while(inc < size){
		pow = 1;
		int tmp = 0;
		while(tmp < (size - (inc + 1))){
			pow*=10;
			tmp++;
		}
		i+=(pow * p[inc]);
		inc++;
	}
	return i;
}
int atoi(const char *str){
	int i = 0;
	int tmp[strlen(str)];
	while(i < strlen(str)){
		if(str[i] == '0')
			 tmp[i] = 0;
		else if(str[i] == '1')
                         tmp[i] = 1;
		else if(str[i] == '2')
                         tmp[i] = 2;
		else if(str[i] == '3')
                         tmp[i] = 3;
		else if(str[i] == '4')
                         tmp[i] = 4;
		else if(str[i] == '5')
                         tmp[i] = 5;
		else if(str[i] == '6')
                         tmp[i] = 6;
		else if(str[i] == '7')
                         tmp[i] = 7;
		else if(str[i] == '8')
                         tmp[i] = 8;
		else if(str[i] == '9')
                         tmp[i] = 9;
		i++;
	}
	i = 0;
	int ret = combi(tmp,strlen(str));
	return ret;
	
}
