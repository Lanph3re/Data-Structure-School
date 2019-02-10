#include<stdio.h>
#include"queueADT.h"

int main(void) {
	Queue *queue = CreateQueue();
	QueueNode *walker = NULL;
	int n, temp;
	int hotdogs;

	hotdogs = 0;

	printf("number of customer : ");
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		printf("Patience of customer : ");
		scanf("%d", &temp);

		Enqueue(queue, temp);
	}

	walker = queue->front;

	while (walker != NULL) {
		if (walker->patience >= hotdogs) { // 가독성을 위해 기존 헤더구현에서 노드의 데이터 변수명을 data에서 patience로 바꿈
			hotdogs++;
		}
		walker = walker->nextPtr;
	}

	printf("I sell %d hotdogs\n", hotdogs);

	return;
}