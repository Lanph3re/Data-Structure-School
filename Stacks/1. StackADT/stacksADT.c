#include<stdlib.h>
#include"stacksADT.h"

/* allocate memories for stack */
Stack *CreateStack() {
	Stack *head = (Stack *)malloc(sizeof(Stack));
	head->count = 0;
	head->top = NULL;

	return head;
}

/* push a element into stack */
void Push(Stack *head, int data) {
	StackNode *new = (StackNode *)malloc(sizeof(StackNode));
	StackNode *temp = NULL;

	new->data = data;
	temp = head->top;
	head->top = new;
	new->next = temp;
	head->count++;
}

/* return the element of the stack top and pop it from the stack*/
int Pop(Stack *head) {
	StackNode *ptr;
	int data;

	if (head->count == 0) return 0;
	else {
		head->count--;
		ptr = head->top;
		head->top = ptr->next;
		data = ptr->data;
		free(ptr);
		return data;
	}
}

/* return the element of stack top */
int StackTop(Stack *head) {
	if (head->count == 0) return 0;
	else {
		return head->top->data;
	}
}

/* free all stack nodes and stack head */
void DestroyStack(Stack *head) {
	StackNode *ptr = NULL;

	for (int i = 0; i < head->count; i++) {
		ptr = head->top;
		head->top = ptr->next;
		free(ptr);
	}

	free(head);
}

/* concatenate stack2 to stack 1 */
void CatStack(Stack *head_1, Stack *head_2) {
	StackNode *temp_ = head_1->top;
	StackNode *temp__ = head_2->top;

	while (temp__->next != NULL) {
		temp__ = temp__->next;
	}

	temp__->next = temp_;
	head_1->top = head_2->top;
	head_1->count += head_2->count;
	free(head_2);
}