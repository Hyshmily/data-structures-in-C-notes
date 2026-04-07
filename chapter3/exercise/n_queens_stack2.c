#include <stdbool.h>
#include <stdio.h>

#define N 8

int queen_col[N]; // queen_col[i] = 第 i 行皇后所在的列
int next_col[N];  // next_col[i]  = 第 i 行下一次要从哪一列开始试

// 检查在 (row, col) 放置皇后是否冲突
bool is_safe(int row, int col) {
  for (int i = 0; i < row; i++) {
    if (queen_col[i] == col ||
        i - queen_col[i] == row - col ||
        i + queen_col[i] == row + col)
      return false;
  }
  return true;
}

void print_solution(void) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++)
      printf("%c ", j == queen_col[i] ? 'Q' : '.');
    printf("\n");
  }
  printf("\n");
}

int main(void) {
  int count = 0;
  int row = 0;
  next_col[0] = 0;

  while (row >= 0) {
    bool found = false;

    // 从 next_col[row] 开始逐列尝试
    for (int col = next_col[row]; col < N; col++) {
      if (is_safe(row, col)) {
        queen_col[row] = col;
        next_col[row] = col + 1; // 下次回溯到本行时从 col+1 开始
        found = true;
        break;
      }
    }

    if (found) {
      if (row == N - 1) {
        count++;
        print_solution();
        row--; // 找到解后回退，继续搜索
      } else {
        row++;
        next_col[row] = 0; // 新行从第 0 列开始
      }
    } else {
      next_col[row] = 0; // 重置，下次再进入时从头开始
      row--;
    }
  }

  printf("total: %d\n", count);
  return 0;
}
