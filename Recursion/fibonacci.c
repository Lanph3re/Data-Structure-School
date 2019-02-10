#include<stdio.h>

int fibo(int n);

int main(){
	for (int i = 1; i <= 9; i++) {
		printf("%d : %d\n", i, fibo(i));
	}
	return 0;
}
/*
int fibo(int n) {
	if (n == 1)
		return 0;
	else if (n == 2)
		return 1;
	else
		return fibo(n - 1) + fibo(n - 2);
}*/

int fibo(int n) {
	int base = 0;
	int base_ = 1;
	int val;

	if (n == 1)
		return 0;
	else if (n == 2)
		return 1;
	else {
		for (int i = 0; i < n - 2; i++) {
			val = base + base_;
			base = base_;
			base_ = val;
		}
		
		return val;
	}
}