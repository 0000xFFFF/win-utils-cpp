#include <stdio.h>
#include <windows.h>

int main(int argc, char* argv[]){
	// SND_ASYNC     - play in the background
	// SND_FILENAME  - play and pause
	
	if (argc == 1) {
		fprintf(stderr, "USAGE: %s <WavSoundFile>", argv[0]);
		return 0;
	}
	
	PlaySound(argv[1], NULL, SND_FILENAME);
	
    return 0;
}