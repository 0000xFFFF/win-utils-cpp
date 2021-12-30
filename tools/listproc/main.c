#include <stdio.h>
#include <ctype.h>
#include <windows.h>
#include <tlhelp32.h>
#include <shlwapi.h>

int listproc(const char* procNameOrId) {
	
	// check if input is number (id) or process name
	DWORD pID = -1;
	BOOL isID = TRUE;
	if (procNameOrId != NULL) {
		for (size_t i = 0; i < strlen(procNameOrId); i++) {
			if (!isdigit(procNameOrId[i])) { isID = FALSE; }
		}
		if (isID) { pID = atoi(procNameOrId); }
	}
	
	
	HANDLE thSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (thSnapShot == INVALID_HANDLE_VALUE) {
		fprintf(stderr, "failed to get snapshot handle\n");
		return 1;
	} 
	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(PROCESSENTRY32);
	BOOL retval = Process32First(thSnapShot, &pe);
	while (retval) {
		retval = Process32Next(thSnapShot, &pe);
		if (procNameOrId != NULL && !(isID ? (pe.th32ProcessID == pID) : (StrStrI(pe.szExeFile, procNameOrId) != NULL))) { continue; }
		printf("%ld\t: %s\n", pe.th32ProcessID, pe.szExeFile);
	}
	CloseHandle(thSnapShot);
	
	return 0;
}


int main(int argc, char* argv[]) {
	
	listproc(argc >= 2 ? argv[1] : NULL);
	
	return 0;
}
