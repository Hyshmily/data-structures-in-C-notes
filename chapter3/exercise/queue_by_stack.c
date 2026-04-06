#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
  int data[MAX_SIZE];
  int top;
} Stack;

Stack *stack_init() {
  Stack *s = malloc(sizeof(Stack));
  s->top = -1;
  return s;
}

void stack_destroy(Stack *s) { free(s); }

bool stack_is_empty(Stack *s) { return s->top == -1; }

void stack_push(Stack *s, int x) { s->data[++s->top] = x; }

int stack_pop(Stack *s) { return s->data[s->top--]; }

int stack_peek(Stack *s) { return s->data[s->top]; }

/**
 * 用两个栈模拟队列
 *
 * s1: 输入栈，push 时直接入栈
 * s2: 输出栈，pop/peek 时如果 s2 为空，把 s1 全部倒入 s2
 */
typedef struct {
  Stack *s1;
  Stack *s2;
} MyQueue;

MyQueue *myQueueCreate() {
  MyQueue *q = malloc(sizeof(MyQueue));
  q->s1 = stack_init();
  q->s2 = stack_init();
  return q;
}

void myQueuePush(MyQueue *obj, int x) { stack_push(obj->s1, x); }

// 把 s1 的元素全部倒入 s2
void transfer(MyQueue *obj) {
  while (!stack_is_empty(obj->s1)) {
    stack_push(obj->s2, stack_pop(obj->s1));
  }
}

int myQueuePop(MyQueue *obj) {
  if (stack_is_empty(obj->s2))
    transfer(obj);
  return stack_pop(obj->s2);
}

int myQueuePeek(MyQueue *obj) {
  if (stack_is_empty(obj->s2))
    transfer(obj);
  return stack_peek(obj->s2);
}

bool myQueueEmpty(MyQueue *obj) {
  return stack_is_empty(obj->s1) && stack_is_empty(obj->s2);
}

void myQueueFree(MyQueue *obj) {
  stack_destroy(obj->s1);
  stack_destroy(obj->s2);
  free(obj);
}

/**
 * Your MyQueue struct will be instantiated and called as such:
 * MyQueue* obj = myQueueCreate();
 * myQueuePush(obj, x);
 *
 * int param_2 = myQueuePop(obj);
 *
 * int param_3 = myQueuePeek(obj);
 *
 * bool param_4 = myQueueEmpty(obj);
 *
 * myQueueFree(obj);
 */

int main() {
  MyQueue *obj = myQueueCreate();
  myQueuePush(obj, 1);
  myQueuePush(obj, 2);
  myQueuePush(obj, 3);

  printf("peek: %d\n", myQueuePeek(obj)); // 1
  printf("pop: %d\n", myQueuePop(obj));   // 1
  printf("pop: %d\n", myQueuePop(obj));   // 2
  printf("pop: %d\n", myQueuePop(obj));   // 3
  printf("empty: %d\n", myQueueEmpty(obj)); // 1 (true)

  myQueueFree(obj);
  return 0;
}
