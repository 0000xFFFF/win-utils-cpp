#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	size_t BIG = 536870912;
	int count = 0;
	size_t total = 0;
	while (1) {
		int* p = malloc(BIG);
		if (p == NULL) {
			BIG = BIG / 2;
			if (BIG < 512) { break; }
			continue;
		}
		
		memset(p, 0, BIG);
		count++;
		total += BIG;
		printf("%d +%d = %d\n", count, BIG, total);
	}
	
	getchar();
	return 0;
}
