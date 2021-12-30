#include <stdio.h>
#include <stdlib.h>
#include "strisnum.h"

int main(int argc, char** argv) {
	
	if (argc == 1) { fprintf(stderr, "USAGE: %s <input>\n", argv[0]); return 1; }
	
	
	int r = strIsNum(argv[1]);
	printf("is num: %s\n", r ? "TRUE" : "FALSE");
	
	
	return 0;
}
