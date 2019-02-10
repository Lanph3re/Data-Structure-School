#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct node {
	int data;
	struct node *next;
} Node;

void merge(int *arr, int low, int mid, int high) {
	int *temp = (int *)malloc(sizeof(int)*(high - low + 1));
	int i, j, k;

	if (temp == NULL) return;

	i = low;
	j = mid + 1;
	k = 0;

	while (i <= mid && j <= high) {
		if (arr[i] >= arr[j])
			temp[k++] = arr[j++];
		else
			temp[k++] = arr[i++];
	}


	if (i > mid) {
		while (j <= high)
			temp[k++] = arr[j++];
	}
	else {
		while (i <= mid)
			temp[k++] = arr[i++];
	}

	for (int i = low; i <= high; i++)
		arr[i] = temp[i-low];

	free(temp);

	return;
}

void mergeSort(int *arr, int low, int high) {
	if (low < high) {
		int mid = (low + high) / 2;
		mergeSort(arr, low, mid);
		mergeSort(arr, mid + 1, high);
		merge(arr, low, mid, high);
	}
}

void radixSort(int *arr, int size) {
	int max = arr[0];
	int digits = 1;
	int idx;
	Node **bucket = (Node **)malloc(sizeof(Node *) * 10);
	Node *temp;

	for (int i = 0; i < 10; i++)
		bucket[i] = NULL;

	for (int i = 0; i < size; i++) {	// find the largest element
		if (arr[i] > max)
			max = arr[i];
	}

	while (max / 10 != 0) {				// find the number of digits
		digits++;
		max /= 10;
	}

	for (int round = 0; round < digits; round++) {
		// put all elements in bucket
		for (int i = 0; i < size; i++) {
			// find the digit number
			idx = arr[i];
			for (int j = 0; j < round; j++) {
				idx /= 10;
			}
			idx = idx % 10;

			// create a node and put it in bucket
			Node *node = (Node *)malloc(sizeof(Node));

			if (node == NULL) {
				free(bucket);
				return;
			}

			node->data = arr[i];
			node->next = NULL;
			
			if (bucket[idx] == NULL)
				bucket[idx] = node;
			else {
				for (temp = bucket[idx]; temp->next != NULL; temp = temp->next);
				temp->next = node;
			}
		}	// end for(int i..)

		// pop elements in buckets and put them in arr
		idx = 0;
		for (int i = 0; i < 10; i++) {
			while (bucket[i] != NULL) {
				temp = bucket[i];
				bucket[i] = temp->next;
				
				arr[idx++] = temp->data;
				free(temp);
			}
		}
	}	// end for(int round..)
}

int main() {
	int arr[6] = { 12,11,13,5,6,7 };
	int arr_2[8] = { 170,45,75,90,802,24,2,66 };

	/* Merge Sort */
	puts("/* Merge Sort */");
	for (int i = 0; i < 6; i++)
		printf("%2d  ", arr[i]);

	puts("");
	mergeSort(arr, 0, 5);

	for (int i = 0; i < 6; i++)
		printf("%2d  ", arr[i]);

	/* Radix Sort */
	puts("\n\n/* Radix Sort */");
	for (int i = 0; i < 8; i++)
		printf("%3d ", arr_2[i]);

	puts("");
	radixSort(arr_2, 8);

	for (int i = 0; i < 8; i++)
		printf("%3d ", arr_2[i]);

	puts("");
}