#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char data;
    struct node *left;
    struct node *right;
} Node;

typedef struct stack {
    Node* data[100];
    int top;
} Stack;

Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = -1;
    return stack;
}
void push(Stack* stack, Node* node) {
    stack->data[++stack->top] = node;
}

Node* pop(Stack* stack) {
    return stack->data[stack->top--];
}

void destroyStack(Stack* stack) {
    free(stack);
}

Node* createNode(char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
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
    int child = 0;  // 1: left child, 2: right child

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

// 按括号表达式输出二叉树，例如 A(B(D,E),C(F,G))
void displayTree(Node* root) {
    if (root == NULL) {
        return;
    }

    printf("%c", root->data);
    if (root->left != NULL || root->right != NULL) {
        printf("(");
        displayTree(root->left);
        if (root->right != NULL)
            printf(",");
        displayTree(root->right);
        printf(")");
    }
}

size_t height(Node* root) {
    if (root == NULL) {
        return 0;
    }
    size_t leftHeight = height(root->left);
    size_t rightHeight = height(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

Node *findNode(Node* root, char data) {
    if (root == NULL) {
        return NULL;
    }
    if (root->data == data) {
        return root;
    }
    Node* leftResult = findNode(root->left, data);
    if (leftResult != NULL) {
        return leftResult;
    }
    return findNode(root->right, data);
}

Node *leftMostNode(Node* root) {
    if (root == NULL) {
        return NULL;
    }
    Node *current = root;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

Node *leftMostNodeRecursive(Node* root) {
    if (root == NULL) {
        return NULL;
    }
    if (root->left == NULL) {
        return root;
    }
    return leftMostNodeRecursive(root->left);
}

Node *rightMostNode(Node* root) {
    if (root == NULL) {
        return NULL;
    }
    Node *current = root;
    while (current->right != NULL) {
        current = current->right;
    }
    return current;
}

Node *rightMostNodeRecursive(Node* root) {
    if (root == NULL) {
        return NULL;
    }
    if (root->right == NULL) {
        return root;
    }
    return rightMostNodeRecursive(root->right);
}

void inOrder(Node* root) {
    if (root == NULL) {
        return;
    }
    inOrder(root->left);
    printf("%c ", root->data);
    inOrder(root->right);
}

void preOrder(Node* root) {
    if (root == NULL) {
        return;
    }
    printf("%c ", root->data);
    preOrder(root->left);
    preOrder(root->right);
}

void postOrder(Node* root) {
    if (root == NULL) {
        return;
    }
    postOrder(root->left);
    postOrder(root->right);
    printf("%c ", root->data);
}

void destroyTree(Node* root) {
    if (root != NULL) {
        destroyTree(root->left);
        destroyTree(root->right);
        free(root);
    }
}

int main(void) {
    char str[] = "A(B(,E),C(F,G))";

    Node *root = createTree(str);
    if (root == NULL) {
        printf("createTree failed\n");
        return 1;
    }

    printf("input:   %s\n", str);
    printf("output(stack): ");
    displayTree(root);
    printf("\n");

    printf("height(stack): %zu\n", height(root));

    Node *target = findNode(root, 'E');
    if (target != NULL) {
        printf("find 'E' in stack tree: found\n");
    } else {
        printf("find 'E' in stack tree: not found\n");
    }

    Node *leftMost = leftMostNode(root);
    Node *leftMostRec = leftMostNodeRecursive(root);
    if (leftMost != NULL) {
        printf("leftMost(iter): %c\n", leftMost->data);
    } else {
        printf("leftMost(iter): NULL\n");
    }
    if (leftMostRec != NULL) {
        printf("leftMost(rec):  %c\n", leftMostRec->data);
    } else {
        printf("leftMost(rec):  NULL\n");
    }

    Node *rightMost = rightMostNode(root);
    Node *rightMostRec = rightMostNodeRecursive(root);
    if (rightMost != NULL) {
        printf("rightMost(iter): %c\n", rightMost->data);
    } else {
        printf("rightMost(iter): NULL\n");
    }
    if (rightMostRec != NULL) {
        printf("rightMost(rec):  %c\n", rightMostRec->data);
    } else {
        printf("rightMost(rec):  NULL\n");
    }

    destroyTree(root);
    return 0;
}

