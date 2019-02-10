#include<stdio.h>
#include"stacksADT.h"

int main() {
	FILE *file = fopen("file.txt", "r");
	Stack *head = CreateStack();
	char arr[500];
	char *ptr = arr;
	int len;
	int count = 0;

	while (!feof(file)) {
		fgets(arr, sizeof(arr), file);
		count++;
		len = strlen(arr);

		for (int i = 0; i < len; i++) {
			switch (ptr[i])
			{
			case '(':
			case '{':
			case '[':
				Push(head, ptr[i]);
				break;
			case ')':
				if (Pop(head) != '(') {
					printf("Brace Error '%c' in line %d\n", ptr[i], count);
					return;
				}
				else
					break;
			case '}':
				if (Pop(head) != '{') {
					printf("Brace Error '%c' in line %d\n", ptr[i], count);
					return;
				}
				else
					break;
			case ']':
				if (Pop(head) != '[') {
					printf("Brace Error '%c' in line %d\n", ptr[i], count);
					return;
				}
				else
					break;
			default:
				break;
			}
		}
	}

	printf("No Error\n");
	return 0;
}