#include "stack.h"
#include <stdlib.h>

typedef struct Node {
  ElemType data;
  struct Node *next;
} Node;

struct Stack {
  Node *top; // It is a dummy head
};

Stack *stack_init() {
  Stack *stack = malloc(sizeof(Stack));
  stack->top = malloc(sizeof(Node)); // dummy head
  stack->top->next = NULL;
  return stack;
}

void stack_destroy(Stack *stack) {
  Node *current = stack->top;
  while (current != NULL) {
    Node *next = current->next;
    free(current);
    current = next;
  }
  free(stack);
}

bool stack_is_empty(const Stack *stack) { return stack->top->next == NULL; }

bool stack_push(Stack *stack, ElemType e) {
  Node *new_node = malloc(sizeof(Node));
  new_node->data = e;
  new_node->next = stack->top->next;
  stack->top->next = new_node;
  return true;
}

bool stack_pop(Stack *stack, ElemType *result) {
  if (stack_is_empty(stack)) {
    return false; // Stack underflow
  }
  Node *top_node = stack->top->next;
  *result = top_node->data;
  stack->top->next = top_node->next;
  free(top_node);
  return true;
}

bool stack_peek(const Stack *stack, ElemType *result) {
  if (stack_is_empty(stack)) {
    return false; // Stack underflow
  }
  *result = stack->top->next->data;
  return true;
}
