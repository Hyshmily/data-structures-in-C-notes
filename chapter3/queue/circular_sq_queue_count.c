#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef int ElemType;

typedef struct {
  ElemType data[MAX_SIZE];
  int front; // 指向队首元素
  int count; // 元素数量
} CircularSqQueue;

CircularSqQueue *queue_init() {
  CircularSqQueue *queue = malloc(sizeof(CircularSqQueue));
  queue->front = 0;
  queue->count = 0;
  return queue;
}

void queue_destory(CircularSqQueue *queue) { free(queue); }

bool queue_is_empty(CircularSqQueue *queue) {
  return queue->count == 0;
}

bool queue_is_full(CircularSqQueue *queue) {
  return queue->count == MAX_SIZE;
}

bool queue_enq(CircularSqQueue *queue, ElemType e) {
  if (queue_is_full(queue))
    return false;
  int rear = (queue->front + queue->count) % MAX_SIZE;
  queue->data[rear] = e;
  queue->count++;
  return true;
}

bool queue_deq(CircularSqQueue *queue, ElemType *e) {
  if (queue_is_empty(queue))
    return false;
  *e = queue->data[queue->front];
  queue->front = (queue->front + 1) % MAX_SIZE;
  queue->count--;
  return true;
}

size_t queue_len(CircularSqQueue *queue) {
  return (size_t)queue->count;
}

int main() {
  CircularSqQueue *q = queue_init();

  // 空队列测试
  printf("empty: %d\n", queue_is_empty(q));
  printf("len: %zu\n", queue_len(q));

  // 入队测试
  for (int i = 1; i <= 5; i++)
    queue_enq(q, i * 10);
  printf("len after enq 5: %zu\n", queue_len(q));

  // 出队测试
  int e;
  while (queue_deq(q, &e))
    printf("deq: %d\n", e);

  printf("empty after deq all: %d\n", queue_is_empty(q));

  // 循环测试：入队再出队，验证环形复用
  for (int i = 0; i < MAX_SIZE; i++)
    queue_enq(q, i);
  printf("full: %d\n", queue_is_full(q));
  printf("len: %zu\n", queue_len(q));

  queue_destory(q);
  return 0;
}
