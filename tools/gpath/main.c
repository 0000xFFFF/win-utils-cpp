#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	char* str = getenv("PATH");
	for (unsigned int i = 0; i < strlen(str); i++) {
		if (str[i] == ';') { str[i] = '\n'; }
	}
	printf("%s\n", str);
	return 0;
}
