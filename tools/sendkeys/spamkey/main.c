#include <stdio.h>
#include <windows.h>

#include "sendkeys.h"

BOOL g_Exit = FALSE;

DWORD WINAPI endSpam() {
	while(!g_Exit) {
		if (GetAsyncKeyState(VK_END) != 0) {
			g_Exit = TRUE;
			printf("# [END] pressed, exiting...\n");
			break;
		}
		Sleep(50);
	}
	return 0;
}

int main(int argc, char* argv[]) {
	
	// arg check
	if (argc < 3) {
		printf("USAGE: %s <delay (ms)> <stringToSpam>\n", argv[0]);
		printf(sendkeys_help());
		return 1;
	}
	
	// create spam thread
	if (!CreateThread(NULL, 0, endSpam, NULL, 0, NULL))
	{ fprintf(stderr, "ERROR: failed to create spam click thread\n"); return 1; }
	
	// countdown
	printf("# press the [END] key on your keyboard to stop the spam...\n");
	printf("# starting spam in 3...\n"); Sleep(1000);
	printf("# starting spam in 2...\n"); Sleep(1000);
	printf("# starting spam in 1...\n"); Sleep(1000);
	
	// main loop
	int sleep = atoi(argv[1]);
	while (!g_Exit) { sendkeys(argv[2]); Sleep(sleep); }
	
	return 0;
}




















