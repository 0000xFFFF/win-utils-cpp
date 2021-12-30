#include <stdio.h>

int main(int argc, char** argv) {
	
	
	for (int i = 1; i < argc; i++) {
		fclose(fopen(argv[i], "a"));
	}
	
	return 0;
}
