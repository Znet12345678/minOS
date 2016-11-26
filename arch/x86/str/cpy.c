/*
*Some c library functions for math and strings
*(c) 2015 Zachary James Schlotman
*/
#include <kernel/types.h>
#include <stdlib.h>
#include <string.h>
void kstrcpy(char *dest,const char *src){
	int i = strlen(dest);
	int i1 = 0;
	while(i < (strlen(dest) + strlen(src))){
		dest[i] = src[i1];
		i++;
		i1++;
	}
}
void kstrcat(char *dest,const char *src){
	kstrcpy(&dest[strlen(dest)],src);
}
struct div{
	int quot;
	int rem;
};
struct div *div(int num, int denom)
{
	int r;
	int k;
	int j;
	k = num/denom;
	j = num % denom;
	if(num >=0 && j < 0){
		k++;
		j -= denom;
	}
	struct div *ret = malloc(sizeof(struct div *));
	ret->quot = k;
	ret->rem = j;
	return ret;

}
struct ldiv{
	long quot;
	long rem;
};
struct ldiv *ldiv(long num,long denom){
	struct ldiv *ret = malloc(sizeof(struct ldiv *));
	ret->quot = num / denom;
	ret->rem = num % denom;
	if(num >= 0 && ret->rem < 0){
		ret->quot++;
		ret->rem -=denom;
	}
	return ret;
};
char *strncpy(char *dest,const char *src,size_t n){
	int i = 0;
	int i1 = strlen(dest);
	while(i < n){
		dest[i1] = src[i];
		i++;
	}
}
void *memcpy(void *dest,const void *src,ksize_t s){
	unsigned char *d = (unsigned char *)dest;
	const unsigned char *sr = (const unsigned char *)src;
	ksize_t s1;
	while( s1 < s){
		d[s1] = sr[s1];
		s1++;
	}
	return d;
}
void* memmove(void* dstptr, const void* srcptr, ksize_t size)
{
	unsigned char* dst = (unsigned char*) dstptr;
	const unsigned char* src = (const unsigned char*) srcptr;
	if ( dst < src )
		for ( ksize_t i = 0; i < size; i++ )
			dst[i] = src[i];
	else
		for ( ksize_t i = size; i != 0; i-- )
			dst[i-1] = src[i-1];
	return dstptr;
}
void *memset(void* bufptr, int value, ksize_t size)
{
	unsigned char* buf = (unsigned char*) bufptr;
	for ( ksize_t i = 0; i < size; i++ )
		buf[i] = (unsigned char) value;
	return bufptr;
}
