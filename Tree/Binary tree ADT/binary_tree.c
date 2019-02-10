#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"binary_tree.h"

TreeNode *CreateTree(Element item, TreeNode *left, TreeNode *right) {
	TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));

	if (newNode == NULL) return NULL;

	newNode->data = (char *)malloc(strlen(item) + 1);
	strcpy(newNode->data, item);

	newNode->lch = left;
	newNode->rch = right;

	return newNode;
}

void insertNode(Element item, TreeNode *tree) {
	if (strcmp(tree->data, item) >= 0) {
		if (tree->lch == NULL) {
			TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));

			if (newNode == NULL) return;

			newNode->data = (char *)malloc(sizeof(item) + 1);
			strcpy(newNode->data, item);
			newNode->lch = NULL;
			newNode->rch = NULL;

			tree->lch = newNode;
			
			return;
		}
		else {
			insertNode(item, tree->lch);
		}
	}
	else {
		if (tree->rch == NULL) {
			TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));

			if (newNode == NULL) return;

			newNode->data = (char *)malloc(sizeof(item) + 1);
			strcpy(newNode->data, item);
			newNode->lch = NULL;
			newNode->rch = NULL;

			tree->rch = newNode;

			return;
		}
		else {
			insertNode(item, tree->rch);
		}
	}
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

	return tree->data;
}

void DestroyTree(TreeNode *tree) {
	if (tree == NULL) return;

	if (tree->lch) DestroyTree(tree->lch);
	if (tree->rch) DestroyTree(tree->rch);

	free(tree);
}

void traversal_preorder(TreeNode *tree) {
	if (tree == NULL) return;

	printf("%s ", tree->data);
	traversal_preorder(tree->lch);
	traversal_preorder(tree->rch);
}

void traversal_inorder(TreeNode *tree) {
	if (tree == NULL) return;

	traversal_inorder(tree->lch);
	printf("%s ", tree->data);
	traversal_inorder(tree->rch);
}

void traversal_postorder(TreeNode *tree) {
	if (tree == NULL) return;

	traversal_postorder(tree->lch);
	traversal_postorder(tree->rch);
	printf("%s ", tree->data);
}