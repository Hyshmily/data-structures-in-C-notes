#include "stack.h"
#include <assert.h>
#include <stdio.h>

int main() {
  // Test stack_init and stack_is_empty
  Stack *stack = stack_init();
  assert(stack != NULL);
  assert(stack_is_empty(stack));

  // Test stack_peek on empty stack
  ElemType val;
  assert(stack_peek(stack, &val) == false);

  // Test stack_push
  assert(stack_push(stack, 10) == true);
  assert(stack_push(stack, 20) == true);
  assert(stack_push(stack, 30) == true);
  assert(!stack_is_empty(stack));

  // Test stack_peek (does not modify stack)
  assert(stack_peek(stack, &val) == true);
  assert(val == 30);
  assert(stack_peek(stack, &val) == true);
  assert(val == 30); // still 30, peek doesn't pop

  // Test stack_pop (LIFO order)
  assert(stack_pop(stack, &val) == true);
  assert(val == 30);

  assert(stack_pop(stack, &val) == true);
  assert(val == 20);

  assert(stack_pop(stack, &val) == true);
  assert(val == 10);

  // Stack should be empty after popping all elements
  assert(stack_is_empty(stack));

  // Test stack_pop on empty stack
  assert(stack_pop(stack, &val) == false);

  // Test stack_destroy
  stack_destroy(stack);

  printf("All tests passed\n");
  return 0;
}
