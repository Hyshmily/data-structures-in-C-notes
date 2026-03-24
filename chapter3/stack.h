#pragma once

#include <stdbool.h>

struct Stack;

typedef struct Stack Stack;

typedef int ElemType;

Stack *stack_init();

void stack_destroy(Stack *stack);

bool stack_is_empty(const Stack *stack);

bool stack_push(Stack *stack, ElemType e);

bool stack_pop(Stack *stack, ElemType *result);

bool stack_peek(const Stack *stack, ElemType *result);
