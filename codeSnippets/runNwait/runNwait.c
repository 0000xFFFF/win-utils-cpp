int runNwait(char* path) {
	PROCESS_INFORMATION pi;
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
	STARTUPINFO si;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	if (!CreateProcess(NULL, path, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi)) { return 0; }
	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
	return 1;
}