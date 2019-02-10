#include"HeapADT.h"
#include<stdlib.h>

Heap *heapCreate(int size, Type type) { // type == 1 : MAX Heap, type == 0 : MIN Heap
	Heap *newHeap = (Heap *)malloc(sizeof(Heap));

	if (newHeap == NULL) return NULL;

	newHeap->type = type;
	newHeap->count = 0;
	newHeap->arr = (int *)malloc(sizeof(int)*size);
	newHeap->size = size;

	for (int i = 0; i < size; i++) { // initialize the heap with -1
		*(newHeap->arr + i) = -1;
	}

	if(newHeap->arr == NULL) {
		free(newHeap);
		return NULL;
	}

	return newHeap;
}

void heapInsert(Heap *heap, int data) {
	int i;
	int parent;
	int temp;

	if (heap->count == heap->size) return; // heap is full

	for (i = 0; heap->arr[i] != -1; i++); // find empty slot in arr

	*(heap->arr + i) = data;

	if (heap->count == 0) {
		heap->count++;
		return;
	}
	else { // check whether the heap needs to be rearranged		
		while (1) {
			parent = (i % 2 == 1) ? (i - 1) / 2 : (i - 2) / 2; // find the parent's index;

			if (heap->type == MAX) { // Max Heap Routine
				if (*(heap->arr + i) > *(heap->arr + parent)) {
					temp = *(heap->arr + i);
					*(heap->arr + i) = *(heap->arr + parent);
					*(heap->arr + parent) = temp;
				}

				if (parent == 0)
					break;
				else
					i = parent;
			}
			else { // Min Heap Routine
				if (*(heap->arr + i) < *(heap->arr + parent)) {
					temp = *(heap->arr + i);
					*(heap->arr + i) = *(heap->arr + parent);
					*(heap->arr + parent) = temp;
				}

				if (parent == 0)
					break;
				else
					i = parent;
			}
		} // end while(1)

		heap->count++;
		return;
	} // end else
}

int heapDelete(Heap *heap) {
	int heapVal = heap->arr[0];
	int size = heap->size;
	int cur_idx, next_idx;
	int temp;
	
	heap->arr[0] = heap->arr[heap->count - 1]; // bring the last element in heap to the first element.
	heap->arr[heap->count - 1] = -1; // put -1 in the index where the last element were to indicate that the element is deleted.

	if (heap->count == 1) { // when there's one element in heap before heapDelete, no need to rearrange
		heap->count--;
		return heapVal;
	}

	cur_idx = 0;
	while (1) {
		if (2 * cur_idx + 1 > size - 1)	// indexs of two children are out of range
			break;
		else if (2 * cur_idx + 2 > size - 1) {	// only the index of left child is in range
			if (heap->arr[2 * cur_idx + 1] != -1) {
				if ((heap->type == MAX && heap->arr[2 * cur_idx + 1] > heap->arr[cur_idx]) || (heap->type == MIN && heap->arr[2 * cur_idx + 1] < heap->arr[cur_idx])) {
					temp = heap->arr[cur_idx];
					heap->arr[cur_idx] = heap->arr[2 * cur_idx + 1];
					heap->arr[2 * cur_idx + 1] = temp;
				}
			}
			break;
		}	// end else if(2 * cur_idx + 2 > size - 1)
		else {	// indexs of two children are in range
			if (heap->arr[2 * cur_idx + 1] == -1 && heap->arr[2 * cur_idx + 2] == -1)
				break;
			else if (heap->arr[2 * cur_idx + 2] == -1) {
				if ((heap->type == MAX && heap->arr[2 * cur_idx + 1] > heap->arr[cur_idx]) || (heap->type == MIN && heap->arr[2 * cur_idx + 1] < heap->arr[cur_idx])) {
					temp = heap->arr[cur_idx];
					heap->arr[cur_idx] = heap->arr[2 * cur_idx + 1];
					heap->arr[2 * cur_idx + 1] = temp;
				}
				break;
			}
			else {
				if (heap->type == MAX)
					next_idx = heap->arr[2 * cur_idx + 1] > heap->arr[2 * cur_idx + 2] ? 2 * cur_idx + 1 : 2 * cur_idx + 2;
				else
					next_idx = heap->arr[2 * cur_idx + 1] < heap->arr[2 * cur_idx + 2] ? 2 * cur_idx + 1 : 2 * cur_idx + 2;

				if ((heap->type == MAX && heap->arr[next_idx] > heap->arr[cur_idx]) || (heap->type == MIN && heap->arr[next_idx] < heap->arr[cur_idx])) {
					temp = heap->arr[cur_idx];
					heap->arr[cur_idx] = heap->arr[next_idx];
					heap->arr[next_idx] = temp;
					cur_idx = next_idx;
				}
				else
					break;
			}
		}	// end else
	}	// end while(1)

	heap->count--;
	return heapVal;
}

int heapCount(Heap *heap) {
	return heap->count;
}

int heapFull(Heap *heap) {
	return heap->count == heap->size;
}

int heapEmpty(Heap *heap) {
	return heap->count == 0;
}

void *heapDestroy(Heap *heap) {
	free(heap->arr);
	free(heap);

	return NULL;
}

void heapPrint(Heap *heap) {
	int count = heap->count;
	
	for (int i = 0; i < count; i++) {
		printf("%d ", heap->arr[i]);
	}

	return;
}

void heapSort(int *arr, int size) {
	Heap *heap = heapCreate(size, MIN);

	for (int i = 0; i < size; i++)
		heapInsert(heap, arr[i]);

	for (int i = 0; i < size; i++)
		arr[i] = heapDelete(heap);

	return;
}