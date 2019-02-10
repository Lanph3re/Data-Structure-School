#include"binary_search_tree.h"
#include<stdlib.h>

TreeNode *CreateNode(int item) {
	TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));

	if (newNode == NULL) return NULL;

	newNode->data = item;
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

TreeNode *BST_insertion(TreeNode *root, TreeNode *newNode) {
	if (root == NULL) return newNode;

	if (newNode->data < root->data)
		root->left = BST_insertion(root->left, newNode);
	else
		root->right = BST_insertion(root->right, newNode);

	return root;
}

TreeNode *BST_search(TreeNode *root, int key) {
	if (root == NULL) return NULL;

	if (key == root->data) return root;
	else if (key > root->data) return BST_search(root->right, key);
	else return BST_search(root->left, key);
}

TreeNode *BST_deletion(TreeNode *root, int key) {
	if (root == NULL) return NULL;

	if (key < root->data)
		root->left = BST_deletion(root->left, key);
	else if (key > root->data)
		root->right = BST_deletion(root->right, key);
	else { // root is the node to delete
		/* case 1 : root has no children */
		if (!root->left && !root->right) {
			free(root);

			return NULL;
		}
		/* case 2 : root has only one child */
		else if ((root->left&&!root->right)||(!root->left&&root->right)) {
			TreeNode *temp = root->left != NULL ? root->left : root->right;
			free(root);

			return temp;
		}
		/* case 3 : root has two children */
		else {
			// find successor of root
			TreeNode *temp = root->right;
			for (; temp->left != NULL; temp = temp->left);
			
			root->data = temp->data;
			root->right = BST_deletion(root->right, temp->data);
		}
	}

	return root;
}