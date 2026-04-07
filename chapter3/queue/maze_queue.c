#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1024
#define N 5

typedef struct {
  size_t x;
  size_t y;
} Position;

typedef struct {
  Position data[MAX_SIZE];
  int front, rear;
} CircularSqQueue;

CircularSqQueue *queue_init() {
  CircularSqQueue *queue = malloc(sizeof(CircularSqQueue));
  queue->front = 0;
  queue->rear = 0;
  return queue;
}

void queue_destroy(CircularSqQueue *queue) { free(queue); }

bool queue_is_empty(CircularSqQueue *queue) {
  return queue->front == queue->rear;
}

bool queue_enq(CircularSqQueue *queue, Position e) {
  if ((queue->rear + 1) % MAX_SIZE == queue->front)
    return false;
  queue->data[queue->rear] = e;
  queue->rear = (queue->rear + 1) % MAX_SIZE;
  return true;
}

bool queue_deq(CircularSqQueue *queue, Position *e) {
  if (queue_is_empty(queue))
    return false;
  *e = queue->data[queue->front];
  queue->front = (queue->front + 1) % MAX_SIZE;
  return true;
}

/**
 * 1表示墙壁，0表示通道
 * 四周再加上一道围墙
 */
int MAZE[N + 2][N + 2] = {{1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1},
                          {1, 1, 0, 0, 0, 1, 1}, {1, 1, 1, 0, 1, 1, 1},
                          {1, 1, 0, 0, 0, 1, 1}, {1, 1, 1, 1, 1, 1, 1},
                          {1, 1, 1, 1, 1, 1, 1}};

// 记录每个位置的前驱，用于回溯路径
Position prev_pos[N + 2][N + 2];
bool visited[N + 2][N + 2];

void print_path(Position end, size_t start_x, size_t start_y) {
  Position path[MAX_SIZE];
  int k = 0;
  Position p = end;
  while (true) {
    path[k++] = p;
    if (p.x == start_x && p.y == start_y)
      break;
    p = prev_pos[p.x][p.y];
  }
  for (int i = k - 1; i >= 0; i--) {
    printf("(%zu, %zu)", path[i].x, path[i].y);
    if (i > 0)
      printf("->");
  }
  printf("\n");
}

bool find_path(size_t start_x, size_t start_y, size_t end_x, size_t end_y) {
  CircularSqQueue *queue = queue_init();

  memset(visited, 0, sizeof(visited));
  memset(prev_pos, 0, sizeof(prev_pos));

  Position start = {start_x, start_y};
  queue_enq(queue, start);
  visited[start_x][start_y] = true;

  while (!queue_is_empty(queue)) {
    Position current;
    queue_deq(queue, &current);

    if (current.x == end_x && current.y == end_y) {
      print_path(current, start_x, start_y);
      queue_destroy(queue);
      return true;
    }

    // 四个方向: 上、右、下、左
    size_t next_x, next_y;
    for (int d = 0; d < 4; d++) {
      switch (d) {
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
      if (MAZE[next_x][next_y] == 0 && !visited[next_x][next_y]) {
        visited[next_x][next_y] = true;
        prev_pos[next_x][next_y] = current;
        Position next = {next_x, next_y};
        queue_enq(queue, next);
      }
    }
  }
  queue_destroy(queue);
  return false;
}

int main() {
  bool r = find_path(2, 2, 4, 4);
  printf("find_path: %s\n", r ? "true" : "false");
  return 0;
}
