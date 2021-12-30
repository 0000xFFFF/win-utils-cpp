#include <windows.h>

int gotoxy(int x, int y) { 
    COORD pos = {x, y};
    return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}