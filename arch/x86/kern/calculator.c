#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define OPP_ADD 1
#define OPP_SUB 2
#define OPP_DIV 3
#define OPP_MULT 4
#define OPP_FACT 5
#define OPP_EXP 6
#define OPP_SQRT 7
void calculator_init(){
	t_init();
}
void calculator_process(const char *buf);
void calculator(){
	kprintf("minOS Calculator v0.1\n");
	while(1){
		kprintf("\n#");
		char *buf = malloc(1024);
		kstrcat(buf,kgets());
		calculator_process(buf);
	}
}
void solve_mult(const char *tmp,int *mult){
        int i = 0;
        int *_tmp = malloc(80);
        int n = 0;
        int first = 0;
        while(tmp[i] != 0){
                  if(tmp[i] == '*' && first == 0){
                        int j = i - 1;
                        int *__tmp = malloc(3);
                        while(tmp[j] == ' ')
                                j--;
                        ///printf("%d\n",j);
                        __tmp[0] = atoi(&tmp[j]);
                        j = i + 1;
                        while(tmp[j] == ' ')
                                j++;
                        __tmp[1] = atoi(&tmp[j]);
                        int result = __tmp[1] * __tmp[0];
                        mult[n] = result;
                        n++;
                        first = 1;
                }
                else if(tmp[i] == '*' && first == 1){
                        int j = i + 1;
                        while(j == ' ')
                                j++;
                        int result = mult[n - 1] * atoi(&tmp[j]);
                        mult[n] = result;;
                        n++;
                }
                i++;
	}
}
void solve_div(const char *tmp,int *div){
	int i = 0;
        int *_tmp = malloc(80);
        int n = 0;
        int first = 0;
        while(tmp[i] != 0){
                  if(tmp[i] == '/' && first == 0){
                        int j = i - 1;
                        int *__tmp = malloc(3);
                        while(tmp[j] == ' ')
                                j--;
                        ///printf("%d\n",j);
                        __tmp[0] = atoi(&tmp[j]);
                        j = i + 1;
                        while(tmp[j] == ' ')
                                j++;
                        __tmp[1] = atoi(&tmp[j]);
                        int result = __tmp[1] / __tmp[0];
                        div[n] = result;
                        n++;
                        first = 1;
                }
                else if(tmp[i] == '/' && first == 1){
                        int j = i + 1;
                        while(j == ' ')
                                j++;
                        int result = div[n - 1] / atoi(&tmp[j]);
	 		div[n] = result;
                        n++;
                }
                i++;
        }
}

