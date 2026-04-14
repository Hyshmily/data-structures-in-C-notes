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

int solve_iterative(void) {
  int count = 0;
  int row = 0;

  // 初始化：每一行都还没开始尝试，记为 -1
  for (int i = 0; i < N; i++)
    col[i] = -1;

  while (row >= 0) {
    // 当前行从“上次尝试过的位置的下一列”开始继续找
    col[row]++;

    // 跳过所有不合法的位置
    while (col[row] < N && !is_valid(row, col[row])) {
      col[row]++;
    }

    if (col[row] < N) {
      // 找到了当前行的一个合法位置
      if (row == N - 1) {
        // 最后一行也放成功了，得到一个完整解
        count++;
      } else {
        // 进入下一行
        row++;
        col[row] = -1; // 下一行从 0 列开始试（因为循环开头会先 ++）
      }
    } else {
      // 当前行已经没有合法列了，需要回溯到上一行
      col[row] = -1;
      row--;
    }
  }

  return count;
}

int main(void) {
  printf("N=%d: %d solutions\n", N, solve_iterative());
  return 0;
}
