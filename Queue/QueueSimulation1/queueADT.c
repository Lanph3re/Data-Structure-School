#include <stdlib.h>
#include "queueADT.h"

Queue *CreateQueue() {
	Queue *queue = (Queue *)malloc(sizeof(Queue));

	if (queue == NULL) return NULL;

	queue->count = 0;
	queue->front = queue->rear = NULL;

	return  queue;
}

void Enqueue(Queue *Queue, int data) {
	QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
	
	if (newNode == NULL) return;
	
	newNode->patience = data;
	newNode->nextPtr = NULL;

	if (Queue->count <= 0) {
		Queue->front = Queue->rear = newNode;
	}
	else {
		Queue->rear->nextPtr = newNode;
		Queue->rear = newNode;
	}

	Queue->count++;
}

int Dequeue(Queue *Queue) {
	QueueNode *front = NULL;
	int data = 0;

	if (Queue->count <= 0) return 0;

	front = Queue->front;
	data = front->patience;
	
	if (Queue->count == 1) {
		Queue->front = Queue->rear = NULL;
	}
	else {
		Queue->front = front->nextPtr;
	}

	free(front);
	Queue->count--;

	return data;
}

int QueueFront(Queue *Queue) {
	return Queue->front->patience;
}

void DestroyQueue(Queue *Queue) {
	QueueNode *cur, *next;

	for (cur = Queue->front; cur != NULL;cur=next) {
		next = cur->nextPtr;
		free(cur);
	}

	free(Queue);
}