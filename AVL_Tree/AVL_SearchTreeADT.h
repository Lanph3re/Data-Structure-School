#pragma once
typedef struct TreeNode{
	int data;
	int bal;
	struct TreeNode *left;
	struct TreeNode *right;
} TreeNode;

typedef struct {
	int count;
	TreeNode *root;
} AVL_Tree;

AVL_Tree *AVL_Create();
TreeNode *AVL_CreateNode(int data);
TreeNode *AVL_RotateLeft(TreeNode *root);
TreeNode *AVL_RotateRight(TreeNode *root);
TreeNode *_AVL_Insert(TreeNode *root, TreeNode *newNode, int *taller);
void AVL_Insert(AVL_Tree *tree, TreeNode *newNode);
TreeNode *_AVL_delLeftBal(TreeNode *root, int *shorter);
TreeNode *_AVL_delRightBal(TreeNode *root, int *shorter);
TreeNode *_AVL_Delete(TreeNode *root, int key, int *shorter, int *result);
int AVL_Delete(AVL_Tree *tree, int key);
TreeNode *_AVL_Search(TreeNode *root, int key);
TreeNode *AVL_Search(AVL_Tree *tree, int key);
int AVL_count(AVL_Tree *tree);
int AVL_Empty(AVL_Tree *tree);
void _AVL_PrintTree(TreeNode *root);
void AVL_PrintTree(AVL_Tree *tree);