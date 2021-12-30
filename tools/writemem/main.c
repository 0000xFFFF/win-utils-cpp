#include <stdio.h>
#include <windows.h>

int main(int argc, char* argv[]) {
	if (argc == 1) {
		fprintf(stderr, "USAGE: %s <PID> <mem_address> <value>\n", argv[0]);
		return 1;
	}
	
	DWORD pid = atoi(argv[1]);
	long int address_ = strtol(argv[2], NULL, 0);
	LPVOID address = (void*)address_;
	int newValue = atoi(argv[3]);
	
	printf("# opening pid: %ld - ...", pid);
	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	printf("\b\b\b");
	if (handle == NULL) { fprintf(stderr, "FAIL\n"); return 1; }
	printf("SUCCESS\n");
	
	printf("# writing: %d -> %p (%ld) - ...", newValue, address, address_);
	BOOL ret = WriteProcessMemory(handle, address, &newValue, sizeof(newValue), 0);
	printf("\b\b\b");
	if (!ret) { fprintf(stderr, "FAIL\n"); return 1; }
	printf("SUCCESS");
	
	return 0;
}