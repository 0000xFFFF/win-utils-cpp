#include <stdio.h>
#include <time.h>

int main() {
	time_t now = time(0);
	struct tm* sTm = gmtime(&now);
	char buff[32] = {0};
	strftime(buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", sTm);
	printf("%s\n", buff);
	return 0;
}