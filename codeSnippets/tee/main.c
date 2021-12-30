#include <stdio.h>

#include "tee.h"

int main() {
	
	tee_init("app.log");
	
	int a = 3;
	tee("this will be writen to a file\n");
	tee("here's a number: %d\n", a); // use it like printf
	
	tee_shutdown();
	
	return 0;
}
