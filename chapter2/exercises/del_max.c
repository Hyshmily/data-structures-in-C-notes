#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node *next;
} Node;

Node *list_init() {
  // return a dummy head
  Node *lst = malloc(sizeof(Node));
  lst->next = NULL;
  return lst;
}

void list_destropy(Node *head) { // head is a dummy head
  Node *current = head;
  while (current != NULL) {
    Node *next = current->next;
    free(current);
    current = next;
  }
}

void list_build_from_array_back(Node *head, int values[], size_t len) {
  Node *tail = head;
  for (size_t i = 0; i < len; i++) {
    Node *node = malloc(sizeof(Node));
    node->data = values[i];
    tail->next = node;
    tail = node;
  }
  tail->next = NULL;
}

Node *locate_max_prev(Node *head) {
  Node *max_prev = head;
  Node *current = head;
  while (current->next != NULL) {
    if (current->next->data > max_prev->next->data) {
      max_prev = current;
    }
    current = current->next;
  }
  return max_prev;
}

void list_del_max2(Node *head) {
  if (head->next == NULL) {
    return;
  }
  Node *max_prev = locate_max_prev(head);
  Node *max = max_prev->next;
  max_prev->next = max->next;
  free(max);
}

void list_del_max(Node *head) {
  if (head->next == NULL) {
    return;
  }
  Node *max_prev = head;
  Node *current = head;
  while (current->next != NULL) {
    if (current->next->data > max_prev->next->data) {
      max_prev = current;
    }
    current = current->next;
  }
  Node *max = max_prev->next;
  max_prev->next = max->next;
  free(max);
}

void list_display(Node *head) {
  Node *current = head->next;
  while (current != NULL) {
    printf("%d->", current->data);
    current = current->next;
  }
  puts("\n");
}

int main() {
  Node *lst = list_init();
  int values[] = {1, 3, 5, 8, 7, 2, 6};
  list_build_from_array_back(lst, values, 7);
  list_display(lst);
  list_del_max(lst);
  list_display(lst);
  list_del_max2(lst);
  list_display(lst);
  list_destropy(lst);
  return 0;
}
