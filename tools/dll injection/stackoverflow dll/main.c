#include "main.h"

DWORD WINAPI HackThread(HMODULE hModule) {
	while (TRUE) { CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, NULL); }
	return 0;
}

BOOL WINAPI DllMain(HINSTANCE hModule, DWORD fdwReason, LPVOID lpReserved) {
	if (fdwReason == DLL_PROCESS_ATTACH) { CloseHandle(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, NULL)); }
	return 1;
}

//MessageBox(NULL, "DLL_PROCESS_ATTACH", "DLL_PROCESS_ATTACH", MB_ICONERROR | MB_OK);