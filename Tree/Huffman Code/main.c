#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"binary_tree.h"

typedef struct {
	char character;
	int count;
} Character;

typedef struct huffList{
	TreeNode *node;
	struct huffList *nextPtr;
} HuffList;

int main() {
	Character huff[128];
	Character temp; // used for sorting
	HuffList *list = NULL;
	HuffList *walker = NULL;
	TreeNode *huffTree = NULL;
	FILE *text = fopen("Huffman.txt", "r");
	FILE *huff_text = NULL;
	int num = 0; // the number of TreeNodes left.
	char ch;


	for (int i = 0; i < 128; i++) {
		huff[i].character = i;
		huff[i].count = 0;
	}

	/* count frequencies of characters in given file */
	while (!feof(text)) {
		fscanf(text, "%c", &ch);
		(huff[ch].count)++;
	}

	/* sort Character array in asscending order of frequency */
	for (int i = 0; i < 128; i++) {
		for (int j = 0; j < 127 - i; j++) {
			if (huff[j].count > huff[j + 1].count) {
				temp = huff[j];
				huff[j] = huff[j + 1];
				huff[j + 1] = temp;
			}
		}
	}

	/* print characters and their frequencies */
	for (int i = 0; i < 128; i++) {
		if (huff[i].character > 32 && huff[i].count != 0) {
			printf("%c : %d\n", huff[i].character, huff[i].count);
			num++;
		}
	}

	/* linked list */
	for (int i = 127; i >= 0; i--) {
		if (huff[i].character <= 32 || huff[i].count == 0) continue;

		HuffList *new = (HuffList *)malloc(sizeof(HuffList));

		if (new == NULL) return;

		new->node = CreateTree(huff[i].character, huff[i].count, NULL, NULL);
		new->nextPtr = list;
		list = new;
	}

	while (1) {
		/* pop out two nodes and make a new TreeNode */
		HuffList *del = list;
		TreeNode *temp_1 = list->node;
		list = list->nextPtr;
		free(del);

		del = list;
		TreeNode *temp_2 = list->node;
		list = list->nextPtr;
		free(del);

		num -= 2;

		if (num == 0) {
			huffTree = CreateTree(-1, temp_1->count + temp_2->count, temp_1, temp_2);
			break;
		}
		else {
			HuffList *new = (HuffList *)malloc(sizeof(HuffList));

			if (new == NULL) return;

			new->node = CreateTree(-1, temp_1->count + temp_2->count, temp_1, temp_2);
			walker = list;

			if (new->node->count <= list->node->count) { // when new node is the first node in the list.
				new->nextPtr = list;
				list = new;
			}
			else {
				while (walker->nextPtr != NULL) { // search the position to insert the new node.
					if (walker->nextPtr->node->count >= new->node->count) {
						new->nextPtr = walker->nextPtr;
						walker->nextPtr = new;
						break;
					}
					else {
						walker = walker->nextPtr;
					}
				}

				if (walker->nextPtr == NULL) {
					new->nextPtr = NULL;
					walker->nextPtr = new;
				}
			} /* end else*/

			num++;
		} /* end else*/
	} /* end while */

	puts("Done");
	char **huffTable = (char **)malloc(sizeof(char *) * 128);
	huffRead(huffTable, huffTree, TRUE);

	puts("Huff Tables");
	for (int i = 0; i < 128; i++) {
		//printf("%c : %s", i, *(huffTable + i));
	}

	/* convert txt file using huffman coding */
	text = fclose(text);
	FILE *text_ = fopen("Huffman.txt", "r");
	huff_text = fopen("Huffman_reslt.txt", "w+");

	while (!feof(text_)) {
		fscanf(text_, "%c", &ch);
		if(ch>32)
			fprintf(huff_text, "%s", *(huffTable + ch));
	}
}