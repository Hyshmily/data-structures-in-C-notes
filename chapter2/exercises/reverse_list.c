#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

struct Node;

typedef struct Node *Link;
typedef struct Node *List;

struct Node {
  ElemType data;
  Link next;
};

List list_init(void) {
  // it returns a pointer to header (a dummy node)
  List L = (List)malloc(sizeof(struct Node));
  L->next = NULL;
  return L;
}

void list_destroy(List lst) {
  Link current = lst;
  while (current != NULL) {
    Link next = current->next;
    free(current);
    current = next;
  }
}

void list_reverse(List lst) {
  Link prev = NULL;
  Link current = lst->next; // skip the header node
  while (current != NULL) {
    Link next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }
  lst->next = prev; // update the header to point to the new first node
}

List list_build_from_array(ElemType values[], size_t count) {
  List lst = list_init();
  Link tail = lst;
  for (size_t i = 0; i < count; ++i) {
    Link new_node = (Link)malloc(sizeof(struct Node));
    new_node->data = values[i];
    new_node->next = NULL;
    tail->next = new_node;
    tail = new_node;
  }
  return lst;
}

void list_display(const List lst) {
  Link current = lst->next; // skip the header node
  while (current != NULL) {
    printf("%d ", current->data);
    current = current->next;
  }
  printf("\n");
}

static bool list_equals(const List lst, const ElemType values[], size_t count) {
  Link current = lst->next;
  size_t i = 0;

  while (current != NULL && i < count) {
    if (current->data != values[i]) {
      return false;
    }
    current = current->next;
    ++i;
  }

  return current == NULL && i == count;
}

int main(void) {
  List empty = list_init();
  list_reverse(empty);
  assert(list_equals(empty, NULL, 0));
  list_destroy(empty);

  ElemType single_values[] = {42};
  List single = list_build_from_array(single_values, 1);
  list_reverse(single);
  assert(list_equals(single, single_values, 1));
  list_destroy(single);

  ElemType values[] = {1, 2, 3, 4, 5};
  ElemType reversed[] = {5, 4, 3, 2, 1};
  List multi = list_build_from_array(values, 5);
  list_reverse(multi);
  assert(list_equals(multi, reversed, 5));
  list_destroy(multi);

  puts("All reverse_list tests passed.");
  return 0;
}
