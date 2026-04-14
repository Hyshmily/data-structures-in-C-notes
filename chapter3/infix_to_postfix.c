#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 1024

// Operator stack (char-based)
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

int precedence(char op) {
  if (op == '*' || op == '/')
    return 2;
  if (op == '+' || op == '-')
    return 1;
  return 0;
}

// Convert a general infix expression (space-separated tokens) to postfix.
// The result is written into `out` (caller must provide a buffer of at least
// MAX_LEN bytes).  Tokens in the output are separated by single spaces.
void infix_to_postfix(const char *exp, char *out) {
  OpStack *ops = opstack_init();

  char buf[MAX_LEN];
  strncpy(buf, exp, sizeof(buf) - 1);
  buf[sizeof(buf) - 1] = '\0';

  out[0] = '\0';
  bool first = true; // track whether we need a leading space

  char *token = strtok(buf, " ");
  while (token != NULL) {
    if (strcmp(token, "(") == 0) {
      opstack_push(ops, '(');
    } else if (strcmp(token, "+") == 0 || strcmp(token, "-") == 0 ||
               strcmp(token, "*") == 0 || strcmp(token, "/") == 0) {
      // Pop operators with higher or equal precedence to the output first
      while (!opstack_is_empty(ops) && opstack_peek(ops) != '(' &&
             precedence(opstack_peek(ops)) >= precedence(token[0])) {
        char op[3] = {opstack_pop(ops), '\0'};
        if (!first)
          strcat(out, " ");
        strcat(out, op);
        first = false;
      }
      opstack_push(ops, token[0]);
    } else if (strcmp(token, ")") == 0) {
      // Pop until matching '('
      while (!opstack_is_empty(ops) && opstack_peek(ops) != '(') {
        char op[3] = {opstack_pop(ops), '\0'};
        if (!first)
          strcat(out, " ");
        strcat(out, op);
        first = false;
      }
      opstack_pop(ops); // discard '('
    } else {
      // Operand: copy directly to output
      if (!first)
        strcat(out, " ");
      strcat(out, token);
      first = false;
    }
    token = strtok(NULL, " ");
  }

  // Flush remaining operators
  while (!opstack_is_empty(ops)) {
    char op[3] = {opstack_pop(ops), '\0'};
    if (!first)
      strcat(out, " ");
    strcat(out, op);
    first = false;
  }

  opstack_destroy(ops);
}

int main() {
  struct {
    const char *infix;
    const char *expected_postfix;
  } tests[] = {{"3 + 4 * 2", "3 4 2 * +"},
               {"( 3 + 4 ) * 2", "3 4 + 2 *"},
               {"10 - 2 - 3", "10 2 - 3 -"},
               {"100 / 5 / 4", "100 5 / 4 /"},
               {"1 + ( ( 2 + 3 ) * ( 4 * 5 ) )", "1 2 3 + 4 5 * * +"},
               {"56 - 20", "56 20 -"},
               {"( 56 - 20 ) / ( 4 + 2 )", "56 20 - 4 2 + /"}};
  int n = sizeof(tests) / sizeof(tests[0]);
  for (int i = 0; i < n; i++) {
    char out[MAX_LEN];
    infix_to_postfix(tests[i].infix, out);
    int ok = strcmp(out, tests[i].expected_postfix) == 0;
    printf("infix:    %s\n", tests[i].infix);
    printf("postfix:  %s  %s\n\n", out, ok ? "OK" : "FAIL");
  }
  return 0;
}
