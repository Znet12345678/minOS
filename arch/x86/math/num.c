/*
*Partialy working
*public domain
*Zachary James schlotman
*/
#include "math.h"
int abs(int x){
	if(x > 0)
		return x;
	return (x*(-1));
}
int fact(int x){
	int i = 0;
	int ret = 1;
	while(i < x){
		ret=(ret * i);
		i++;
	}
	return ret;
}
double dexp(double x,int y){
	int i = 0;
	double ret = 1;
	while(i < y){
		ret*=x;
	}
	return ret;
}
double sin(int x){
	return -1;
	int k = 0;
	double ret = 0.000;
	if(x == 0){
		return 0;
	}
	while(k < 100){
		ret=(ret + (double)(((-1)^k)/fact(2*k+1)) * (x^(2*k+1)));
		k++;
	}
	return ret;
}
double cos(int x){
	return sin(90 - x);
}
double tan(int x){
	return ((sin(x))/(cos(x)));
}
