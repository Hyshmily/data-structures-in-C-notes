#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node *next;
} Node;

Node *list_init() {
  Node *head = malloc(sizeof(Node));
  head->next = NULL;
  return head;
}

void list_destory(Node *head) {
  Node *current = head->next;
  while (current != head) {
    Node *tmp = current;
    current = current->next;
    free(tmp);
  }
  free(head);
}

void build_circle(Node *head, size_t n) {
  Node *tail = head;
  for (size_t i = 1; i <= n; i++) {
    Node *node = malloc(sizeof(Node));
    node->data = i;
    tail->next = node;
    tail = node;
  }
  tail->next = head;
}

int clean(Node *head, size_t m) {
  Node *prev = head;
  Node *current = head->next;

  while (head->next->next != head) {
    for (size_t i = 1; i < m; i++) {
      prev = current;
      current = current->next;
      if (current == head) {
        prev = current;
        current = current->next;
      }
    }
    prev->next = current->next;
    printf("%d is out\n", current->data);
    free(current);

    current = prev->next;
    if (current == head) {
      prev = current;
      current = current->next;
    }
  }
  return head->next->data;
}

int main() {
  Node *head = list_init();
  build_circle(head, 7);
  int live = clean(head, 2);
  printf("%d is alive", live);
  list_destory(head);
  return 0;
}
