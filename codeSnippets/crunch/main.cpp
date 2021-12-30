#include <iostream>
#include <string>

const char ascii_upper[26] = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G',
	'H', 'I', 'J', 'K', 'L', 'M', 'N',
	'O', 'P', 'Q', 'R', 'S', 'T', 'U',
	'V', 'W', 'X', 'Y', 'Z'
};

const char ascii_lower[26] = {
	'a', 'b', 'c', 'd', 'e', 'f', 'g',
	'h', 'i', 'j', 'k', 'l', 'm', 'n',
	'o', 'p', 'q', 'r', 's', 't', 'u',
	'v', 'w', 'x', 'y', 'z'
};

void Generate(unsigned int length, std::string s) {
	//print when length has been reached
	if(length == 0) { std::cout << s << "\n"; return; }
	
	for(unsigned int i = 0; i < 26; i++) { 
	
		std::string appended = s + ascii_lower[i];
		Generate(length - 1, appended);
	}
}

int main() {
	
	Generate(6, "");
	
	return 0;
}
