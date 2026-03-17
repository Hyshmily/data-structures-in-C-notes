#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct Node {
  ElemType data;
  struct Node *prev;
  struct Node *next;
} Node;

typedef struct DoublyLinkedList {
  Node *head; // NOTE that there is no dummy head
} DoublyLinkedList;

Node *list_search(const DoublyLinkedList *list, ElemType e) {
  Node *current = list->head;
  while (current != NULL && current->data != e) {
    current = current->next;
  }
  return current;
}

void list_prepend(DoublyLinkedList *list, ElemType e) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  new_node->data = e;
  new_node->next = list->head;
  new_node->prev = NULL;

  if (list->head != NULL) {
    list->head->prev = new_node;
  }
  list->head = new_node;
}

void list_delete_node(DoublyLinkedList *list, Node *node) {
  if (node == NULL) {
    return;
  }
  if (node->prev != NULL) {
    node->prev->next = node->next;
  } else {
    // Deleting the head node
    list->head = node->next;
  }
  if (node->next != NULL) {
    node->next->prev = node->prev;
  }
  free(node);
}

void list_delete(DoublyLinkedList *list, ElemType e) {
  Node *node = list_search(list, e);
  list_delete_node(list, node);
}

DoublyLinkedList *list_init(void) {
  DoublyLinkedList *list = (DoublyLinkedList *)malloc(sizeof(DoublyLinkedList));
  list->head = NULL;
  return list;
}

void list_destroy(DoublyLinkedList *list) {
  if (list == NULL) {
    return;
  }
  Node *current = list->head;
  while (current != NULL) {
    Node *next = current->next;
    free(current);
    current = next;
  }
  list->head = NULL;
  free(list);
}

void list_display(const DoublyLinkedList *list) {
  Node *current = list->head;
  while (current != NULL) {
    printf("%d ", current->data);
    current = current->next;
  }
  printf("\n");
}

static bool list_equals(const DoublyLinkedList *list, const ElemType values[],
                        size_t count) {
  Node *current = list->head;
  size_t i = 0;

  while (current != NULL && i < count) {
    if (current->data != values[i]) {
      return false;
    }
    if (current->prev == NULL) {
      if (i != 0) {
        return false;
      }
    } else if (current->prev->next != current) {
      return false;
    }
    if (current->next != NULL && current->next->prev != current) {
      return false;
    }
    current = current->next;
    ++i;
  }

  return current == NULL && i == count;
}

int main(void) {
  DoublyLinkedList *list = list_init();

  assert(list != NULL);
  assert(list->head == NULL);
  assert(list_search(list, 42) == NULL);

  list_prepend(list, 3);
  list_prepend(list, 2);
  list_prepend(list, 1);

  ElemType expected1[] = {1, 2, 3};
  assert(list_equals(list, expected1, 3));

  Node *node2 = list_search(list, 2);
  assert(node2 != NULL);
  assert(node2->data == 2);
  assert(node2->prev != NULL && node2->prev->data == 1);
  assert(node2->next != NULL && node2->next->data == 3);

  list_delete(list, 99);
  assert(list_equals(list, expected1, 3));

  list_delete_node(list, node2);
  ElemType expected2[] = {1, 3};
  assert(list_equals(list, expected2, 2));

  list_delete(list, 1);
  ElemType expected3[] = {3};
  assert(list_equals(list, expected3, 1));
  assert(list->head != NULL && list->head->prev == NULL);

  list_delete(list, 3);
  assert(list->head == NULL);
  assert(list_search(list, 3) == NULL);

  list_delete_node(list, NULL);
  assert(list->head == NULL);

  list_destroy(list);
  puts("All doubly linked list tests passed.");
  return 0;
}
