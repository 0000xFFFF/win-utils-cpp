#include <stdio.h>
#include <windows.h>
#include "res.h"

// save file to disk from resource
int main(int argc, char* argv[]){
	HRSRC myResource = FindResource(NULL, MAKEINTRESOURCE(IDR_RCDATA1), RT_RCDATA);
	unsigned int myResourceSize = SizeofResource(NULL, myResource);
	HGLOBAL myResourceData = LoadResource(NULL, myResource);
	void* pMyExecutable = LockResource(myResourceData);
	FILE* f = fopen("new.txt", "wb");
	fwrite((char*)pMyExecutable, sizeof(BYTE), myResourceSize, f);
	fclose(f);
	return 0;
}
