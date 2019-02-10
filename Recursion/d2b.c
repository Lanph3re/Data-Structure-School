#include <stdio.h>

void decimalToBinary(int n) {
	if (n / 2 != 0) {
		decimalToBinary(n / 2);
	}
	printf("%d", n % 2);
}

int main() {
	for (int i = 1; i <= 12; i++) {
		printf("%d : ", i);
		decimalToBinary(i);
		puts("");
	}
}