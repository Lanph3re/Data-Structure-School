#include<stdlib.h>
#include<stdio.h>
#include"listADT.h"

List *createList() {
	List *newList = (List *)malloc(sizeof(List));
	
	if (newList == NULL) return NULL;

	newList->count = 0;
	newList->head = NULL;
	newList->tail = NULL;

	return newList;
}

void destroyList(List *list) {
	ListNode *temp;

	while (list->head != NULL) { // free all the nodes in the list.
		temp = list->head;
		list->head = list->head->nextPtr;
		free(temp);
	}

	free(list);
	
	return;
}

void printList(List *list) {
	ListNode *temp = list->head;

	while (temp != NULL) {
		printf("%d --> ", temp->data);
		temp = temp->nextPtr;
	}

	puts("NULL");

	return;
}

Element front(List *list) {
	return list->head->data;
}

Element back(List *list) {
	return list->tail->data;
}

void pushFront(List *list, Element data) {
	ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));

	if (newNode == NULL) return;

	newNode->data = data;
	newNode->nextPtr = list->head;
	list->head = newNode;

	if (list->count <= 0) list->tail = newNode;
	list->count++;
	
	return;
}

void pushBack(List *list, Element data) {
	ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));

	if (newNode == NULL) return;

	newNode->data = data;
	newNode->nextPtr = NULL;
	if (list->count <= 0) list->head = newNode;
	if(list->count>0) list->tail->nextPtr = newNode;
	list->tail = newNode;
	list->count++;

	return;
}

Element popFront(List *list) {
	ListNode *front = list->head;
	Element data;

	if (list->count <= 0) return 0;
	
	data = front->data;
	list->head = front->nextPtr;
	free(front);
	list->count--;

	if (list->count <= 0) list->tail = NULL; // when the list get empty after pop, set the tail value to NULL.

	return data;
}

Element popBack(List *list) {
	ListNode *temp = list->head;
	ListNode *back = list->tail;
	Element data;

	if (list->count <= 0) return 0;
	
	list->count--;
	data = back->data;

	if (list->count <= 0) { // when the list gets empty after pop, set both head and tail value to NULL.
		list->head = list->tail = NULL;
	}
	else {
		while (temp->nextPtr != list->tail) { // search for the node which is the previous node of the node pointed by tail.
			temp = temp->nextPtr;
		}

		temp->nextPtr = NULL;
		list->tail = temp;
	}

	free(back);

	return data;
}

int listCount(List *list) {
	return list->count;
}

int isEmptyList(List *list) {
	return list->count <= 0;
}

void insert(List *list, Element data, int position) {
	if (position > list->count || position < 0) return; // when the value of the position parameter is out of range of the current list.

	ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
	ListNode *temp = NULL;

	if (newNode == NULL) return;

	newNode->data = data;
	list->count++;

	if (position == 0) { // when the new node is the first node in the list.
		newNode->nextPtr = list->head;
		list->head = newNode;

		if (list->count == 1) list->tail = newNode; // when the new node is the only node in the list, set the tail value to newNode.

		return;
	}
	else { // when the new node is in the middle(last) of the list.
		temp = list->head;

		for (int i = 0; i < position - 1;i++) { // search for the position to be inserted.
			temp = temp->nextPtr;
		}

		newNode->nextPtr = temp->nextPtr;
		temp->nextPtr = newNode;

		if (position == list->count - 1) list->tail = newNode; // when the new node is the last node in the list, set the tail value to newNode.

		return;
	}
}

void erase(List *list, int position) {
	if (list->count <= 0 || position > list->count - 1 || position < 0) return; // when the value of the position parameter is out of range of the current list.

	ListNode *temp = NULL;
	ListNode *erased = NULL;

	list->count--;

	if (position == 0) { // when the erased node is the first node in the list.
		erased = list->head;
		list->head = erased->nextPtr;

		if (list->count == 0) list->tail = NULL; // when the list gets empty after the node gets erased, set the tail value to NULL.
		free(temp);
		return;
	}
	else { // when the erased node is in the middle(last) of the list.
		temp = list->head;

		for (int i = 0; i < position - 1;i++) { // search for the position to be erased.
			temp = temp->nextPtr;
		}

		erased = temp->nextPtr;
		temp->nextPtr = erased->nextPtr;

		if (list->tail == erased) list->tail = temp; // when the erased node was the last node of the list, set the tail pointer to the previous node of the erased node.

		free(erased);

		return;
	}
}

