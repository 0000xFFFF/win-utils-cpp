#include <iostream>
#include <thread>
#include <windows.h>

int main(int argc, char* argv[]) {
	
	int num_threads = 10;
	std::thread t[num_threads];
	
	//Launch a group of threads
	for (int i = 0; i < num_threads; ++i) {
		t[i] = std::thread([]() { MessageBox(NULL, "test", "test", MB_OK | MB_ICONINFORMATION); });
		t[i].detach();
		Sleep(100);
	}
	
	Sleep(1000);
	
	return 0;
}