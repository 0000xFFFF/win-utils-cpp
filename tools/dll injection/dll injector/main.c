#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include <shlwapi.h>
#include <tlhelp32.h>
#include <unistd.h>
#include <windows.h>

BOOL injectDll(DWORD pID, const char* dllPath) {
	
	// get the dll's full path name
	char buf[MAX_PATH] = {0};
	GetFullPathName(dllPath, MAX_PATH, buf, 0);
	printf("using dll: \"%s\"\n", buf);
	
	// check if file exists
	if(access(dllPath, F_OK)) {
		fprintf(stderr, "file not found. aborted.\n");
		fprintf(stderr, "injection failed\n");
		return FALSE;
	}
	
	printf("injecting dll...\n");
	
	HANDLE Proc = OpenProcess(MAXIMUM_ALLOWED, FALSE, pID);
	if (!Proc) {
		fprintf(stderr, "error: OpenProcess() failed: %lu\n", GetLastError());
		return FALSE;
	} 
	
	LPVOID LoadLibAddy = (LPVOID)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
	
	// Allocate space in the process for our DLL
	LPVOID RemoteString = (LPVOID)VirtualAllocEx(Proc, 0, strlen(buf), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	
	// Write the string name of our DLL in the memory allocated 
	if (!WriteProcessMemory(Proc, (LPVOID)RemoteString, buf, strlen(buf), 0)) { fprintf(stderr, "error: WriteProcessMemory() failed: %lu\n", GetLastError()); return FALSE; }
	
	// Load our DLL
	HANDLE RemoteThread = CreateRemoteThread(Proc, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibAddy, (LPVOID)RemoteString, 0, 0);
	
	printf("dll injected\n");
	
	CloseHandle(RemoteThread);
	CloseHandle(Proc);
	
	return TRUE;
}

int main(int argc, char* argv[]) {
	
	if (argc != 3) {
		fprintf(stderr, "USAGE: %s <process name | id> <dll>\n", argv[0]);
		return 1;
	}
	
	DWORD pID = 0;
	const char* input = argv[1];
	
	// check if input is number (id) or process name
	BOOL isID = TRUE;
	for (size_t i = 0; i < strlen(input); i++) {
		if (!isdigit(input[i])) { isID = FALSE; }
	}
	
	if (isID) {
		pID = atoi(input);
		printf("using id: %lu\n", pID);
		injectDll(pID, argv[2]);
	}
	else {
		// retrieve process ID
		HANDLE thSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (thSnapShot == INVALID_HANDLE_VALUE) { fprintf(stderr, "error: unable to create toolhelp snapshot\n"); return FALSE; } 
	
		PROCESSENTRY32 pe;
		pe.dwSize = sizeof(PROCESSENTRY32);
		
		printf("searching for process: \"%s\"\n", input);
		
		// go through processes and match the name
		BOOL retval = Process32First(thSnapShot, &pe);
		while (retval) {
			if (StrStrI(pe.szExeFile, input)) {
				printf("found process id: %lu (%s)\n", pe.th32ProcessID, pe.szExeFile);
				pID = pe.th32ProcessID;
				injectDll(pID, argv[2]);
			}
			retval = Process32Next(thSnapShot, &pe);
		}
		
		if (pID == 0) {
			fprintf(stderr, "error: process with name: \"%s\" not found\n", input);
			return 1;
		}
	}
	
	return 0; 
} 

