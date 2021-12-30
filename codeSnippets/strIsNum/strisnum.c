#include <stdio.h>
#include <ctype.h>
#include <string.h>

int strIsNum(const char* str) {
	int ret = 1;
	for (unsigned int i = 0; i < strlen(str); i++) {
		if (!isdigit(str[i])) { ret = 0; }
	}
	return ret;
}