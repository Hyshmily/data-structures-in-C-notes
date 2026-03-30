#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 1024

// Operator stack implementation
typedef struct {
  char data[MAX_LEN];
  int top;
} OpStack;

OpStack *opstack_init() {
  OpStack *s = malloc(sizeof(OpStack));
  s->top = -1;
  return s;
}

void opstack_push(OpStack *s, char op) { s->data[++s->top] = op; }

char opstack_pop(OpStack *s) { return s->data[s->top--]; }

bool opstack_is_empty(OpStack *s) { return s->top == -1; }

void opstack_destroy(OpStack *s) { free(s); }

double evaluate(char *exp) {
  Stack *values = stack_init();  // operand stack
  OpStack *ops = opstack_init(); // operator stack

  char buf[MAX_LEN];
  strncpy(buf, exp, sizeof(buf) - 1);
  buf[sizeof(buf) - 1] = '\0';

  char *token = strtok(buf, " ");
  while (token != NULL) {
    if (strcmp(token, "(") == 0) {
      // ignore left parenthesis
    } else if (strcmp(token, "+") == 0 || strcmp(token, "-") == 0 ||
               strcmp(token, "*") == 0 || strcmp(token, "/") == 0) {
      opstack_push(ops, token[0]);
    } else if (strcmp(token, ")") == 0) {
      // pop operator and two operands, compute and push result
      char op = opstack_pop(ops);
      double a, b;
      stack_pop(values, &a);
      stack_pop(values, &b);
      double result;
      switch (op) {
      case '+':
        result = b + a;
        break;
      case '-':
        result = b - a;
        break;
      case '*':
        result = b * a;
        break;
      case '/':
        result = b / a;
        break;
      default:
        result = 0;
      }
      stack_push(values, result);
    } else {
      // it is a number
      char *end;
      double v = strtod(token, &end);
      stack_push(values, v);
    }
    token = strtok(NULL, " ");
  }

  double result;
  stack_pop(values, &result);
  stack_destroy(values);
  opstack_destroy(ops);
  return result;
}

int main() {
  char exp[] = "( 1 + ( ( 2 + 3 ) * ( 4 * 5 ) ) )";
  double result = evaluate(exp);
  printf("Expression: %s\n", exp);
  printf("Result: %f\n", result);
  // Expected: 1 + ((2+3) * (4*5)) = 1 + (5 * 20) = 1 + 100 = 101
  return 0;
}
