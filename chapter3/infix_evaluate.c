#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 1024

// Operator stack (char-based, reuse pattern from fully_parenthesized.c)
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

char opstack_peek(OpStack *s) { return s->data[s->top]; }

bool opstack_is_empty(OpStack *s) { return s->top == -1; }

void opstack_destroy(OpStack *s) { free(s); }

// Returns precedence: * and / are higher than + and -
int precedence(char op) {
  if (op == '*' || op == '/') return 2;
  if (op == '+' || op == '-') return 1;
  return 0; // '(' has lowest precedence when on the stack
}

// Apply one operator to the top two operands on the value stack
void apply_op(Stack *values, char op) {
  double a, b;
  stack_pop(values, &a);
  stack_pop(values, &b);
  double result;
  switch (op) {
  case '+': result = b + a; break;
  case '-': result = b - a; break;
  case '*': result = b * a; break;
  case '/': result = b / a; break; // ignore division by zero
  default:  result = 0;
  }
  stack_push(values, result);
}

// Evaluate a general infix expression (tokens separated by spaces).
// Supports +, -, *, / with correct precedence and parentheses.
double evaluate(char *exp) {
  Stack *values = stack_init();
  OpStack *ops = opstack_init();

  char buf[MAX_LEN];
  strncpy(buf, exp, sizeof(buf) - 1);
  buf[sizeof(buf) - 1] = '\0';

  char *token = strtok(buf, " ");
  while (token != NULL) {
    if (strcmp(token, "(") == 0) {
      // Push '(' as a sentinel; it will never be popped by precedence rules
      opstack_push(ops, '(');
    } else if (strcmp(token, "+") == 0 || strcmp(token, "-") == 0 ||
               strcmp(token, "*") == 0 || strcmp(token, "/") == 0) {
      // Pop and apply all pending operators with higher or equal precedence
      // before pushing the current operator (left-associativity)
      while (!opstack_is_empty(ops) &&
             opstack_peek(ops) != '(' &&
             precedence(opstack_peek(ops)) >= precedence(token[0])) {
        apply_op(values, opstack_pop(ops));
      }
      opstack_push(ops, token[0]);
    } else if (strcmp(token, ")") == 0) {
      // Pop and apply until the matching '(' is found
      while (!opstack_is_empty(ops) && opstack_peek(ops) != '(') {
        apply_op(values, opstack_pop(ops));
      }
      opstack_pop(ops); // discard '('
    } else {
      // Operand: parse and push onto value stack
      char *end;
      double v = strtod(token, &end);
      stack_push(values, v);
    }
    token = strtok(NULL, " ");
  }

  // Apply any remaining operators
  while (!opstack_is_empty(ops)) {
    apply_op(values, opstack_pop(ops));
  }

  double result;
  stack_pop(values, &result);
  stack_destroy(values);
  opstack_destroy(ops);
  return result;
}

int main() {
  int n = 5;
  struct { char exp[MAX_LEN]; double expected; } infix_tests[] = {
    {"3 + 4 * 2",          11.0},
    {"( 3 + 4 ) * 2",      14.0},
    {"10 - 2 - 3",          5.0},
    {"100 / 5 / 4",         5.0},
    {"1 + ( ( 2 + 3 ) * ( 4 * 5 ) )", 101.0},
  };
  for (int i = 0; i < n; i++) {
    double result = evaluate(infix_tests[i].exp);
    printf("%-40s = %g  (expected %g) %s\n",
           infix_tests[i].exp, result, infix_tests[i].expected,
           result == infix_tests[i].expected ? "OK" : "FAIL");
  }
  return 0;
}
