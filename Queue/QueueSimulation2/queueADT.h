#pragma once

typedef struct QueueNode {
	int patience;
	struct QueueNode *nextPtr;
} QueueNode;

typedef struct {
	int count;
	QueueNode *front;
	QueueNode *rear;
} Queue;

Queue *CreateQueue(void);
void Enqueue(Queue *Queue, int data);
int Dequeue(Queue *Queue);
int QueueFront(Queue *Queue);
void DestroyQueue(Queue *Queue);