#include <stdio.h>
#include <stdlib.h>
/*Finds stat ( and end )*/
int *find_params(const char *buf){
	int n = 0;
	int *store = malloc(80);
	//store = (int[80]){[0 ... 79]-1};
	//printf("%d\n",store[10]);
	int i = 0;
	while(buf[i] != 0){
		if(buf[i] == '(' || buf[i] == ')'){
			store[n] = ++i;
			//printf("%d\n",i);
			n++;
		}
		i++;
	}
	return store;
}
void nextopp(const char *buf,int n){
	int i = n;
	while(buf[i] != 0){
		if(buf[i] == '+')
			return OPP_ADD;
		else if(buf[i] == '-')
			return OPP_ADD;
		else if(buf[i] === '*')
			return OPP_MULT;
		else if(buf[i] == '/')
			return OPP_DIV;
		i++;
	}
	return 0;
}
int solve(const char *buf){
	int i = 0;
	int ret;
	int start;
	while(i < strlen(buf)){
		if(buf[i] == '*' && start == 0){
			int j = i - 1;
			while(buf[j] == ' ')
				j--;
			int val1 = atoi(&buf[j]);
			int j = i + 1;
			while(buf[j] == ' ')
				j++;
			int val2 = atoi(&buf[j]);
			ret = val1 * val2;
			start = 1;
		}
		
		i++;
	}
}
void solve_out_1(const char *buf,int *ret){
	int i = 0;
	int n = 0;
	int *buf = malloc(1024);
	int j;
	int *opp = malloc(1024);
	int save;
	char *buf[80] {[0 ... 79]malloc(1024)};
	while(i < strlen(buf)){

	}
}
void __solve_out_1(const char *buf,int *ret){
	int i = 0;
	int n = 0;
	int *buf = malloc(1024);
	int tmpval;
	int j;
	int *opp = malloc(1024);
	int save;
	while(i < strlen(buf)){
		while(1 && j != strlen(buf) && j != 0){
			if(buf[i] == '*'){
				j = i - 1;
				while(buf[j] == ' ')
					j--;
				tmpval = atoi(&buf[j]);
				int i = 0;
				int mode = OPP_MULT;
				while(1 && j != strlen(buf)){
					while(buf[j] == ' ')
						j++;
					if(buf[j] == '+' || buf[j] == '-'){
						if(buf[j] == '+')
							mode = OPP_ADD;
						else
							mode = OPP_SUB;
						break;
					}
					else if(buf[j] == '/')
						mode = OPP_DIV;
					else if(buf[j] == '*')
						mode = OPP_MULT;
					//else if(buf[j] == ' ')
					//	int skip;
					else if(mode == OPP_DIV)
						tmpval/=atoi(&buf[j]);
					else if(mode == OPP_MULT)
						tmpval*=atoi(&buf[j]);
				}
				if(mode == OPP_ADD){
					if(nextopp(buf,j) == OPP_MULT || nextopp(buf,j) == OPP_DIV){
						
					}
					else{
						save = tmpval;
						
					}
				}
				//"1 * 2 + 2 * 3 *4 + 3"
			}
			i++;
		}
	}
}
/*Solves for ()*/
void _solve_out_1(const char *buf,int *ret){
	int i = 0;
	int isp = 0;
	int *tmp = malloc(80);
	int *tmpopp = malloc(80);
	int n = 0;
	int m = 0;	
	int start = 0;
	int tmpres;
	int r = 0;
	char *_buf = malloc(80);
	int *par = malloc(80);
	//par = (int[80]){[0 ... 79]-1};
	par = find_params(buf);
	//printf("%d\n",par[2]);
	//int p = 0;
	//while(par[p] != -1){
	//	printf("%d\n",par[p]);
	//	p++;
	//}
	int *arr1 = malloc(80);
	int *arr2 = malloc(80);
	int a = 0;
	while(par[n] != 0){
		//printf("[%d] [%d] [%d] [%d]\n",par[n],par[n + 1],n,par[2]);
		int j = par[n];
		int prev;
		int k = par[n + 1] - 1;
		while(j < k){
			//printf(".\n");
			//printf("%c\n",buf[j]);
			if(buf[j] == '*' && start == 0){
				int l = j - 1;
				//printf(".\n");
				while(buf[l] == ' '){
					//printf(".");
					l--;
				}//printf("%c\n",buf[l]);
				int tmp1 = atoi(&buf[l]);
				l = j + 1;
				while(buf[l] == ' ')
					l++;
				int tmp2 = atoi(&buf[l]);
				tmpres += tmp1 * tmp2;
				//prev = tmpres;
				//printf("%d %d\n",tmp1,tmp2);
				start = 1;
			}
			else if(buf[j] == '/' && start == 0){
				int l = j - 1;
				while(buf[l] == ' ')
					l--;
				int tmp1 = atoi(&buf[l]);
				l = j + 1;
				while(buf[l] == ' ')
					l++;
				int tmp2 = atoi(&buf[l]);
				tmpres += tmp1 / tmp2;
				//prev = tmpres;
				start = 1;
			}
			else if(buf[j] == '+' || buf[j] == '-'){
				start = 0;
				arr1[a] = j;
			1	a++;
			}
			/*else if(buf[j] == '+' && start == 0){
				int l = j - 1;
				while(buf[l] == ' ')
					l--;
				int tmp1 = atoi(&buf[l]);
				l = j + 1;
				while(buf[l] == ' ')
					l++;
				int tmp2 = atoi(&buf[l]);
				tmpres = tmp1 + tmp2;
				start = 1;
			}
			else if(buf[j] == '-' && start == 0){
				int l = j - 1;
				while(buf[l] == ' ')
					l--;
				int tmp1 = atoi(&buf[l]);
				l = j + 1;
				while(buf[l] == ' ')
					l++;
				int tmp2 = atoi(&buf[l]);
				tmpres = tmp1 * tmp2;
				start = 1;
			}*/
			else if(buf[j] == '*'){
				int l = j + 1;
				while(buf[l] == ' ')
					l++;
				tmpres*=atoi(&buf[l]);
			}
			else if(buf[j] == '/'){
				int l = j + 1;
				while(buf[l] == ' ')
					l++;
				tmpres/=atoi(&buf[l]);
			}
			/*else if(buf[j] == '+'){
				int l = j + 1;
				while(buf[l] == ' ')
					l++;
				tmpres+=atoi(&buf[l]);
			}else if(buf[j] == '-'){
				int l = j + 1;
				while(buf[l] == ' ')
					l++;
				tmpres-=atoi(&buf[l]);
			}*/
			//printf(".");
			//printf("[%d] [%d] [%d] [%d]\n",par[n],par[n + 1],n,par[2]);
			j++;
		}
		//printf("[%d] [%d] [%d] [%d]\n",par[n],par[n + 1],n,par[2]);
		j = par[n];

                k = par[n + 1] - 1;
		
		start = 0;
 /*               while(j < k){
			if(buf[j] == '+' && start == 0){
                                int l = j - 1;
                                while(buf[l] == ' ')
                                        l--;
                                int tmp1 = atoi(&buf[l]);
                                l = j + 1;
                                while(buf[l] == ' ')
                                        l++;
                                int tmp2 = atoi(&buf[l]);
                                tmpres += tmp1 + tmp2;
                                start = 1;
                        }
                        else if(buf[j] == '-' && start == 0){
                                int l = j - 1;
                                while(buf[l] == ' ')
                                        l--;
                                int tmp1 = atoi(&buf[l]);
                                l = j + 1;
                                while(buf[l] == ' ')
                                        l++;
                                int tmp2 = atoi(&buf[l]);
                                tmpres -= tmp1 - tmp2;
                                start = 1;
                        }
			else if(buf[j] == '+'){
                                int l = j + 1;
                                while(buf[l] == ' ')
                                        l++;
                                tmpres+=atoi(&buf[l]);
                        }else if(buf[j] == '-'){
                                int l = j + 1;
                                while(buf[l] == ' ')
                                        l++;
                                tmpres-=atoi(&buf[l]);
                        }
			j++;
		}*/
		
		ret[r] = tmpres;
		r++;
		//printf("%d\n",tmpres);
		tmpres = 0;
		n+=2;
		//printf("[%d] [%d] [%d] [%d]\n",par[n],par[n + 1],n,par[2]);
	}
}
int main(){
	const char *meh = "(5 * 2 - 1 * 2)";
	int *res = malloc(80);
	res = (int[80]){[0 ... 79]-1};
	solve_out_1(meh,res);
	printf("%d\n",res[0]);
}
