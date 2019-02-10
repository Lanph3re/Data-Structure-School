#include<stdio.h>
#include<stdlib.h>
#include"queueADT.h"

void ClearLine(Queue *Queue) {
	QueueNode *cleaner = Queue->front;
	QueueNode *temp = NULL;

	while (cleaner != NULL) {
		if (cleaner->patience == 0) {
			if (cleaner == Queue->front) {
				Queue->front = cleaner->nextPtr;
				free(cleaner);
				cleaner = Queue->front;
			}
			else {
				temp = Queue->front;
				while (1) {
					if (temp->nextPtr == cleaner) {
						temp->nextPtr = cleaner->nextPtr;
						free(cleaner);
						cleaner = temp->nextPtr;
						break;
					}
					else {
						temp = temp->nextPtr;
					}
				}
			}
		}
		else {
			cleaner = cleaner->nextPtr;
		}
	}
}

int main(void) {
	Queue *queue = CreateQueue();
	QueueNode *ptr = NULL;
	int n, temp;
	int hotdogs, max_hotdogs;

	hotdogs = 0;

	printf("number of customer : ");
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		printf("Patience of customer : ");
		scanf("%d", &temp);
		Enqueue(queue, temp);
	}
	
	while (1) {
		for (int i = 0; i < 2; i++) {
			if (queue->front != NULL) {
				hotdogs++;
				Dequeue(queue);
			}
			else break;
		}

		if (queue->front != NULL) {
			ptr = queue->front;
			ClearLine(queue);

			while (ptr != NULL) {
				ptr->patience--;
				ptr = ptr->nextPtr;
			}
		}
		else break;
	}

	printf("I sell %d hotdogs\n", hotdogs);

	return;
}