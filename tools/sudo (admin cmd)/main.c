#include <stdio.h>
#include <windows.h>
#include <direct.h>

//#define MY_ICON 101

int main(int argc, char* argv[]) {
	
	// change dir to system dir
	//chdir("C:\\Windows\\System32");
	
	for (int i = 1; i < argc; i++) {
		
		//run args as a command
		system(argv[i]);
		
		//find exit in args and exit exe
		if (strcmp(argv[i], "exit")) {
			return 0;
		}
	}
	
	WinExec("cmd.exe /K", SW_SHOW);
	
	return 0;
}




