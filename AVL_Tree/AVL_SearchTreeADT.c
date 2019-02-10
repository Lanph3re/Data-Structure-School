#include<stdlib.h>
#include<stdio.h>
#include"AVL_SearchTreeADT.h"

#define TRUE 1
#define FALSE 0
#define LH 1
#define EH 0
#define RH -1

AVL_Tree *AVL_Create() {
	AVL_Tree *tree = (AVL_Tree *)malloc(sizeof(AVL_Tree));

	if (tree == NULL) return NULL;
	
	tree->root = NULL;
	tree->count = 0;

	return tree;
}

TreeNode *AVL_CreateNode(int data) {
	TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));

	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->bal = 0;

	return newNode;
}

TreeNode *AVL_RotateLeft(TreeNode *root) {
	TreeNode *temp = root->right;
	
	root->right = temp->left;
	temp->left = root;

	return temp;
}

TreeNode *AVL_RotateRight(TreeNode *root) {
	TreeNode *temp = root->left;

	root->left = temp->right;
	temp->right = root;

	return temp;
}

TreeNode *_AVL_Insert(TreeNode *root, TreeNode *newNode, int *taller) {
	if (root == NULL) {
		*taller = TRUE;
		return newNode;
	}

	if (root->data > newNode->data) {
		root->left = _AVL_Insert(root->left, newNode, taller);
		if (*taller) {
			TreeNode *leftTree = root->left;
			TreeNode *rightTree = root->left->right;

			switch (root->bal) {
			case LH:
				if (leftTree->bal == LH) { // case LL
					root->bal = leftTree->bal = EH;
					root = AVL_RotateRight(root);
					*taller = FALSE;
				}
				else { // case LR
					switch (rightTree->bal) {
					case LH:
						root->bal = RH;
						leftTree->bal=EH;
						rightTree->bal = EH;
						break;
					case EH:
						root->bal = EH;
						leftTree->bal = EH;
						rightTree->bal = EH;
						break;
					case RH:
						root->bal = EH;
						leftTree->bal = LH;
						rightTree->bal = EH;
						break;
					} /* end switch */
					root->left = AVL_RotateLeft(leftTree);
					root = AVL_RotateRight(root);
					*taller = FALSE;
				} /* end case LR */
				break;
			case EH:
				root->bal = LH;
				break;
			case RH:
				root->bal = EH;
				*taller = FALSE;
				break;
			} /* end switch */
		} /* end if(*taller) */	
	}
	else { // root->data < newNode->data
		root->right = _AVL_Insert(root->right, newNode, taller);
		if (*taller) {
			TreeNode *rightTree = root->right;
			TreeNode *leftTree = root->right->left;

			switch (root->bal) {
			case LH:
				root->bal = EH;
				*taller = FALSE;
				break;
			case EH:
				root->bal = RH;
				break;
			case RH:
				if (rightTree->bal == RH) { // case RR
					root->bal = rightTree->bal = EH;
					root = AVL_RotateLeft(root);
					*taller = FALSE;
				}
				else { // case RL
					switch (leftTree->bal) {
					case LH:
						root->bal = EH;
						leftTree->bal = EH;
						rightTree->bal = RH;
						break;
					case EH:
						root->bal = EH;
						leftTree->bal = EH;
						rightTree->bal = EH;
						break;
					case RH:
						root->bal = LH;
						leftTree->bal = EH;
						rightTree->bal = EH;
						break;
					} /* end switch */
					root->right = AVL_RotateRight(rightTree);
					root = AVL_RotateLeft(root);
					*taller = FALSE;
				} /* end case RL */
				break;
			} /* end switch */
		} /* end if(*taller) */
	}

	return root;
}

void AVL_Insert(AVL_Tree *tree, TreeNode *newNode) {
	int taller = FALSE;

	tree->root = _AVL_Insert(tree->root, newNode, &taller); // Insert newNode into Tree and check whether there is unbalanced node.
	tree->count++;

	return;
}

TreeNode *_AVL_delLeftBal(TreeNode *root, int *shorter) { // check whether root node gets unbalanced and if it does, call the balancing procedure
	TreeNode *leftTree;
	TreeNode *rightTree = root->right;

	switch (root->bal) {
	case LH:
		root->bal = EH;
		break;
	case EH:
		root->bal = RH;
		*shorter = FALSE;
		break;
	case RH: // root-> bal becomes RH - 1 (-2)
		if (rightTree->bal == RH) { // case RR
			root->bal = EH;
			rightTree->bal = EH;
			root = AVL_RotateLeft(root);
			*shorter = FALSE;
		}
		else { // case RL
			leftTree = root->right->left;
			switch (leftTree->bal) {
			case LH:
				root->bal = EH;
				leftTree->bal = EH;
				rightTree->bal = RH;
				break;
			case EH:
				root->bal = EH;
				leftTree->bal = EH;
				rightTree->bal = EH;
				break;
			case RH:
				root->bal = LH;
				leftTree->bal = EH;
				rightTree->bal = EH;
				break;
			}
			root->right = AVL_RotateRight(rightTree);
			root = AVL_RotateLeft(root);
			*shorter = FALSE;
		}
	} // end switch(root->bal)

	return root;
}

