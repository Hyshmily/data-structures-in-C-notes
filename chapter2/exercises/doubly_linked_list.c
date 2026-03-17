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

typedef Node *Link;

typedef struct DoublyLinkedList {
  Link header;  // dummy head
  Link trailer; // dummy tail
} DoublyLinkedList;

static Link node_create(ElemType e) {
  Link node = (Link)malloc(sizeof(Node));
  assert(node != NULL);
  node->data = e;
  node->prev = NULL;
  node->next = NULL;
  return node;
}

DoublyLinkedList list_init(void) {
  DoublyLinkedList list;
  list.header = node_create(0);
  list.trailer = node_create(0);
  list.header->next = list.trailer;
  list.trailer->prev = list.header;
  return list;
}

bool list_is_empty(const DoublyLinkedList *list) {
  return list->header->next == list->trailer;
}

static void insert_between(Link prev, Link next, Link node) {
  node->prev = prev;
  node->next = next;
  prev->next = node;
  next->prev = node;
}

void list_add_first(DoublyLinkedList *list, ElemType e) {
  insert_between(list->header, list->header->next, node_create(e));
}

void list_add_last(DoublyLinkedList *list, ElemType e) {
  insert_between(list->trailer->prev, list->trailer, node_create(e));
}

void list_insert_after(Link p, ElemType e) {
  assert(p != NULL && p->next != NULL);
  insert_between(p, p->next, node_create(e));
}

void list_insert_before(Link p, ElemType e) {
  assert(p != NULL && p->prev != NULL);
  insert_between(p->prev, p, node_create(e));
}

static ElemType remove_node(Link node) {
  ElemType value = node->data;
  node->prev->next = node->next;
  node->next->prev = node->prev;
  free(node);
  return value;
}

bool list_remove_first(DoublyLinkedList *list, ElemType *out) {
  if (list_is_empty(list)) {
    return false;
  }
  ElemType value = remove_node(list->header->next);
  if (out != NULL) {
    *out = value;
  }
  return true;
}

bool list_remove_last(DoublyLinkedList *list, ElemType *out) {
  if (list_is_empty(list)) {
    return false;
  }
  ElemType value = remove_node(list->trailer->prev);
  if (out != NULL) {
    *out = value;
  }
  return true;
}

bool list_remove_node(Link node, ElemType *out) {
  if (node == NULL || node->prev == NULL || node->next == NULL) {
    return false;
  }
  ElemType value = remove_node(node);
  if (out != NULL) {
    *out = value;
  }
  return true;
}

Link list_find(const DoublyLinkedList *list, ElemType e) {
  for (Link current = list->header->next; current != list->trailer;
       current = current->next) {
    if (current->data == e) {
      return current;
    }
  }
  return NULL;
}

size_t list_length(const DoublyLinkedList *list) {
  size_t length = 0;
  for (Link current = list->header->next; current != list->trailer;
       current = current->next) {
    ++length;
  }
  return length;
}

void list_display_forward(const DoublyLinkedList *list) {
  for (Link current = list->header->next; current != list->trailer;
       current = current->next) {
    printf("%d ", current->data);
  }
  printf("\n");
}

void list_display_backward(const DoublyLinkedList *list) {
  for (Link current = list->trailer->prev; current != list->header;
       current = current->prev) {
    printf("%d ", current->data);
  }
  printf("\n");
}

void list_clear(DoublyLinkedList *list) {
  Link current = list->header->next;
  while (current != list->trailer) {
    Link next = current->next;
    free(current);
    current = next;
  }
  list->header->next = list->trailer;
  list->trailer->prev = list->header;
}

void list_destroy(DoublyLinkedList *list) {
  list_clear(list);
  free(list->header);
  free(list->trailer);
  list->header = NULL;
  list->trailer = NULL;
}

static bool list_equals(const DoublyLinkedList *list, const ElemType values[],
                        size_t count) {
  Link current = list->header->next;
  size_t i = 0;

  while (current != list->trailer && i < count) {
    if (current->data != values[i]) {
      return false;
    }
    current = current->next;
    ++i;
  }

  return current == list->trailer && i == count;
}

int main(void) {
  DoublyLinkedList list = list_init();
  ElemType removed = 0;

  assert(list_is_empty(&list));
  assert(list_length(&list) == 0);

  list_add_first(&list, 2);
  list_add_first(&list, 1);
  list_add_last(&list, 4);
  Link node2 = list_find(&list, 2);
  assert(node2 != NULL);
  list_insert_after(node2, 3);

  ElemType expected1[] = {1, 2, 3, 4};
  assert(list_equals(&list, expected1, 4));
  assert(list_length(&list) == 4);

  Link node4 = list_find(&list, 4);
  assert(node4 != NULL);
  list_insert_before(node4, 99);
  ElemType expected2[] = {1, 2, 3, 99, 4};
  assert(list_equals(&list, expected2, 5));

  assert(list_remove_first(&list, &removed) && removed == 1);
  assert(list_remove_last(&list, &removed) && removed == 4);
  ElemType expected3[] = {2, 3, 99};
  assert(list_equals(&list, expected3, 3));

  Link node99 = list_find(&list, 99);
  assert(node99 != NULL);
  assert(list_remove_node(node99, &removed) && removed == 99);
  ElemType expected4[] = {2, 3};
  assert(list_equals(&list, expected4, 2));

  list_clear(&list);
  assert(list_is_empty(&list));
  assert(!list_remove_first(&list, NULL));
  assert(!list_remove_last(&list, NULL));

  list_destroy(&list);
  puts("All doubly linked list tests passed.");
  return 0;
}
