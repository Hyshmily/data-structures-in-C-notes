#pragma once

#include <stdbool.h>

struct QueueNode;
typedef struct QueueNode QueueNode;

struct Queue;
typedef struct Queue Queue;

Queue *queue_init();

void queue_destroy(Queue *q);

void queue_enqueue(Queue *q, void *val);

bool queue_deq(Queue *q, void **val);
