#include <stdio.h>
#include <windows.h>   // WinApi header

int main() {
	
	// get console handle
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	// get color for backup
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	
	#define nc 16
	int newLines[nc] = { 15, 31, 47, 63, 79, 95, 111, 127, 143, 159, 175, 191, 207, 223, 239, 254 };
	
	// print all colors
	for(int k = 1; k < 255; k++) {
		// set color
		SetConsoleTextAttribute(hConsole, k);
		printf("%3d", k);
		
		int nl = 0;
		for (int i = 0; i < nc; i++) {
			if (newLines[i] == k) { nl = 1; break; }
		}
		
		// reset color
		SetConsoleTextAttribute(hConsole, csbi.wAttributes);
		printf(nl ? "\n" : " ");
	}
	
	return 0;
}