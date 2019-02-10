#include<stdio.h>

long long fibo(int n, long long acc);

int main() {
	for (int i = 50; i <= 59; i++) {
		printf("%d : %lld\n", i, fibo(i, 0));
	}
	return 0;
}

long long fibo(int n, long long acc) {
	static long long base;
	static long long base_;
	static int count;

	if (count == n && acc != 0) return acc;

	if (acc == 0) {
		base = 0;
		base_ = 1;
		count = 2;
	}

	if (n == 1) {
		return base;
	}
	else if (n == 2) {
		return base_;
	}
	else {
		count++;
		acc = base + base_;
		base = base_;
		base_ = acc;
		return fibo(n, acc);
	}
}