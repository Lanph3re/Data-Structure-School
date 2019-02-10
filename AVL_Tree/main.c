#include<stdio.h>
#include<time.h>
#include"AVL_SearchTreeADT.h"

int main() {
	AVL_Tree *tree = AVL_Create();
	int N;

	srand(time(NULL));

	printf("Enter N : ");
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		AVL_Insert(tree, AVL_CreateNode(rand()%100));

		if (!AVL_Empty(tree)) {
			printf("%d : ", AVL_count(tree));
			AVL_PrintTree(tree);
		}
		else
			printf("Empty");

		puts("");
	}

	puts("");

	for (int i = 0; i < N; i++) {
		if (!AVL_Delete(tree, rand()%100)) {
			printf("Key Not Found\n\t");
		}

		if (!AVL_Empty(tree)) {
			printf("%d : ", AVL_count(tree));
			AVL_PrintTree(tree);
		}
		else
			printf("Empty");

		puts("");
	}

	return;
}