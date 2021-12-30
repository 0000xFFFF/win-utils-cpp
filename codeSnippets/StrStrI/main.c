#include <stdio.h>
#include <windows.h>
#include <shlwapi.h>

int main(int argc, char** argv) {
	
	if (argc < 3) { return 1; }
	
	LPSTR d = StrStrI(argv[1], argv[2]);
	printf("RET: %s\n", (char*)d);
	printf("NUM: %d\n", (int)d);
	
	
	return 0;
}
