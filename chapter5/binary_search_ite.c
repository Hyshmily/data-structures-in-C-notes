#include <stdio.h>
#include <assert.h>

int binary_search(int a[], size_t N, int target) {
  int low = 0;
  int high = N - 1;
  while (high >= low) {
    int mid = low + (high - low) / 2;
    if (a[mid] == target)
      return mid;
    else if (a[mid] > target)
      high = mid - 1;
    else
      low = mid + 1;
  }
  return -1;
}

int main(void) {
  int a[] = {1, 3, 5, 7, 9, 11, 13};
  size_t n = sizeof(a) / sizeof(a[0]);

  // 找到的情况
  assert(binary_search(a, n, 1)  == 0);
  assert(binary_search(a, n, 7)  == 3);
  assert(binary_search(a, n, 13) == 6);

  // 找不到的情况
  assert(binary_search(a, n, 0)  == -1);
  assert(binary_search(a, n, 6)  == -1);
  assert(binary_search(a, n, 14) == -1);

  printf("all tests passed\n");
  return 0;
}
