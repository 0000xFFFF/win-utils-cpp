#include <stdio.h>
#include <windows.h>

#define MAXCOUNT 10000

DWORD WINAPI ThreadFunc(void* data) {
	for (int i = 0; i <= MAXCOUNT; i++) { printf("from thread: %d\n", i); }
	return 0;
}

int main() {
	HANDLE thread = CreateThread(NULL, 0, ThreadFunc, NULL, 0, NULL);
	if (thread) {
		for (int i = 0; i <= MAXCOUNT; i++) { printf("from main: %d\n", i); }
	}
}