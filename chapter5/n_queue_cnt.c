#include <stdio.h>

#define N 8

int col[N]; // col[i] = 第 i 行皇后所在的列

int is_valid(int row, int c) {
  for (int i = 0; i < row; i++) {
    if (col[i] == c || col[i] - c == i - row || col[i] - c == row - i)
      return 0;
  }
  return 1;
}

int solve(int row) {
  if (row == N)
    return 1;
  int count = 0;
  for (int c = 0; c < N; c++) {
    if (is_valid(row, c)) {
      col[row] = c;
      count += solve(row + 1);
    }
  }
  return count;
}

int main() {
  printf("N=%d: %d solutions\n", N, solve(0));
  return 0;
}
