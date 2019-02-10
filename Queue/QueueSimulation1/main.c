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
		if (walker->patience >= hotdogs) { // �������� ���� ���� ����������� ����� ������ �������� data���� patience�� �ٲ�
			hotdogs++;
		}
		walker = walker->nextPtr;
	}

	printf("I sell %d hotdogs\n", hotdogs);

	return;
}