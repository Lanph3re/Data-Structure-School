#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"binary_tree.h"

TreeNode *CreateTree(char ch, int count, TreeNode *left, TreeNode *right) {
	TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));

	if (newNode == NULL) return NULL;

	newNode->ch = ch;
	newNode->count = count;

	newNode->lch = left;
	newNode->rch = right;

	return newNode;
}

Boolean IsEmpty(TreeNode *tree) {
	return (tree == NULL);
}

TreeNode *LeftTree(TreeNode *tree) {
	if (IsEmpty(tree)) return NULL;

	return tree->lch;
}

TreeNode *RightTree(TreeNode *tree) {
	if (IsEmpty(tree)) return NULL;

	return tree->rch;
}

Element TreeData(TreeNode *tree) {
	if (IsEmpty(tree)) return NULL;

	return tree->count;
}

void DestroyTree(TreeNode *tree) {
	if (tree == NULL) return;

	if (tree->lch) DestroyTree(tree->lch);
	if (tree->rch) DestroyTree(tree->rch);

	free(tree);
}

void traversal_preorder(TreeNode *tree) {
	if (tree == NULL) return;

	printf("%d ", tree->count);
	traversal_preorder(tree->lch);
	traversal_preorder(tree->rch);
}

void traversal_inorder(TreeNode *tree) {
	if (tree == NULL) return;

	traversal_inorder(tree->lch);
	printf("%d ", tree->count);
	traversal_inorder(tree->rch);
}

void traversal_postorder(TreeNode *tree) {
	if (tree == NULL) return;

	traversal_postorder(tree->lch);
	traversal_postorder(tree->rch);
	printf("%d ", tree->count);
}

void huffRead(char **table, TreeNode *tree, Boolean init) {
	static char arr[100];
	if (tree == NULL) return;
	if (init == TRUE) arr[0] = 0;
	
	strcat(arr, "0");
	huffRead(table, tree->lch, FALSE);
	arr[strlen(arr) - 1] = 0;

	if (tree->ch != -1) {
		printf("%c : %s\n", tree->ch, arr);
		*(table +tree->ch) = (char *)malloc(strlen(arr) + 1);
		strcpy(*(table + tree->ch), arr);
	}

	strcat(arr, "1");
	huffRead(table, tree->rch, FALSE);
	arr[strlen(arr) - 1] = 0;
}