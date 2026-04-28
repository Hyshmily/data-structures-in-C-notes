#include "queue.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
  char data;
  struct TreeNode *left;
  struct TreeNode *right;
} TreeNode;

TreeNode *createNode(char data) {
  TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
  newNode->data = data;
  newNode->left = NULL;
  newNode->right = NULL;
  return newNode;
}

void destroyTree(TreeNode *root) {
  if (root != NULL) {
    destroyTree(root->left);
    destroyTree(root->right);
    free(root);
  }
}

/*
 * 核心打印函数（侧置旋转风格）
 *
 * 树以顺时针旋转90°的方式呈现：
 *   - 右子树在上方
 *   - 根节点居中
 *   - 左子树在下方
 *
 * 参数：
 *   node   - 当前节点
 *   prefix - 当前行前缀字符串（用于缩进和连线）
 *   is_left - 当前节点是否为左子节点
 */
static void print_tree_impl(const TreeNode *node, const char *prefix,
                            int is_left) {
  if (!node)
    return;

  /* 右子树先递归（打印在上方） */
  {
    char new_prefix[256];
    snprintf(new_prefix, sizeof(new_prefix), "%s%s", prefix,
             is_left ? "│   " : "    ");
    print_tree_impl(node->right, new_prefix, 0);
  }

  /* 打印当前节点 */
  printf("%s%s[%c]\n", prefix, is_left ? "└── " : "┌── ", node->data);

  /* 左子树递归（打印在下方） */
  {
    char new_prefix[256];
    snprintf(new_prefix, sizeof(new_prefix), "%s%s", prefix,
             is_left ? "    " : "│   ");
    print_tree_impl(node->left, new_prefix, 1);
  }
}

/*
 * 对外接口：打印整棵树
 */
void print_tree(const TreeNode *root) {
  if (!root) {
    printf("(empty tree)\n");
    return;
  }
  print_tree_impl(root->right, "    ", 0);
  printf("[%c]\n", root->data);
  print_tree_impl(root->left, "    ", 1);
}

void level_order(TreeNode *root) {
  if (root == NULL) {
    return;
  }

  Queue *q = queue_init();
  queue_enqueue(q, root);

  void *value = NULL;
  while (queue_deq(q, &value)) {
    TreeNode *node = (TreeNode *)value;
    printf("%c ", node->data);

    if (node->left != NULL) {
      queue_enqueue(q, node->left);
    }
    if (node->right != NULL) {
      queue_enqueue(q, node->right);
    }
  }

  queue_destroy(q);
}

static TreeNode *createSampleTree(void) {
  TreeNode *a = createNode('A');
  TreeNode *b = createNode('B');
  TreeNode *c = createNode('C');
  TreeNode *d = createNode('D');
  TreeNode *e = createNode('E');
  TreeNode *f = createNode('F');
  TreeNode *g = createNode('G');

  a->left = b;
  a->right = c;
  b->left = d;
  b->right = e;
  c->left = f;
  c->right = g;

  return a;
}

int main(void) {
  TreeNode *root = createSampleTree();

  print_tree(root);
  printf("level order: ");
  level_order(root);
  printf("\n");

  destroyTree(root);
  return 0;
}
