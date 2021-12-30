#include <stdio.h>
#include <windows.h>

int SPAM_DELAY = 3;

int gl_status1 = 0;
int gl_status2 = 0;

HHOOK mouseHook;
LRESULT __stdcall MouseHookCallback(int nCode, WPARAM wParam, LPARAM lParam) {
	KBDLLHOOKSTRUCT* key = (KBDLLHOOKSTRUCT*)lParam;
	if (key != NULL) {
		switch (key->flags) {
			case 131072: gl_status1 = wParam; return 1; break;
			case 65536:  gl_status2 = wParam; return 1; break;
		}
	}
	return CallNextHookEx(mouseHook, nCode, wParam, lParam);
}

void send_vk_mouse(DWORD flags) {
	INPUT input;
	ZeroMemory(&input, sizeof(input));
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = flags;
	SendInput(1, &input, sizeof(INPUT));
}

BOOL isSpamThreadRunning = FALSE;
DWORD WINAPI SpamThread() {
	isSpamThreadRunning = TRUE;
	int x = 0;
	int y = 0;
	while (isSpamThreadRunning) {
		// down = 523, up = 524
		if      (gl_status1 == 523) { x++; printf("\rsideButton1: %d", x); send_vk_mouse(MOUSEEVENTF_LEFTDOWN);  send_vk_mouse(MOUSEEVENTF_LEFTUP);  }
		else if (gl_status1 == 524) { x = 0; printf("\n"); gl_status1 = 0; }
		if      (gl_status2 == 523) { y++; printf("\rsideButton2: %d", y); send_vk_mouse(MOUSEEVENTF_RIGHTDOWN); send_vk_mouse(MOUSEEVENTF_RIGHTUP); }
		else if (gl_status2 == 524) { y = 0; printf("\n"); gl_status2 = 0; }
		Sleep(SPAM_DELAY);
	}
	return 0;
}

int main(int argc, char** argv) {
    
	if (argc == 1) {
		fprintf(stderr, "USAGE: %s <delay>\n", argv[0]);
		return 1;
	}
	
	SPAM_DELAY = atoi(argv[1]);
	
	// hook
	if (!(mouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseHookCallback, NULL, 0))) { fprintf(stderr, "ERROR: failed to install mouse hook\n"); }
	
	// create spam thread
	HANDLE thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)SpamThread, NULL, 0, NULL);
	if (!thread) { fprintf(stderr, "ERROR: failed to create spam click thread\n"); }
	
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) { TranslateMessage(&msg); DispatchMessage(&msg); }
	
	isSpamThreadRunning = FALSE;    // stop spam thread
	UnhookWindowsHookEx(mouseHook); // unhook
	return msg.wParam;
}