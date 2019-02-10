#pragma once

typedef struct StackNode {
	int data;
	struct StackNode *next;
} StackNode;

typedef struct {
	int count;
	StackNode *top;
} Stack;

Stack *CreateStack();
void Push(Stack *head, int data);
int Pop(Stack *head);
int StackTop(Stack *head);
void DestroyStack(Stack *head);
void CatStack(Stack *head_1, Stack *head_2);