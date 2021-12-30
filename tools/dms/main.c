#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <conio.h>

bool quit = false;
int timeoutSeconds = 0;

void* newThread(void* arg) {
	time_t* to = arg;
	while (1) {
		int a = getch();
		if (quit) { return NULL; }
		if (a == 113) { quit = true; return NULL; } // 133 = 'q'
		printf("\n");
		*to = time(0) + timeoutSeconds;
	}
	return NULL;
}

int main(int argc, char** argv) {

	if (argc < 3) {
		fprintf(stderr, "USAGE: %s <time (s)> <command>\n", argv[0]);
		return 1;
	}
	
	timeoutSeconds = atoi(argv[1]);
	time_t ct = time(0);
	time_t to = ct + timeoutSeconds;

	pthread_t thread_id;
	pthread_create(&thread_id, NULL, newThread, (void*)&to);

	printf("Countdown started... Press 'q' to quit, any other key to reset countdown...\n");

	while (1) {
		ct = time(0);
		
		printf("\rcountdown: %ld (%d)               ", to-ct, timeoutSeconds);
		if (ct >= to) { break; }
		if (quit) { return 0; }
	}
	printf("\n");

	quit = true;
	
	char* programToStart = argv[2];

	// start program
	printf("> %s\n", programToStart);
	system(programToStart);
	
	return 0;
}
