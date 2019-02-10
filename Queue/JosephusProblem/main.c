#include<stdio.h>
#include<stdlib.h>
#include"queueADT.h"

int main() {
	Queue *queue = CreateQueue();
	QueueNode *temp = NULL;
	int n, k;
	
	printf("number of people : ");
	scanf("%d", &n);
	printf("k : ");
	scanf("%d", &k);

	for (int i = 0; i < n; i++) {
		Enqueue(queue, i+1);
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < k-1; j++) {
			queue->front = queue->front->nextPtr;
			queue->rear = queue->rear->nextPtr;
		}

		printf("%d ", Dequeue(queue));
	}
	puts("");

	return;
}