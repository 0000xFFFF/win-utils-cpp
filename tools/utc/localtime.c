#include <stdio.h>
#include <time.h>

int main() {
	char buff[64] = {0};
	time_t rawtime;
	time(&rawtime);
	struct tm* info = localtime(&rawtime);
	strftime(buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", info);
	printf("%s\n", buff);
	return 0;
}