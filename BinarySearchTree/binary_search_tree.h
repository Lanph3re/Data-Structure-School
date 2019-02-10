#pragma once
typedef struct TreeNode {
	int data;
	struct TreeNode *left;
	struct TreeNode *right;
} TreeNode;

TreeNode *CreateNode(int item);
TreeNode *BST_insertion(TreeNode *root, TreeNode *newNode);
TreeNode *BST_search(TreeNode *root, int key);
TreeNode *BST_deletion(TreeNode *root, int key);