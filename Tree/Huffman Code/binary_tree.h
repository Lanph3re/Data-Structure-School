#pragma once
#define TRUE 1
#define FALSE 0
typedef char* Element;
typedef int Boolean;
typedef struct treeNode {
	char ch;
	int count;
	struct treeNode *lch, *rch;
} TreeNode;

TreeNode *CreateTree(char ch, int count, TreeNode *left, TreeNode *right);
Boolean IsEmpty(TreeNode *tree);
TreeNode *LeftTree(TreeNode *tree);
TreeNode *RightTree(TreeNode *tree);
Element TreeData(TreeNode *tree);
void DestroyTree(TreeNode *tree);
void traversal_preorder(TreeNode *tree);
void traversal_inorder(TreeNode *tree);
void traversal_postorder(TreeNode *tree);
void huffRead(char **table, TreeNode *tree, Boolean init);