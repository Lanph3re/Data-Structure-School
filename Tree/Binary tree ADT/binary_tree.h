#pragma once
#define TRUE 1
#define FALSE 0
typedef char* Element;
typedef int Boolean;
typedef struct treeNode {
	Element data;
	struct treeNode *lch, *rch;
} TreeNode;

TreeNode *CreateTree(Element item, TreeNode *left, TreeNode *right);
void insertNode(Element item, TreeNode *tree);
Boolean IsEmpty(TreeNode *tree);
TreeNode *LeftTree(TreeNode *tree);
TreeNode *RightTree(TreeNode *tree);
Element TreeData(TreeNode *tree);
void DestroyTree(TreeNode *tree);
void traversal_preorder(TreeNode *tree);
void traversal_inorder(TreeNode *tree);
void traversal_postorder(TreeNode *tree);
