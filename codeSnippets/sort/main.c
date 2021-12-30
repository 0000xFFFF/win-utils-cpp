#include <stdio.h>

// Function to swap elements 
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to print the elements of an array
void printArray(int array[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", array[i]);
    printf("\n");
}

// bubble sort function
void bubbleSort(int array[], int n) {
    for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			printf("i=%d -- j=%d\ta[j]=%d > a[j+1]=%d\t", i, j, array[j], array[j+1]);
            if (array[j] > array[j + 1]) {
				swap(&array[j], &array[j + 1]);
				printf(" -- swap --> ");
				printArray(array, n);
			}
			else {
				printf("\n");
			}
		}
	}
}

// Main Function
int main() {
    int array[] = { 89, 32, 20, 113, -15 };
    int size = sizeof(array) / sizeof(array[0]);
	printf("Size: %d\n", size);
	printf("Array: ");
	printArray(array, size);
    bubbleSort(array, size);
    printf("Sorted array: ");
    printArray(array, size);
    return 0;
}