void removeElements(List *list, Element value) {
	int cur_pos = 0;
	ListNode *temp = list->head;

	if (list->count <= 0) return;

	while (temp != NULL) {
		if (temp->data == value) {
			temp = temp->nextPtr;
			erase(list, cur_pos);
			continue;
		}
		else {
			cur_pos++;
			temp = temp->nextPtr;
		}
	}
}

void unique(List *list) {
	Element *uniques = (Element *)malloc(sizeof(Element)*list->count); // the array for incongruent values.
	ListNode *temp = list->head;
	int num = 0; // the number of incongruent values.
	int isUnique;

	if (list->count <= 1) return;

	while (temp != NULL) { // find unique values.
		isUnique = 1;

		for (int i = 0; i < num; i++) {
			if (*(uniques + i) == temp->data) {
				isUnique = 0;
				break;
			}
		}

		if (isUnique) {
			*(uniques + num) = temp->data;
			num++;
		}

		temp = temp->nextPtr;
	}

	while (list->head != NULL) { // free all the nodes in the list.
		temp = list->head;
		list->head = list->head->nextPtr;
		free(temp);
	}
	list->tail = NULL;
	list->count = 0;

	for (int i = 0; i < num; i++) {
		pushBack(list, *(uniques + i));
	}

	return;
}

void reverse(List *list) {
	if (list->count <= 1) return;
	int count = list->count;
	ListNode *temp = list->head;
	ListNode **nodes = (ListNode **)malloc(sizeof(ListNode *) * count);

	for (int i = 0; i < count; i++) { // save the node pointers
		*(nodes + i) = temp;
		temp = temp->nextPtr;
	}

	list->head = *(nodes + count - 1);

	temp = list->head;

	for (int i = count - 2; i >= 0; i--) {
		temp->nextPtr = *(nodes + i);
		temp = temp->nextPtr;
	}

	list->tail = temp;
	temp->nextPtr = NULL;

	return;
}

void exchange(List *list, int position_1, int position_2) {
	if(list->count<=1 || position_1 == position_2 || position_1 < 0 || position_1 > list->count-1 || position_2 < 0 || position_2 > list->count - 1) return;

	ListNode *ptr_1 = list->head;
	ListNode *ptr_2 = list->head;
	Element temp;

	for (int i = 0; i < position_1; i++) {
		ptr_1 = ptr_1->nextPtr;
	}

	for (int i = 0; i < position_2; i++) {
		ptr_2 = ptr_2->nextPtr;
	}

	temp = ptr_1->data;
	ptr_1->data = ptr_2->data;
	ptr_2->data = temp;

	return;
}

void *merge(List *list_1, List *list_2) { // merge list_2 into list_1
	list_1->count += list_2->count;
	list_1->tail->nextPtr = list_2->head;
	list_2->tail = list_2->tail;

	list_2->count = 0;
	list_2->head = list_2->tail = NULL;
	
	free(list_2);
}

int *partition(int *arr, int *low, int *high) {
	int temp;
	int pivot = *(low);
	int *left = low;
	int *right = high;

	while (left < right) {
		while (*left <= pivot && left<high) left++;

		while (*right >= pivot && right>low) right--;

		if (left < right) {
			temp = *left;
			*left = *right;
			*right = temp;
		}
	}
	temp = *right;
	*right = pivot;
	*low = temp;

	return right;
}

void quickSort(int *arr, int *low, int *high) {
	if (low < high) {
		int *pivot = partition(arr, low, high);
		quickSort(arr, low, pivot - 1);
		quickSort(arr, pivot + 1, high);
	}
}

void sort(List *list) {
	int num = list->count;
	Element *data = (Element *)malloc(sizeof(Element)*num);
	ListNode *temp = list->head;

	for (int i = 0; i < num; i++) {
		*(data + i) = temp->data;
		temp = temp->nextPtr;
	}

	quickSort(data, data, data + num - 1);
	temp = list->head;

	for (int i = 0; i < num; i++) {
		temp->data = *(data + i);
		temp = temp->nextPtr;
	}

	return;
}

