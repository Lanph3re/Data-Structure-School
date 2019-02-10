#include<stdio.h>

int string_length(char * sentence, int initial) { // initial is the flag for initial function call of recursion
	static int len;
	if (initial)
		len = 0;
	if (*sentence == '\0')
		return;
	else {
		len++;
		string_length(sentence + 1, 0);
	}

	return len;
}

int isPalindrome(char *sentence, int len) {

	if (sentence[0] == sentence[len - 1]) {
		if (len == 2)
			return 1;
		else if (len - 2 == 1)
			return 1;
		else {
			if (isPalindrome(sentence + 1, len - 2)) {
				return 1;
			}
			else
				return 0;
		}
	}
	else {
		return 0;
	}
}

int main() {
	char arr[100];

	while (1) {
		scanf("%100s", arr);
		if (isPalindrome(arr,string_length(arr, 1))) {
			printf("The string is palindrome\n");
		}
		else {
			printf("The string is not palindrome\n");
		}
	}
}