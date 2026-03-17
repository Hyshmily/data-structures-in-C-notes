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

void list_display(const List lst) {
  Link current = lst->next; // skip the header node
  while (current != NULL) {
    printf("%d ", current->data);
    current = current->next;
  }
  printf("\n");
}

void insert_after(Link p, ElemType e) {
  Link new_node = (Link)malloc(sizeof(struct Node));
  new_node->data = e;
  new_node->next = p->next;
  p->next = new_node;
}

void list_add_first(List lst, ElemType e) { insert_after(lst, e); }

void list_add_last(List lst, ElemType e) {
  Link current = lst; // start from the header node
  while (current->next != NULL) {
    current = current->next;
  }
  insert_after(current, e);
}

void remove_after(Link p) {
  if (p->next != NULL) {
    Link temp = p->next;
    p->next = temp->next;
    free(temp);
  }
}

void list_remove_first(List lst) { remove_after(lst); }

void list_remove_last(List lst) {
  Link current = lst; // start from the header node
  while (current->next != NULL && current->next->next != NULL) {
    current = current->next;
  }
  remove_after(current);
}

void list_split_alternating(List l1, List l2) {
  Link current = l1->next;
  Link a_tail = l1;
  bool take_a = true;

  l1->next = NULL;
  l2->next = NULL;

  while (current != NULL) {
    Link next = current->next;

    if (take_a) {
      a_tail->next = current;
      a_tail = current;
      a_tail->next = NULL;
    } else {
      current->next = l2->next;
      l2->next = current;
    }

    take_a = !take_a;
    current = next;
  }
}

List build_list_front(ElemType values[], size_t count) {
  List lst = list_init();
  for (size_t i = 0; i < count; ++i) {
    insert_after(lst, values[i]);
  }
  return lst;
}

Link insert_after_return_new(Link p, ElemType e) {
  Link new_node = (Link)malloc(sizeof(struct Node));
  new_node->data = e;
  new_node->next = p->next;
  p->next = new_node;
  return new_node;
}

Link build_list_back(ElemType values[], size_t count) {
  List lst = list_init();
  Link tail = lst;
  for (size_t i = 0; i < count; ++i) {
    tail = insert_after_return_new(tail, values[i]);
  }
  return lst;
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
  List lst = list_init();

  assert(list_equals(lst, NULL, 0));

  list_add_first(lst, 2);
  ElemType expected1[] = {2};
  assert(list_equals(lst, expected1, 1));

  list_add_first(lst, 1);
  ElemType expected2[] = {1, 2};
  assert(list_equals(lst, expected2, 2));

  list_add_last(lst, 3);
  ElemType expected3[] = {1, 2, 3};
  assert(list_equals(lst, expected3, 3));

  list_remove_first(lst);
  ElemType expected4[] = {2, 3};
  assert(list_equals(lst, expected4, 2));

  list_remove_last(lst);
  ElemType expected5[] = {2};
  assert(list_equals(lst, expected5, 1));

  list_remove_last(lst);
  assert(list_equals(lst, NULL, 0));

  list_remove_first(lst);
  assert(list_equals(lst, NULL, 0));

  list_destroy(lst);

  ElemType source_values[] = {1, 10, 2, 20, 3, 30};
  List l1 = build_list_back(source_values, 6);
  List l2 = list_init();
  ElemType expected_a[] = {1, 2, 3};
  ElemType expected_b[] = {30, 20, 10};

  list_split_alternating(l1, l2);
  assert(list_equals(l1, expected_a, 3));
  assert(list_equals(l2, expected_b, 3));

  list_destroy(l1);
  list_destroy(l2);
  puts("All list API tests passed.");
  return 0;
}
