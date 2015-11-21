#include <kernel/types.h>
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
