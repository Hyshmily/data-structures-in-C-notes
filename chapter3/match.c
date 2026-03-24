#include "stack.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>

static bool is_left(char c) { return c == '(' || c == '[' || c == '{'; }

static bool is_right(char c) { return c == ')' || c == ']' || c == '}'; }

static bool is_match(char left, char right) {
  return (left == '(' && right == ')') || (left == '[' && right == ']') ||
         (left == '{' && right == '}');
}

bool is_balanced(const char exp[], size_t n) {
  Stack *stack = stack_init();

  for (size_t i = 0; i < n; i++) {
    char c = exp[i];
    if (is_left(c)) {
      stack_push(stack, c);
    } else if (is_right(c)) {
      ElemType top;
      if (!stack_pop(stack, &top) || !is_match(top, c)) {
        stack_destroy(stack);
        return false;
      }
    }
  }

  bool result = stack_is_empty(stack);
  stack_destroy(stack);
  return result;
}

int main() {
  // Test balanced strings
  assert(is_balanced("()", 2) == true);
  assert(is_balanced("[]", 2) == true);
  assert(is_balanced("{}", 2) == true);
  assert(is_balanced("()[]{}", 6) == true);
  assert(is_balanced("([{}])", 6) == true);
  assert(is_balanced("{[()]}", 6) == true);
  assert(is_balanced("((()))", 6) == true);
  assert(is_balanced("", 0) == true);
  assert(is_balanced("a(b)c[d]e{f}g", 13) == true);

  // Test unbalanced strings
  assert(is_balanced("(", 1) == false);
  assert(is_balanced(")", 1) == false);
  assert(is_balanced("(]", 2) == false);
  assert(is_balanced("([)]", 4) == false);
  assert(is_balanced("{[}", 3) == false);
  assert(is_balanced("((())", 5) == false);
  assert(is_balanced("(()))", 5) == false);

  printf("All tests passed\n");
  return 0;
}
