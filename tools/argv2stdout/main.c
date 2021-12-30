#include <stdio.h>
#include <conio.h>
int main(int argc, char* argv[]) {
	if (argc == 1) { return 1; }
	for (int i = 1; i < argc; i++)
	{ printf("%s\n", argv[i]); }
	getch();
	return 0;
}
