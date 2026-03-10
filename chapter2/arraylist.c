#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#define INIT_CAPACITY 10

typedef struct {
  int *data;         // 数据数组
  size_t size;       // 当前元素数量
  size_t capacity;   // 当前容量
} List;

static bool list_resize(List *list, size_t new_capacity) {
  int *new_data = (int *)realloc(list->data, sizeof(int) * new_capacity);
  if (new_data == NULL) {
    return false;
  }
  list->data = new_data;
  list->capacity = new_capacity;
  return true;
}

static bool list_expand_if_needed(List *list) {
  if (list->size < list->capacity) {
    return true;
  }
  size_t new_capacity = list->capacity == 0 ? INIT_CAPACITY : list->capacity * 2;
  return list_resize(list, new_capacity);
}

static void list_shrink_if_needed(List *list) {
  if (list->capacity <= INIT_CAPACITY) {
    return;
  }
  if (list->size * 4 > list->capacity) {
    return;
  }

  size_t new_capacity = list->capacity / 2;
  if (new_capacity < INIT_CAPACITY) {
    new_capacity = INIT_CAPACITY;
  }
  list_resize(list, new_capacity);
}

void list_init(List *list) {
  list->capacity = INIT_CAPACITY;
  list->size = 0;
  list->data = (int *)malloc(sizeof(int) * list->capacity);
}

void list_destroy(List *list) {
  if (list == NULL) {
    return;
  }
  free(list->data);
  list->data = NULL;
  list->size = 0;
  list->capacity = 0;
}

bool list_is_empty(const List *list) { return list == NULL || list->size == 0; }

int list_get(const List *list, size_t index, int *value) {
  if (list == NULL || value == NULL || index >= list->size) {
    return -1;
  }
  *value = list->data[index];
  return 0;
}

bool list_insert(List *list, size_t index, int value) {
  if (list == NULL || index > list->size) {
    return false;
  }
  if (!list_expand_if_needed(list)) {
    return false;
  }

  for (size_t i = list->size; i > index; --i) {
    list->data[i] = list->data[i - 1];
  }
  list->data[index] = value;
  ++list->size;
  return true;
}

bool list_append(List *list, int value) { return list_insert(list, list->size, value); }

bool list_delete_at(List *list, size_t index) {
  if (list == NULL || index >= list->size) {
    return false;
  }

  for (size_t i = index; i + 1 < list->size; ++i) {
    list->data[i] = list->data[i + 1];
  }
  --list->size;
  list_shrink_if_needed(list);
  return true;
}

bool list_delete_value(List *list, int value) {
  if (list == NULL) {
    return false;
  }

  for (size_t i = 0; i < list->size; ++i) {
    if (list->data[i] == value) {
      return list_delete_at(list, i);
    }
  }
  return false;
}

size_t list_remove_all(List *list, int value) {
  if (list == NULL) {
    return 0;
  }

  size_t write = 0;
  for (size_t read = 0; read < list->size; ++read) {
    if (list->data[read] != value) {
      list->data[write++] = list->data[read];
    }
  }

  size_t removed = list->size - write;
  list->size = write;
  list_shrink_if_needed(list);
  return removed;
}

static void assert_list_value(const List *list, size_t index, int expected) {
  int value = 0;
  assert(list_get(list, index, &value) == 0);
  assert(value == expected);
}

int main(void) {
  List list;
  int value = 0;

  list_init(&list);
  assert(list.data != NULL);
  assert(list_is_empty(&list));
  assert(list.size == 0);
  assert(list.capacity == INIT_CAPACITY);
  assert(list_get(&list, 0, &value) == -1);

  assert(list_append(&list, 10));
  assert(list_append(&list, 30));
  assert(list_insert(&list, 1, 20));
  assert(!list_is_empty(&list));
  assert(list.size == 3);
  assert_list_value(&list, 0, 10);
  assert_list_value(&list, 1, 20);
  assert_list_value(&list, 2, 30);
  assert(!list_insert(&list, 4, 99));

  for (int i = 0; i < 8; ++i) {
    assert(list_append(&list, 40 + i));
  }
  assert(list.size == 11);
  assert(list.capacity == 20);
  assert_list_value(&list, 10, 47);

  assert(list_delete_at(&list, 1));
  assert(list.size == 10);
  assert_list_value(&list, 1, 30);
  assert(!list_delete_at(&list, 10));

  assert(list_delete_value(&list, 44));
  assert(list.size == 9);
  assert(!list_delete_value(&list, 999));

  assert(list_append(&list, 46));
  assert(list_append(&list, 46));
  assert(list_append(&list, 46));
  assert(list.size == 12);
  assert(list_remove_all(&list, 46) == 4);
  assert(list.size == 8);
  assert(list.capacity == 20);

  while (list.size > 5) {
    assert(list_delete_at(&list, list.size - 1));
  }
  assert(list.size == 5);
  assert(list.capacity == 10);

  assert_list_value(&list, 0, 10);
  assert_list_value(&list, 1, 30);
  assert_list_value(&list, 2, 40);
  assert_list_value(&list, 3, 41);
  assert_list_value(&list, 4, 42);

  list_destroy(&list);
  assert(list.data == NULL);
  assert(list.size == 0);
  assert(list.capacity == 0);

  printf("All array list tests passed.\n");
  return 0;
}
