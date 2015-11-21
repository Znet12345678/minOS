#include <string.h>
#include <kernel/types.h>
ksize_t strlen(const char *str){
	ksize_t ret = 0;
	while(str[ret] != '\0')
		ret++;
	return ret;
}
