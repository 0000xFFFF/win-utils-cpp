#include <iostream>
#include <fstream>

// ofstream: Stream class to write on files
// ifstream: Stream class to read from files
// fstream: Stream class to both read and write from/to files.

int main() {
	std::ofstream file;
	file.open("file.txt");
	file << "DATA";
	file.close();
	
	return 0;
}