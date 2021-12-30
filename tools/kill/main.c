#include <stdio.h>
#include <ctype.h>
#include <windows.h>
#include <tlhelp32.h>
#include <shlwapi.h>

BOOL TerminateProcessEx(DWORD dwProcessId, UINT uExitCode) {
	HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, dwProcessId);
	if (hProcess == NULL) { return FALSE; }
	BOOL result = TerminateProcess(hProcess, uExitCode);
	CloseHandle(hProcess);
	return result;
}

int kill(char* procNameOrId) {
	
	DWORD pID = -1;
	
	// check if input is number (id) or process name
	BOOL isID = TRUE;
	for (unsigned int i = 0; i < strlen(procNameOrId); i++) {
		if (!isdigit(procNameOrId[i])) { isID = FALSE; }
	}
	if (isID) { pID = atoi(procNameOrId); }
	
	HANDLE thSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (thSnapShot == INVALID_HANDLE_VALUE) {
		fprintf(stderr, "failed to get snapshot handle\n");
		return 0;
	} 
	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(PROCESSENTRY32);
	BOOL retval = Process32First(thSnapShot, &pe);
	int result = -1;
	int killed = 0;
	int failed = 0;
	while (retval) {
		if ((isID ? (pe.th32ProcessID == pID) : (StrStrI(pe.szExeFile, procNameOrId) != NULL))) {
			printf("> %ld\t: %s", pe.th32ProcessID, pe.szExeFile);
			if (TerminateProcessEx(pe.th32ProcessID, 0)) {
				killed++;
				printf(" - SUCCESS\n");
			}
			else {
				failed++;
				printf(" - FAILED\n");
			}
		}
		
		retval = Process32Next(thSnapShot, &pe);
	}
	
	CloseHandle(thSnapShot);
	
	printf("\n");
	printf("killed: %d\n", killed);
	printf("failed: %d\n", failed);
	
	return result;
}

int main(int argc, char* argv[]) {
	
	if (argc == 1) {
		printf("USAGE: %s <procNameOrId>\n", argv[0]);
		return 1;
	}
	
	kill(argv[1]);
	return 0;
}
