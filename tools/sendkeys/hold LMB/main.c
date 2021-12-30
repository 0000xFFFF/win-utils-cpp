#include <stdio.h>
#include <windows.h>

BOOL g_Exit = FALSE;
DWORD WINAPI end() {
	while(!g_Exit) {
		Sleep(50);
		if (GetAsyncKeyState(VK_END) != 0) {
			printf("# [END] pressed, exiting...\n");
			g_Exit = TRUE;
			break;
		}
	}
	return 0;
}

int main() {
	
	if (!CreateThread(NULL, 0, end, NULL, 0, NULL))
	{ fprintf(stderr, "ERROR: failed to create END thread\n"); return 1; }
	
	printf("# press the [END] key on your keyboard to stop holding LMB...\n");
	printf("# holding LMB in 3...\n"); Sleep(1000);
	printf("# holding LMB in 2...\n"); Sleep(1000);
	printf("# holding LMB in 1...\n"); Sleep(1000);
	
	INPUT input; ZeroMemory(&input, sizeof(input));
	input.type = INPUT_MOUSE;
	
	printf("# holding...\n");
	input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	SendInput(1, &input, sizeof(INPUT));
	printf("# hold\n");
	
	// the most laziest way (code) to wait for something o____o
	while (!g_Exit) { Sleep(100); }
	
	printf("# releasing...\n");
	input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput(1, &input, sizeof(INPUT));
	printf("# released\n");
	
	printf("# quit\n");
	return 0;
}




















