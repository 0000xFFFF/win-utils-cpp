#include <windows.h>
#include <conio.h>

int main() {
	while (getch() != 113) { Sleep(10); }
	return 0;
}