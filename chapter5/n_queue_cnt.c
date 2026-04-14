#include <stdio.h>

#define N 8

int col[N]; // col[i] = 第 i 行皇后所在的列

// 判断在第 row 行、第 c 列放置皇后是否与前 row 行冲突
int is_valid(int row, int c) {
  for (int i = 0; i < row; i++) {
    if (col[i] == c || col[i] - c == i - row || col[i] - c == row - i)
      return 0;
  }
  return 1;
}

// solve(k)：前 k 行已合法放置，返回整个棋盘的合法方案总数。
//
// 归纳定义：
//   - 基础情形：k == N，N 行全部放完，恰好构成 1 种合法方案，返回 1。
//   - 归纳步骤：枚举第 k 行的每一列 c，若合法则递归调用 solve(k+1)，
//               由归纳假设 solve(k+1) 已正确，累加其结果即得 solve(k)。
//
// 因此 solve(0) 给出空棋盘（前 0 行已放好）时的总方案数，即问题的解。
int solve(int k) {
  if (k == N)
    return 1;
  int count = 0;
  for (int c = 0; c < N; c++) {
    if (is_valid(k, c)) {
      col[k] = c;
      count += solve(k + 1);
    }
  }
  return count;
}

int main() {
  printf("N=%d: %d solutions\n", N, solve(0));
  return 0;
}
