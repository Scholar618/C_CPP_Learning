/*
	计算字符串长度
*/
#include <stdlib.h> 

size_t strlen(const char *str) {
	int length = 0;
	while (*str++ != '\0') {
		length++;
	}
	return length;
}

