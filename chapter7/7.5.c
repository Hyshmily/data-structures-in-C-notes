#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  char data;
  struct node *left;
  struct node *right;
} Node;

typedef struct stack {
  Node *data[100];
  int top;
} Stack;

Stack *createStack() {
  Stack *stack = (Stack *)malloc(sizeof(Stack));
  stack->top = -1;
  return stack;
}
void push(Stack *stack, Node *node) { stack->data[++stack->top] = node; }

Node *pop(Stack *stack) { return stack->data[stack->top--]; }

void destroyStack(Stack *stack) { free(stack); }

Node *createNode(char data) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = data;
  newNode->left = NULL;
  newNode->right = NULL;
  return newNode;
}

// str是括号表示的二叉树；比如 A(B(D,E),C(F,G)), 函数返回二叉树的根节点
Node *createTree(char *str) {
  if (str == NULL) {
    return NULL;
  }

  Stack *stack = createStack();
  Node *root = NULL;
  Node *current = NULL;
  int child = 0; // 1: left child, 2: right child

  for (int i = 0; str[i] != '\0'; i++) {
    char ch = str[i];

    if (ch == '(') {
      if (current != NULL) {
        push(stack, current);
      }
      child = 1;
    } else if (ch == ',') {
      child = 2;
    } else if (ch == ')') {
      if (stack->top >= 0) {
        pop(stack);
      }
    } else {
      current = createNode(ch);

      if (root == NULL) {
        root = current;
      }

      if (stack->top >= 0) {
        Node *parent = stack->data[stack->top];
        if (child == 1) {
          parent->left = current;
        } else if (child == 2) {
          parent->right = current;
        }
      }
    }
  }

  destroyStack(stack);
  return root;
}

size_t height(Node *root) {
  if (root == NULL) {
    return 0;
  }
  size_t leftHeight = height(root->left);
  size_t rightHeight = height(root->right);
  return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int levelOfNode(Node *root, char x, int level) {
  if (root == NULL) {
    return 0;
  }
  if (root->data == x) {
    return level;
  }

  int leftLevel = levelOfNode(root->left, x, level + 1);
  if (leftLevel != 0) {
    return leftLevel;
  }

  return levelOfNode(root->right, x, level + 1);
}

int countLevelK(Node *root, int k) {
  if (root == NULL || k < 1) {
    return 0;
  }
  if (k == 1) {
    return 1;
  }
  return countLevelK(root->left, k - 1) + countLevelK(root->right, k - 1);
}

void inOrder(Node *root) {
  if (root == NULL) {
    return;
  }
  inOrder(root->left);
  printf("%c ", root->data);
  inOrder(root->right);
}

void preOrder(Node *root) {
  if (root == NULL) {
    return;
  }
  printf("%c ", root->data);
  preOrder(root->left);
  preOrder(root->right);
}

void postOrder(Node *root) {
  if (root == NULL) {
    return;
  }
  postOrder(root->left);
  postOrder(root->right);
  printf("%c ", root->data);
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
static void print_tree_impl(const Node *node, const char *prefix, int is_left) {
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
void print_tree(const Node *root) {
  if (!root) {
    printf("(empty tree)\n");
    return;
  }
  print_tree_impl(root->right, "    ", 0);
  printf("[%c]\n", root->data);
  print_tree_impl(root->left, "    ", 1);
}

/* 递归翻转：后序遍历，先翻转子树再交换 */
Node *invert_tree(Node *root) {
  if (!root)
    return NULL;

  Node *left = invert_tree(root->left);
  Node *right = invert_tree(root->right);

  root->left = right;
  root->right = left;

  return root;
}

void destroyTree(Node *root) {
  if (root != NULL) {
    destroyTree(root->left);
    destroyTree(root->right);
    free(root);
  }
}

int main(void) {
  char str[] = "A(B(,E),C(F,G))";

  Node *root = createTree(str);

  print_tree(root);

  printf("level of 'A': %d\n", levelOfNode(root, 'A', 1));
  printf("level of 'E': %d\n", levelOfNode(root, 'E', 1));
  printf("level of 'G': %d\n", levelOfNode(root, 'G', 1));
  printf("level of 'X': %d\n", levelOfNode(root, 'X', 1));

  printf("node count of level 1: %d\n", countLevelK(root, 1));
  printf("node count of level 2: %d\n", countLevelK(root, 2));
  printf("node count of level 3: %d\n", countLevelK(root, 3));
  printf("node count of level 4: %d\n", countLevelK(root, 4));

  root = invert_tree(root);

  print_tree(root);

  destroyTree(root);
  return 0;
}
