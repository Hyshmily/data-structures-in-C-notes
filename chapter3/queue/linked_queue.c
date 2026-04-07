#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node *next;
} Node;

typedef struct Queue {
  Node *head; // 这不是头结点！head有数据
  Node *tail;
} Queue;

Queue *queue_init() {
  Queue *q = malloc(sizeof(Queue));
  q->head = NULL;
  q->tail = NULL;
  return q;
}

void queue_destroy(Queue *q) {
  Node *current = q->head;
  while (current) {
    Node *tmp = current;
    current = current->next;
    free(tmp);
  }
  free(q);
}

void queue_enq(Queue *q, int val) {
  // enqueue is to add last
  Node *new_node = malloc(sizeof(Node));
  new_node->data = val;
  new_node->next = NULL;
  if (q->head == NULL) {
    q->head = new_node;
    q->tail = new_node;
  } else {
    q->tail->next = new_node;
    q->tail = new_node;
  }
}

bool queue_deq(Queue *q, int *val) {
  if (q->head == NULL) {
    return false;
  }
  Node *node = q->head;
  *val = node->data;
  if (q->head == q->tail) {
    q->head = NULL;
    q->tail = NULL;
  } else {
    q->head = q->head->next;
  }
  free(node);
  return true;
}

bool queue_is_empty(Queue *q) { return q->head == NULL; }

int main() {
  Queue *q = queue_init();

  // 空队列测试
  printf("empty: %d\n", queue_is_empty(q));

  // 入队测试
  for (int i = 1; i <= 5; i++)
    queue_enq(q, i * 10);
  printf("empty after enq 5: %d\n", queue_is_empty(q));

  // 出队测试
  int e;
  while (queue_deq(q, &e))
    printf("deq: %d\n", e);

  printf("empty after deq all: %d\n", queue_is_empty(q));

  // 单元素测试：验证 head/tail 同步置 NULL
  queue_enq(q, 42);
  queue_deq(q, &e);
  printf("deq single: %d\n", e);
  printf("empty: %d\n", queue_is_empty(q));

  queue_destroy(q);
  return 0;
}
