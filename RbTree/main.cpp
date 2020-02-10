#include <windows.h>
#include <ctime>
#include <iostream>
#include "rb_tree.h"

int main() {
  RedBlackTree *tree = new RedBlackTree;
  srand(time(NULL));
  int arr[100];
  int arr_[100];
  int count = 0;

  for (int i = 0; i < 100; i++) {
    arr[i] = arr_[i] = rand() % 1000;
  }

  while (true) {
    int idx = rand() % 100;
    if (arr[idx] != -1) {
      count++;
      tree->Insert(arr[idx]);
      arr[idx] = -1;
      tree->Print();
      if (count == 100) break;
    }
  }

  while (true) {
    int idx = rand() % 100;
    if (arr_[idx] != -1) {
      count++;
      tree->Delete(arr_[idx]);
      arr_[idx] = -1;
      if (count == 200) break;
      tree->Print();
    }
  }

  std::cout << "END" << std::endl;

  return 0;
}