void solve_add(const char *tmp,int *add){
	int i = 0;
        int *_tmp = malloc(80);
        int n = 0;
        int first = 0;
        while(tmp[i] != 0){
                  if(tmp[i] == '+' && first == 0){
                        int j = i - 1;
                        int *__tmp = malloc(3);
                        while(tmp[j] == ' ')
                                j--;
                        ///printf("%d\n",j);
                        __tmp[0] = atoi(&tmp[j]);
                        j = i + 1;
                        while(tmp[j] == ' ')
                                j++;
                        __tmp[1] = atoi(&tmp[j]);
                        int result = __tmp[1] + __tmp[0];
                        add[n] = result;
                        n++;
                        first = 1;
                }
                else if(tmp[i] == '+' && first == 1){
                        int j = i + 1;
                        while(j == ' ')
                                j++;
                        int result = div[n - 1] + atoi(&tmp[j]);
	 		add[n] = result;
                        n++;
                }
                i++;
        }
}
void solve_sub(const char *tmp,int *div){
	int i = 0;
        int *_tmp = malloc(80);
        int n = 0;
        int first = 0;
        while(tmp[i] != 0){
                  if(tmp[i] == '-' && first == 0){
                        int j = i - 1;
                        int *__tmp = malloc(3);
                        while(tmp[j] == ' ')
                                j--;
                        ///printf("%d\n",j);
                        __tmp[0] = atoi(&tmp[j]);
                        j = i + 1;
                        while(tmp[j] == ' ')
                                j++;
                        __tmp[1] = atoi(&tmp[j]);
                        int result = __tmp[1] - __tmp[0];
                        div[n] = result;
                        n++;
                        first = 1;
                }
                else if(tmp[i] == '-' && first == 1){
                        int j = i + 1;
                        while(j == ' ')
                                j++;
                        int result = div[n - 1] - atoi(&tmp[j]);
	 		div[n] = result;
                        n++;
                }
                i++;
        }
}
/*void solve_mult(char *tmp,int *mult){
	int i = 0;
	int *_tmp = malloc(80);
	int result;
	int n = 0;
	while(tmp[i] != 0){
		if(tmp[i] == '*'){
			int j = i - 1;
			int __tmp[2];
			while(tmp[j] == ' ')
				j--;
			__tmp[0] = tmp[j];
			j = i + 1;
			while(tmp[j] == ' ')
				j++;
			__tmp[1] = tmp[j];
			int result = __tmp[1] * __tmp[2];
			mult[n] = result;
		}
		i++;
	}
}
void solve_mult(const char *tmp,int *mult){
        int i = 0;
        int *_tmp = malloc(80);
        int result;
        int n = 0;
        while(tmp[i] != 0){
                if(tmp[i] == '*'){
                        int j = i - 1;
                        int *__tmp = malloc(3);
                        while(tmp[j] == ' ')
                                j--;
                        ///printf("%d\n",j);
                        __tmp[0] = atoi(&tmp[j]);
                        j = i + 1;
                        while(tmp[j] == ' ')
                                j++;
                        __tmp[1] = atoi(&tmp[j]);
                        int result = __tmp[1] * __tmp[0];
                        mult[n] = result;
                }
                i++;
        }
}
*/
/*Finds stat ( and end )*/
int *find_params(const char *buf){
	int n = 0;
	int *store = malloc(80);
	store = {-1};
	int i = 0;
	while(buf[i] != 0){
		if(buf[i] == '(' || buf[i] == ')'){
			store[n] = i;
			n++;
		}
		i++;
	}
	return store;
}
/*Solves for ()*/
void solve_out_1(const char *buf,int *ret){
	int i = 0;
	int isp = 0;
	int *tmp = malloc(80);
	int *tmpopp = malloc(80);
	int n = 0;
	int m = 0;	
	int start = 0;
	int tmpres;
	char *_buf = malloc(80);
	int *par = find_params(buf);
	while(par[n] != -1){
		int j  = par[n] + 1, k = par[n + 1] + 1;
		while(j < k){
			if(buf[j] == '*' && start == 0){
				int l = j;
				while(buf[l] == ' ')
					l--;
				int tmp1 = atoi(&buf[l]);
				l = j;
				while(buf[l] == ' ')
					l++;
				int tmp2 = atoi(&buf[l]);
				tmpres = tmp1 * tmp2;
				start = 1;
			}
			else if(buf[j] == '/' && start == 0){
				int l = j;
				while(buf[l] == ' ')
					l--;
				int tmp1 = atoi(&buf[l]);
				l = j;
				while(buf[l] == ' ')
					l++;
				int tmp2 = atoi(&buf[l]);
				tmpres = tmp1 / tmp2;
				start = 1;
			}
			else if(buf[j] == '+' && start == 0){
				int l = j;
				while(buf[l] == ' ')
					l--;
				int tmp1 = atoi(&buf[l]);
				l = j;
				while(buf[l] == ' ')
					l++;
				int tmp2 = atoi(&buf[l]);
				tmpres = tmp1 + tmp2;
				start = 1;
			}
			else if(buf[j] == '-' && start == 0){
				int l = j;
				while(buf[l] == ' ')
					l--;
				int tmp1 = atoi(&buf[l]);
				l = j;
				while(buf[l] == ' ')
					l++;
				int tmp2 = atoi(&buf[l]);
				tmpres = tmp1 * tmp2;
				start = 1;
			}
			else if(buf[j] == '*'){
				int l = j;
				while(buf[l] == ' ')
					l++;
				tmpres*=atoi(&buf[l]);
			}
			else if(buf[j] == '/'){
				int l = j;
				while(buf[l] == ' ')
					l++;
				tmpres/=atoi(&buf[l]);
			}
			else if(buf[j] == '+'){
				int l = j;
				while(buf[l] == ' ')
					l++;
				tmpres+=atoi(&buf[l]);
			}else if(buf[j] == '-'){
				int l = j;
				while(buf[l] == ' ')
					l++;
				tmpres-=atoi(&buf[l]);
			}

			j++;
		}
		n+=2;
	}
}
void calculator_process(const char *buf){
	int *out_1 = malloc(1024);
	solve_out_1(buf,out_1);
	int *out_2 = malloc(1024);
	solve_out_2(buf,out_2);
	int *in = malloc(1024);
	solve_in(buf,in);

	/*int i = 0;
	int *args = malloc(80);
	int *opp = malloc(80);
	int n = 0;
	int j = 0;
	char *_buf = malloc(80);
	int *tmpholding = malloc(80);
	int *tmpopp = malloc(80);
	int tmpcalc;
	int isp = 0;
	int l = 0;
	int m = 0;
	while(buf[i] != 0){
		if(isp == 1){
			if(buf[i] == ')'){
				for(int k = 0;k < l;k++,m+=2){
					int opp = tmpopp[k];
					int _args[2] = {tmpholding[m],tmpholding[m + 1]};
					if(opp[n] == OPP_ADD){
						args[n] = _args[0] + _args[1];
						n++;
					}
				}
			}
		}
		else if(buf[i] == '+'){
			opp[n] = OPP_ADD;
			args[n] = atoi(_buf);
			j = 0;
			_buf = malloc(80);
			n++;
		}
		else if(buf[i] == '-'){
			opp[n] = OPP_SUB;
			args[n] = atoi(_buf);
			j = 0;
			_buf = malloc(80);
			n++;
		}
		else if(buf[i] == '*' || buf[i] == 'x' || buf[i] == 'X'){
			opp[n] = OPP_MULT;
			args[n] = atoi(_buf);
			j = 0;
			_buf = malloc(80);
			n++;
		}
		else if(buf[i] == '/' || buf[i] == '\\'){
			opp[n] = OPP_DIV;
			args[n] = atoi(_buf);
			j = 0;
			_buf = malloc(80);
			n++;
		}
		else if(buf[i] == '!'){
			opp[n] = OPP_FACT;
			args[n] = atoi(_buf);
			j = 0;
			_buf = malloc(80);
			n++;
		}
		else if(buf[i] == '^'){
			opp[n] = OPP_EXP;
			args[n] = atoi(_buf);
			j = 0;
			_buf = malloc(80);
			n++;
		}
		else if(buf[i] == '('){
			isp = 1;
			tmpholding = malloc(80);
			tmpopp = malloc(80);
		}

		else if(is_int(buf[i])){
			strcat(_buf,&buf[i]);
		}
		else{
			kprintf("Invalid character: %c\n",buf[i]);
		}
		i++;
	}*/
	
}
