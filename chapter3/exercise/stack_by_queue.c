#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
  int data[MAX_SIZE];
  int front, rear;
} Queue;

Queue *queue_init() {
  Queue *q = malloc(sizeof(Queue));
  q->front = 0;
  q->rear = 0;
  return q;
}

void queue_destroy(Queue *q) { free(q); }

bool queue_is_empty(Queue *q) { return q->front == q->rear; }

bool queue_enq(Queue *q, int e) {
  if ((q->rear + 1) % MAX_SIZE == q->front)
    return false;
  q->data[q->rear] = e;
  q->rear = (q->rear + 1) % MAX_SIZE;
  return true;
}

bool queue_deq(Queue *q, int *e) {
  if (queue_is_empty(q))
    return false;
  *e = q->data[q->front];
  q->front = (q->front + 1) % MAX_SIZE;
  return true;
}

size_t queue_len(Queue *q) {
  return (q->rear - q->front + MAX_SIZE) % MAX_SIZE;
}

typedef struct {
  Queue *q;
} MyStack;

MyStack *myStackCreate() {
  MyStack *s = malloc(sizeof(MyStack));
  s->q = queue_init();
  return s;
}

void myStackPush(MyStack *obj, int x) {
  queue_enq(obj->q, x);
  size_t n = queue_len(obj->q);
  for (size_t i = 0; i < n - 1; i++) {
    int e;
    queue_deq(obj->q, &e);
    queue_enq(obj->q, e);
  }
}

int myStackPop(MyStack *obj) {
  int e;
  queue_deq(obj->q, &e);
  return e;
}

int myStackTop(MyStack *obj) {
  int e = myStackPop(obj);
  myStackPush(obj, e);
  return e;
}

bool myStackEmpty(MyStack *obj) { return queue_is_empty(obj->q); }

void myStackFree(MyStack *obj) {
  queue_destroy(obj->q);
  free(obj);
}

/**
 * Your MyStack struct will be instantiated and called as such:
 * MyStack* obj = myStackCreate();
 * myStackPush(obj, x);
 *
 * int param_2 = myStackPop(obj);
 *
 * int param_3 = myStackTop(obj);
 *
 * bool param_4 = myStackEmpty(obj);
 *
 * myStackFree(obj);
 */

int main() {
  MyStack *obj = myStackCreate();
  myStackPush(obj, 1);
  myStackPush(obj, 2);

  printf("top: %d\n", myStackTop(obj));     // 2
  printf("pop: %d\n", myStackPop(obj));     // 2
  printf("empty: %d\n", myStackEmpty(obj)); // 0 (false)

  myStackFree(obj);
  return 0;
}
