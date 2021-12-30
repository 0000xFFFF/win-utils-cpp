#include <stdio.h>
#include <ctype.h>

int main(int argc, char** argv) {
	
	if (argc < 2) { printf("USAGE: %s <file>\n", argv[0]); return 1; }
	
	FILE* f = fopen(argv[1], "rb");
	if (!f) { fprintf(stderr, "failed to open file\n"); return 1; }
	
	int c;
	int p = 0;
	while ((c = fgetc(f)) != EOF) {
		if (isprint(c))
		//if (c >= 32 && c <= 127)
		{ printf("%c", c); p++; continue; }
		if (c == 0 && p != 0) { p = 0; printf("\n"); continue; }
	}
	
	fclose(f);
	
	return 0;
}
