#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"HeapADT.h"

#define N 20

int main() {
	int count, temp;
	int *arr = (int *)malloc(sizeof(int)*N);
	Heap *heap = heapCreate(N, MAX);

	srand(time(NULL));

	puts("/* Insert */");
	for (int i = 0; i < N; i++) {
		temp = rand() % 10000;
		arr[i] = temp;
		heapInsert(heap, temp);
		printf("%d : ", heapCount(heap));
		heapPrint(heap);
		puts("");
	}

	puts("\n/* Delete */");
	count = heap->count;
	for (int i = 0; i < count; i++) {
		if (heapEmpty(heap))
			puts("Empty");
		else {
			heapDelete(heap);
			if (heapCount(heap)) {
				printf("%d : ", heapCount(heap));
				heapPrint(heap);
				puts("");
			}
			else {
				puts("Empty");
			}
		}
	}

	puts("\n/* HeapSort */");
	
	printf("Before : ");
	for (int i = 0; i < N; i++)
		printf("%d ", arr[i]);
	
	heapSort(arr, N);

	printf("\nAfter : ");
	for (int i = 0; i < N; i++)
		printf("%d ", arr[i]);

	puts("");

	return;
}