#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cry.h"

int main(int argc, char** argv) {
	
	if (argc < 4) {
		printf("USAGE: %s <mode> <shift> <input file> <output file>\n", argv[0]);
		printf(" mode: 1 = +, 2 = -\n");
		return 1;
	}
	
	int mode = atoi(argv[1]);
	switch (mode) {
		case 1: break;
		case 2: break;
		default: fprintf(stderr, "ERROR: invalid input mode\n"); return 1; break;
	}
	int shift = atoi(argv[2]);
	
	char* filei = argv[3];
	char* fileo = argv[4];
	cry_file(filei, fileo, mode, shift);
	
    return 0;
}