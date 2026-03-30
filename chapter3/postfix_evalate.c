#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 1024

double evaluate(char *exp) {
  Stack *stack = stack_init();

  char buf[MAX_LEN];
  strncpy(buf, exp, sizeof(buf) - 1);
  buf[sizeof(buf) - 1] = '\0';

  char *token = strtok(buf, " ");
  while (token != NULL) {
    if (strcmp(token, "+") == 0) {
      double a, b;
      stack_pop(stack, &a);
      stack_pop(stack, &b);
      stack_push(stack, b + a);
    } else if (strcmp(token, "-") == 0) {
      double a, b;
      stack_pop(stack, &a);
      stack_pop(stack, &b);
      stack_push(stack, b - a);
    } else if (strcmp(token, "*") == 0) {
      double a, b;
      stack_pop(stack, &a);
      stack_pop(stack, &b);
      stack_push(stack, b * a);
    } else if (strcmp(token, "/") == 0) {
      double a, b;
      stack_pop(stack, &a);
      stack_pop(stack, &b);
      stack_push(stack, b / a); // ignore the case when a is zero
    } else {
      // it is number
      char *end;
      double v = strtod(token, &end);
      stack_push(stack, v);
    }
    token = strtok(NULL, " ");
  }
  double result;
  stack_pop(stack, &result);
  stack_destroy(stack);
  return result;
}

int main() {
  char exp[] = "56 20 - 4 2 + /";
  double result = evaluate(exp);
  printf("The result is %f\n", result);
}
