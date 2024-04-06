#include <stdio.h>

void printArr(int* arr, int size) {
	printf("arr: ");
	for (int i = 0; i < size; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void sortArr(int* arr, int size) {
	for (int x = 0; x < size; x++) {
		
		// find max
		int* max = &arr[0];
		for (int y = 0; y < size-x; y++) {
			if (arr[y] > *max) { max = &arr[y]; }
		}
		
		// swap max with last
		int tmp = *max;
		*max = arr[size-1-x];
		arr[size-1-x] = tmp;
	}
	
}

#define ARR_SIZE(x) (sizeof(x) / sizeof(x[0]))

void psp(int* arr, int size) {
	printArr(arr, size);
	sortArr (arr, size);
	printArr(arr, size);
}

int main() {
	
	
	int arr1[] = { 10, 3, 4, 5, 6, 7, 12, 13, 56, 1 };
	psp(arr1, ARR_SIZE(arr1));
	
	int arr2[] = { 2, 3, 1, 9, 3, 2, 2, 6, 7, 10, 100, 13, 19, 20 };
	psp(arr2, ARR_SIZE(arr2));
	
	
	return 0;
}
