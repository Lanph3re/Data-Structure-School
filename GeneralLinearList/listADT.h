#pragma once

typedef int Element;

typedef struct listNode {
	Element data;
	struct listNode *nextPtr;
} ListNode;

typedef struct {
	int count;
	ListNode *head;
	ListNode *tail;
} List;

List *createList();
void destroyList(List *list);
void printList(List *list);
Element front(List *list);
Element back(List *list);
void pushFront(List *list, Element data);
void pushBack(List *list, Element data);
Element popFront(List *list);
Element popBack(List *list);
int listCount(List *list);
int isEmptyList(List *list);
void insert(List *list, Element data, int position);
void erase(List *list, int position);
void removeElements(List *list, Element value);
void unique(List *list);
void reverse(List *list);
void exchange(List *list, int position_1, int position_2);
void *merge(List *list_1, List *list_2);
int *partition(int *arr, int *low, int *high); // used for sort()
void quickSort(int *arr, int *low, int *high); // used for sort()
void sort(List *list);


