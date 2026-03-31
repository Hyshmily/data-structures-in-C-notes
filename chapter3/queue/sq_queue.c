#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef int ElemType;

typedef struct {
  ElemType data[MAX_SIZE];
  int rear, front; // rear 指向队尾元素，front指向队首的前一个位置
} SqQueue;

SqQueue *queue_init() {
  SqQueue *queue = malloc(sizeof(SqQueue));
  queue->rear = -1;
  queue->front = -1;
  return queue;
}

void queue_destory(SqQueue *queue) { free(queue); }

bool queue_is_empty(SqQueue *queue) { return queue->front == queue->rear; }

bool queue_enq(SqQueue *queue, ElemType e) {
  if (queue->rear == MAX_SIZE - 1)
    return false;
  queue->rear++;
  queue->data[queue->rear] = e;
  return true;
}

bool queue_deq(SqQueue *queue, ElemType *e) {
  if (queue_is_empty(queue))
    return false;
  queue->front++;
  *e = queue->data[queue->front];
  return true;
}

size_t queue_len(SqQueue *queue) { return queue->rear - queue->front; }

int main() {
  SqQueue *q = queue_init();

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

  queue_destory(q);
  return 0;
}
