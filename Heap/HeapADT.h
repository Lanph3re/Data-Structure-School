#pragma once
#define MAX 1
#define MIN 0

typedef int Type;

typedef struct {
	Type type;
	int size;
	int count;
	int *arr;
} Heap;

Heap *heapCreate(int size, Type type);
void heapInsert(Heap *heap, int data);
int heapDelete(Heap *heap);
int heapCount(Heap *heap);
int heapFull(Heap *heap);
int heapEmpty(Heap *heap);
void *heapDestroy(Heap *heap);
void heapPrint(Heap *heap);
void heapSort(int *arr, int size);
