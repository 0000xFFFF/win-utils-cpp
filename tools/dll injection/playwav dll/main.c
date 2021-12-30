#include "main.h"

DWORD WINAPI HackThread(HMODULE hModule) {
	PlaySound("C:\\Users\\user\\Desktop\\file.wav", GetModuleHandle(NULL), SND_FILENAME | SND_SYNC);
	return 0;
}

BOOL WINAPI DllMain(HINSTANCE hModule, DWORD fdwReason, LPVOID lpReserved) {
	if (fdwReason == DLL_PROCESS_ATTACH) { CloseHandle(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, NULL)); }
	return 1;
}