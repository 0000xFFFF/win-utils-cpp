#include <stdio.h>
#include <windows.h>

#include "sendkeys.h"

int main(int argc, char* argv[]) {
	
	if (argc < 2) {
		printf("USAGE: %s <stringToSend>\n", argv[0]);
		printf("%s\n", sendkeys_help());
		return 1;
	}
	
	sendkeys(argv[1]);
	
	return 0;
}






















