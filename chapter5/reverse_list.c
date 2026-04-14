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

void list_display(List list) {
  Link current = list->next;
  while (current) {
    printf("%d ->", current->data);
    current = current->next;
  }
  printf("\n");
}

/* 递归辅助函数：翻转从 current 开始的链表，返回新的头节点 */
static Link reverse_recursive(Link current, Link prev) {
  if (current == NULL)
    return prev; /* 到达末尾，prev 就是新的头节点 */

  Link next = current->next;
  current->next = prev;                    /* 反转指针方向 */
  return reverse_recursive(next, current); /* 继续递归 */
}

/* 翻转链表（带哑节点的版本） */
void list_reverse(List lst) {
  /* lst 是哑节点（header），真正的数据从 lst->next 开始 */
  Link new_head = reverse_recursive(lst->next, NULL);
  lst->next = new_head;
}

void list_prepend(List lst, ElemType val) {
  Link node = (Link)malloc(sizeof(struct Node));
  node->data = val;
  node->next = lst->next;
  lst->next = node;
}

int main(void) {
  List lst = list_init();

  // 构建链表 1 -> 2 -> 3 -> 4 -> 5
  for (int i = 5; i >= 1; i--) {
    list_prepend(lst, i);
  }

  printf("原始链表: ");
  list_display(lst);

  list_reverse(lst);
  printf("翻转之后: ");
  list_display(lst);

  // 单元素
  List single = list_init();
  list_prepend(single, 42);
  printf("单元素翻转前: ");
  list_display(single);
  list_reverse(single);
  printf("单元素翻转后: ");
  list_display(single);

  // 空链表
  List empty = list_init();
  printf("空链表翻转前: ");
  list_display(empty);
  list_reverse(empty);
  printf("空链表翻转后: ");
  list_display(empty);

  list_destroy(lst);
  list_destroy(single);
  list_destroy(empty);
  return 0;
}
