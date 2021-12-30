#include <stdio.h>
#include <windows.h>

int main(int argc, char** argv) {
	
	if (argc == 1) { return 1; }
	
	char buff[MAX_PATH] = {0};
	GetFullPathName(argv[1], MAX_PATH, buff, NULL);
	printf("RT: %s\n", buff);
	
	return 0;
}
