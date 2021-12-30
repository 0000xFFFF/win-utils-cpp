#include "main.h"


DWORD WINAPI HackThread(HMODULE hModule) {
	
	AllocConsole();
	FILE* f;
	freopen("CONOUT$", "w", stdout);
	
	while (TRUE) {
		Sleep(10);
		// //uncomment to end console without ending the process with the END key
		// if (GetAsyncKeyState(VK_END) & 1) { break; }
	}
	
	//cleanup & eject
	fclose(f);
	FreeConsole();
	FreeLibraryAndExitThread(hModule, 0);
	
	return 0;
}

BOOL WINAPI DllMain(HINSTANCE hModule, DWORD fdwReason, LPVOID lpReserved) {
	if (fdwReason == DLL_PROCESS_ATTACH) { CloseHandle(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, NULL)); }
	return 1;
}

//MessageBox(NULL, "DLL_PROCESS_ATTACH", "DLL_PROCESS_ATTACH", MB_ICONERROR | MB_OK);