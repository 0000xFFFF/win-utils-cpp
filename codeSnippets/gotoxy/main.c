#include <stdio.h>
#include <stdlib.h>
#include "gotoxy.h"

int main() {
	
	system("cls");
	
	int count1 = 0, count2 = 10, count3 = 30;
	while (1) {
		count1++;
		count2 += 5;
		count3 += 40;
		printf("count1 : %d\n", count1);
		printf("count2 : %d\n", count2);
		printf("count3 : %d\n", count3);
		printf("count3 : %d\n", count3);
		printf("count3 : %d\n", count3);
		printf("count3 : %d\n", count3);
		printf("count3 : %d\n", count3);
		printf("count3 : %d\n", count3);
		printf("count3 : %d\n", count3);
		gotoxy(0, 0);
	}
	
	return 0;
}
