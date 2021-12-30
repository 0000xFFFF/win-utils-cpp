#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	
	if (argc == 1) {
		fprintf(stderr, "USAGE: %s <command> <cmd2> <...>\n", argv[0]);
		return 1;
	}
	
	while (1) {
		for (int i = 1; i < argc; i++) {
			system(argv[i]);
		}
	}
	return 0;
}
