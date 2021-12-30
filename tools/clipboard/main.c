#include <stdio.h>
#include <conio.h>
#include <windows.h>

int main() {
	if (!OpenClipboard(NULL)) { fprintf(stderr, "ERROR: can't open clipboard\n"); return 1; } 
	
	HANDLE hData = GetClipboardData(CF_TEXT);
	if (hData == NULL) { fprintf(stderr, "ERROR: can't get clipboard data\n"); return 2; }
	
	// Lock the handle to get the actual text pointer
	char* text = (char*)(GlobalLock(hData));
	if (text == NULL) { fprintf(stderr, "ERROR: text is null\n"); return 3; }
	GlobalUnlock(hData);
	CloseClipboard();
	
	printf("%s\n", text);
	return 0;
}
