#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cry.h"

int main(int argc, char** argv) {
	
	if (argc < 3) {
		printf("USAGE: %s <mode> <shift> <str>\n", argv[0]);
		printf(" mode: 1 = [+37], 2 = [-37]\n");
		return 1;
	}
	
	int mode = atoi(argv[1]);
	switch (mode) {
		case 1: break;
		case 2: break;
		default: fprintf(stderr, "ERROR: invalid input mode\n"); return 1; break;
	}
	int shift = atoi(argv[2]);
	
	char* str = argv[3];
	int strl = strlen(str);
	char str2[strl+1];
	memset(str2, 0, strl+1);
	cry_str(str, str2, mode, shift);
	int str2l = strlen(str2);
	printf("STR1[%d]: %s\n", strl, str);
	printf("STR2[%d]: %s\n", str2l, str2);
	
	return 0;
}