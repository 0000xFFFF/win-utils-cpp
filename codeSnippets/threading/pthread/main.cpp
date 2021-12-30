#include <stdio.h>
#include <pthread.h>

#define MAXCOUNT 10000

void* newThread(void* arg) {
	for (int i = 0; i <= MAXCOUNT; i++) { printf("from main: %d\n", i); }
	return NULL;
}

int main() {
	pthread_t thread_id;
	pthread_create(&thread_id, NULL, newThread, (void*)0);
	for (int i = 0; i <= MAXCOUNT; i++) { printf("from main: %d\n", i); }
	return 0;
}