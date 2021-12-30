#include <iostream>
#include <windows.h>

int main() {
	while (true) {
		for (int i = 0; i <= 260; i++) {
			int num = GetAsyncKeyState(i);
			if (num != 0) { std::cout << i << " [" << num << "]" << std::endl; }
		}
	}
	
	return 0;
}
