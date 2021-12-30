#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
	
	// if args use args
	if (argc < 2) {
		printf("USAGE: %s <string>\n", argv[0]);
		return 0;
	}
	
	const char* str = argv[1];
	
	printf("char VAR[] = { ");
	size_t l = strlen(str);
	for (size_t i = 0; i < l; i++) {
		printf("HIDE_LETTER('%c'), ", str[i]);
	}
	printf("'\\0' };\n");
	
	return 0;
}
