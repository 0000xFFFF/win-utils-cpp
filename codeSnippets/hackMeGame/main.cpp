#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <conio.h>

int main(int argc, char* argv[]){
	
	bool gameOver = false;
	
	int time = 0;
	int health = 1000;
	int money = 20;
	int money_time = 0;
	
	const char* str = "this is a const string.";
	
	while (!gameOver) {
		
		std::cout << &gameOver << "  > gameOver..: " << gameOver << std::endl;
		std::cout << &time     << "  > time......: " << time     << std::endl;
		std::cout << &health   << "  > health....: " << health   << std::endl;
		std::cout << &money    << "  > money.....: " << money    << std::endl;
		std::cout << &str      << "  > str.......: " << str      << std::endl;
		
		time++;
		money_time++;
		if (time % 2 == 0) { health++; }
		if (money_time >= 20) { money += 10; money_time = 0; }
		
		std::cout << std::endl << std::endl;
		std::cout << ":: press any key to pass time..." << std::endl;
		getch();
		system("cls");
	}
	
	return 0;
}
