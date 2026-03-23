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

void list_destroy(Node *head) {
  Node *current = head;
  while (current != NULL) {
    Node *next = current->next;
    free(current);
    current = next;
  }
}

void list_build_from_array(Node *head, int values[], size_t len) {
  Node *tail = head;
  for (size_t i = 0; i < len; i++) {
    Node *node = malloc(sizeof(Node));
    node->data = values[i];
    tail->next = node;
    tail = node;
  }
  tail->next = NULL;
}

void list_display(Node *head) {
  Node *current = head->next;
  while (current != NULL) {
    printf("%d->", current->data);
    current = current->next;
  }
  puts("NULL");
}

// LA和LB都是递增的，LA仅保留共同元素，删除其他节点
// 用尾插法重建 LA
void common_node(Node *LA, Node *LB) {
  Node *pa = LA->next;
  Node *pb = LB->next;
  LA->next = NULL;
  Node *pa_tail = LA;

  while (pa != NULL) {
    while (pb != NULL && pb->data < pa->data) {
      pb = pb->next;
    }

    Node *tmp = pa;
    pa = pa->next;

    if (pb != NULL && tmp->data == pb->data) {
      // 相等，尾插到 LA
      pa_tail->next = tmp;
      pa_tail = tmp;
      pb = pb->next;
    } else {
      free(tmp);
    }
  }
  pa_tail->next = NULL;
}

int main() {
  // 测试1：正常交集
  Node *LA = list_init();
  Node *LB = list_init();
  int va[] = {1, 3, 5, 7, 9};
  int vb[] = {2, 3, 5, 8, 9};
  list_build_from_array(LA, va, 5);
  list_build_from_array(LB, vb, 5);

  printf("LA: ");
  list_display(LA);
  printf("LB: ");
  list_display(LB);

  common_node(LA, LB);

  printf("交集后LA: ");
  list_display(LA);

  list_destroy(LA);
  list_destroy(LB);

  // 测试2：无交集
  printf("\n--- 测试2：无交集 ---\n");
  Node *LA2 = list_init();
  Node *LB2 = list_init();
  int va2[] = {1, 2, 3};
  int vb2[] = {4, 5, 6};
  list_build_from_array(LA2, va2, 3);
  list_build_from_array(LB2, vb2, 3);

  printf("LA2: ");
  list_display(LA2);
  printf("LB2: ");
  list_display(LB2);

  common_node(LA2, LB2);

  printf("交集后LA2: ");
  list_display(LA2);

  list_destroy(LA2);
  list_destroy(LB2);

  // 测试3：完全相同
  printf("\n--- 测试3：完全相同 ---\n");
  Node *LA3 = list_init();
  Node *LB3 = list_init();
  int va3[] = {1, 2, 3};
  int vb3[] = {1, 2, 3};
  list_build_from_array(LA3, va3, 3);
  list_build_from_array(LB3, vb3, 3);

  printf("LA3: ");
  list_display(LA3);
  printf("LB3: ");
  list_display(LB3);

  common_node(LA3, LB3);

  printf("交集后LA3: ");
  list_display(LA3);

  list_destroy(LA3);
  list_destroy(LB3);

  return 0;
}
