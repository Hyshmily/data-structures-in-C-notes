#include "queue.h"
#include <stdlib.h>

struct QueueNode {
  void *data;
  struct QueueNode *next;
};

struct Queue {
  QueueNode *head; // 这不是头结点！head有数据
  QueueNode *tail;
};

Queue *queue_init() {
  Queue *q = malloc(sizeof(Queue));
  q->head = NULL;
  q->tail = NULL;
  return q;
}

void queue_destroy(Queue *q) {
  QueueNode *current = q->head;
  while (current) {
    QueueNode *tmp = current;
    current = current->next;
    free(tmp);
  }
  free(q);
}

void queue_enqueue(Queue *q, void *val) {
  // enqueue is to add last
  QueueNode *new_node = malloc(sizeof(QueueNode));
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

bool queue_deq(Queue *q, void **val) {
  if (q->head == NULL) {
    return false;
  }
  QueueNode *node = q->head;
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
