#include <stdio.h>
#include <assert.h>

static int search(int a[], int low, int high, int target) {
  if (low > high)
    return -1;
  int mid = low + (high - low) / 2;
  if (a[mid] == target)
    return mid;
  else if (a[mid] > target)
    return search(a, low, mid - 1, target);
  else
    return search(a, mid + 1, high, target);
}

int binary_search(int a[], size_t n, int target) {
  return search(a, 0, (int)n - 1, target);
}

int main(void) {
  int a[] = {1, 3, 5, 7, 9, 11, 13};
  size_t n = sizeof(a) / sizeof(a[0]);

  assert(binary_search(a, n, 1)  == 0);
  assert(binary_search(a, n, 7)  == 3);
  assert(binary_search(a, n, 13) == 6);

  assert(binary_search(a, n, 0)  == -1);
  assert(binary_search(a, n, 6)  == -1);
  assert(binary_search(a, n, 14) == -1);

  printf("all tests passed\n");
  return 0;
}
