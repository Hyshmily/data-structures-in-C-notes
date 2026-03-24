#include "stack.h"
#include <stdlib.h>

#define MAX_SIZE 100

struct Stack {
  ElemType data[MAX_SIZE];
  int top;
};

Stack *stack_init() {
  Stack *stack = malloc(sizeof(Stack));
  stack->top = -1;
  return stack;
}

void stack_destroy(Stack *stack) { free(stack); }

bool stack_is_empty(const Stack *stack) { return stack->top == -1; }

bool stack_push(Stack *stack, ElemType e) {
  if (stack->top >= MAX_SIZE - 1) {
    return false; // Stack overflow
  }
  stack->data[++stack->top] = e;
  return true;
}

bool stack_pop(Stack *stack, ElemType *result) {
  if (stack_is_empty(stack)) {
    return false; // Stack underflow
  }
  *result = stack->data[stack->top--];
  return true;
}

bool stack_peek(const Stack *stack, ElemType *result) {
  if (stack_is_empty(stack)) {
    return false; // Stack underflow
  }
  *result = stack->data[stack->top];
  return true;
}
