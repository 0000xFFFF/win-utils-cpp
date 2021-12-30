#include <windows.h>
#include <stdio.h>

int main(int argc, char* argv[]){
	if (argc == 1) { fprintf(stderr, "USAGE: %s <filename.jpg/jpeg/png/...>\n", argv[0]); return 1; }
	if ((SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, argv[1], SPIF_UPDATEINIFILE | SPIF_SENDCHANGE)) == 0) {
		printf("ERROR: failed\n");
		return 1;
	}
	
	printf("SUCCESS!\n");
	return 0;
}

