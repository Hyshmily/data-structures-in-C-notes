#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1024
#define N 5

typedef struct {
  size_t x;
  size_t y;
  int next_direction; // 0: up; 1: right; 2: down; 3: left
} Position;

typedef struct {
  Position data[MAX_SIZE];
  int top;
} MazeTrack;

MazeTrack *stack_init() {
  MazeTrack *stack = malloc(sizeof(MazeTrack));
  stack->top = -1;
  return stack;
}

void stack_destroy(MazeTrack *stack) { free(stack); }

void stack_push(MazeTrack *stack, Position p) { stack->data[++stack->top] = p; }

Position stack_pop(MazeTrack *stack) { return stack->data[stack->top--]; }

Position stack_peek(const MazeTrack *stack) { return stack->data[stack->top]; }

bool stack_is_empty(const MazeTrack *stack) { return stack->top == -1; }

/**
 * 1表示墙壁，0表示通道
 * 四周再加上一道围墙
 */
int MAZE[N + 2][N + 2] = {{1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1},
                          {1, 1, 0, 0, 0, 1, 1}, {1, 1, 1, 0, 1, 1, 1},
                          {1, 1, 0, 0, 0, 1, 1}, {1, 1, 1, 1, 1, 1, 1},
                          {1, 1, 1, 1, 1, 1, 1}};

bool find_path(size_t start_x, size_t start_y, size_t end_x, size_t end_y) {

  MazeTrack *stack = stack_init();

  Position p = {start_x, start_y, -1};
  stack_push(stack, p);

  MAZE[start_x][start_y] = -1; // 避免重复访问

  while (!stack_is_empty(stack)) {
    Position current = stack_peek(stack);
    if (current.x == end_x && current.y == end_y) {
      // 打印路径
      Position path[MAX_SIZE];
      int k = 0;
      while (!stack_is_empty(stack)) {
        path[k++] = stack_pop(stack);
      }
      while (k > 0) {
        printf("(%zu, %zu)->", path[k - 1].x, path[k - 1].y);
        k--;
      }
      printf("\n");
      stack_destroy(stack);
      return true;
    }
    bool find = false;
    int direction = current.next_direction;
    size_t next_x, next_y;
    while (direction < 4 && !find) {
      direction++;
      switch (direction) {
      case 0:
        next_x = current.x - 1;
        next_y = current.y;
        break;
      case 1:
        next_x = current.x;
        next_y = current.y + 1;
        break;
      case 2:
        next_x = current.x + 1;
        next_y = current.y;
        break;
      case 3:
        next_x = current.x;
        next_y = current.y - 1;
        break;
      }
      if (MAZE[next_x][next_y] == 0)
        find = true;
    }
    if (find) {
      stack->data[stack->top].next_direction = direction;
      Position p = {next_x, next_y, -1};
      stack_push(stack, p);
      MAZE[next_x][next_y] = -1;
    } else {
      Position p = stack_pop(stack);
      MAZE[p.x][p.y] = 0;
    }
  }
  stack_destroy(stack);
  return false;
}

int main() {
  bool r = find_path(2, 2, 4, 4);
  printf("find_path: %s\n", r ? "true" : "false");
  return 0;
}
