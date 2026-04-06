#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define N 8

typedef struct {
  int data[N];
  int top;
} Stack;

Stack *stack_init() {
  Stack *s = malloc(sizeof(Stack));
  s->top = -1;
  return s;
}

void stack_destroy(Stack *s) { free(s); }

void stack_push(Stack *s, int col) { s->data[++s->top] = col; }

int stack_pop(Stack *s) { return s->data[s->top--]; }

int stack_peek(Stack *s) { return s->data[s->top]; }

bool stack_is_empty(Stack *s) { return s->top == -1; }

// 检查在 (row, col) 放置皇后是否与栈中已有的皇后冲突
bool is_safe(Stack *s, int row, int col) {
  for (int i = 0; i < s->top; i++) {
    int q_col = s->data[i];
    int q_row = i;
    if (q_col == col || q_row - q_col == row - col ||
        q_row + q_col == row + col)
      return false;
  }
  return true;
}

void print_solution(Stack *s) {
  for (int i = 0; i <= s->top; i++) {
    for (int j = 0; j < N; j++) {
      printf("%c ", j == s->data[i] ? 'Q' : '.');
    }
    printf("\n");
  }
  printf("\n");
}

int main() {
  Stack *s = stack_init();
  int count = 0;

  stack_push(s, -1);
  int row = 0;

  while (!stack_is_empty(s)) {
    int col = stack_peek(s) + 1;
    bool found = false;

    while (col < N) {
      if (is_safe(s, row, col)) {
        found = true;
        break;
      }
      col++;
    }

    if (found) {
      s->data[s->top] = col;

      if (row == N - 1) {
        count++;
        print_solution(s);
      } else {
        row++;
        stack_push(s, -1);
      }
    } else {
      stack_pop(s);
      row--;
    }
  }

  printf("total: %d\n", count);
  stack_destroy(s);
  return 0;
}
