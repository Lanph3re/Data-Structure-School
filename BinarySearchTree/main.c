#include<stdio.h>
#include<stdlib.h>
#include"binary_search_tree.h"

void inorder_traverse(TreeNode *root) {
	if (root == NULL) return;

	inorder_traverse(root->left);
	printf("%d ", root->data);
	inorder_traverse(root->right);
}

int main() {
	int temp;
	TreeNode *bt = NULL;

	while (1) {
		printf("Enter a data to insert : ");
		scanf("%d", &temp);
		if (temp == -1) break;
		bt = BST_insertion(bt, CreateNode(temp));
		inorder_traverse(bt);
		puts("");
	}

	puts("");
	while (1) {
		printf("Enter a key to search : ");
		scanf("%d", &temp);
		if (temp == -1) break;
		TreeNode *searched = BST_search(bt, temp);
		if (searched)
			printf("Searched key : %d\n", searched->data);
		else
			printf("Not found\n");
	}

	puts("");
	while (1) {
		printf("Enter a key to delete : ");
		scanf("%d", &temp);
		if (temp == -1) break;
		bt = BST_deletion(bt, temp);

		inorder_traverse(bt);
		puts("");
	}
}