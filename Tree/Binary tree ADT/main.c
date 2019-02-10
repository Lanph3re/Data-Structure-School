#include<stdio.h>
#include"binary_tree.h"

int main() {
	TreeNode *tree = CreateTree("5", NULL, NULL);
	char arr[100];

	while (1) {
		scanf("%s", arr);
		insertNode(arr, tree);

		traversal_inorder(tree);
		puts("");

		traversal_inorder(LeftTree(tree));
		puts("");

		traversal_inorder(RightTree(tree));
		puts("");
	}
}