TreeNode *_AVL_delRightBal(TreeNode *root, int *shorter) {
	TreeNode *leftTree = root->left;
	TreeNode *rightTree;

	switch (root->bal) {
	case LH: // root->bal becomes LH + 1 (+2)
		if (leftTree->bal == LH) { // case LL
			root->bal = EH;
			leftTree->bal = EH;
			root = AVL_RotateRight(root);
			*shorter = FALSE;
		}
		else { // case RL
			rightTree = root->left->right;
			switch (rightTree->bal) {
			case LH:
				root->bal = RH;
				leftTree->bal = EH;
				rightTree->bal = EH;
				break;
			case EH:
				root->bal = EH;
				leftTree->bal = EH;
				rightTree->bal = EH;
				break;
			case RH:
				root->bal = EH;
				leftTree->bal = LH;
				rightTree->bal = EH;
				break;
			}
			root->left = AVL_RotateRight(leftTree);
			root = AVL_RotateRight(root);
			*shorter = FALSE;
		}
		break;
	case EH:
		root->bal = LH;
		*shorter = FALSE;
		break;
	case RH:
		root->bal = EH;
		break;
	} // end switch(root->bal)

	return root;
}

TreeNode *_AVL_Delete(TreeNode *root, int key, int *shorter, int *result) {
	if (root == NULL) { // Fail delete : Not Found
		*result = FALSE;
		*shorter = FALSE;

		return NULL;
	}

	if (key > root->data) {
		root->right = _AVL_Delete(root->right, key, shorter, result);
		if (*shorter)
			root = _AVL_delRightBal(root, shorter);
	}
	else if (key < root->data) {
		root->left = _AVL_Delete(root->left, key, shorter, result);
		if(*shorter)
			root = _AVL_delLeftBal(root, shorter);
	}
	else { // root is the node to delete
		if (!root->left && !root->right) { // case 1 : root has no children
			free(root);
			*shorter = TRUE;
			*result = TRUE;

			return NULL;
		} // end case 1
		else if ((root->left && !root->right) || (!root->left&&root->right)) { // case 2 : root has a child
			TreeNode *temp = (root->left) ? root->left : root->right;
			free(root);
			*shorter = TRUE;
			*result = TRUE;

			return temp;
		} // end case 2
		else { // case 3 : root has two children
			TreeNode *temp = root->right;
			for (; temp->left; temp = temp->left); // Find successor node

			root->data = temp->data; // change key value
			root->right = _AVL_Delete(root->right, temp->data, shorter, result);

			if (*shorter)
				root = _AVL_delRightBal(root, shorter);
		} // end case 3
	} // end else, root is the node to delete

	return root;
}

int AVL_Delete(AVL_Tree *tree, int key) { // delete node in tree and return whether deletion was successful
	int result = FALSE;
	int shorter = FALSE;

	tree->root = _AVL_Delete(tree->root, key, &shorter, &result);
	tree->count--;

	return result;
}

TreeNode *_AVL_Search(TreeNode *root, int key) { 
	if (root == NULL) return NULL;

	if (root->data == key) 
		return root;
	else if (root->data > key) 
		return _AVL_Search(root->left, key);
	else 
		return _AVL_Search(root->right, key);
}

TreeNode *AVL_Search(AVL_Tree *tree, int key) { // Search and Return the node which has the key.
	return _AVL_Search(tree->root, key);
}

int AVL_count(AVL_Tree *tree) { // return the number of nodes in the tree
	return tree->count;
}

int AVL_Empty(AVL_Tree *tree) { // return TRUE if the tree is empty
	return (tree->root) == NULL;
}

void _AVL_PrintTree(TreeNode *root) { 
	if (root == NULL) return;

	_AVL_PrintTree(root->left);
	_AVL_PrintTree(root->right);
	printf("%d ", root->data);
}

void AVL_PrintTree(AVL_Tree *tree) { // Postorder Traversal
	if (tree->root == NULL) return;

	_AVL_PrintTree(tree->root);
}