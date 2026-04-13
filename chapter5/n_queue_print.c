#include <stdio.h>

#define N 8

int col[N];

int is_valid(int row, int c) {
  for (int i = 0; i < row; i++) {
    if (col[i] == c || col[i] - c == i - row || col[i] - c == row - i)
      return 0;
  }
  return 1;
}

int solve(int row) {
  if (row == N) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++)
        printf("%c ", col[i] == j ? 'Q' : '*');
      printf("\n");
    }
    printf("\n");
    return 1;
  }
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
  printf("Total: %d solutions\n", solve(0));
  return 0;
}
