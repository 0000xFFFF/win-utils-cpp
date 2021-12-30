#include <iostream>
#include <windows.h>

int main() {
    std::cout << "Loading... " << std::flush;
	
    while (true) {
		
        std::cout << "\b" << "\\" << std::flush; Sleep(100);
        std::cout << "\b" << "|"  << std::flush; Sleep(100);
        std::cout << "\b" << "/"  << std::flush; Sleep(100);
        std::cout << "\b" << "-"  << std::flush; Sleep(100);
    }
}