#include <stdio.h>

void funcB() {
  int varB = 444;
  printf("| [深度 1] 进入 funcB, varB 的地址: %p\n\n", (void *)&varB);
}

void funcA2() {
  int varA2 = 333;
  printf("|   | [深度 2] 进入 funcA2, varA2 的地址: %p  <-- 重点：完美复用 "
         "varA1 的位置！\n",
         (void *)&varA2);
}

void funcA1() {
  int varA1 = 222;
  printf("|   | [深度 2] 进入 funcA1, varA1 的地址: %p\n", (void *)&varA1);
}

void funcA() {
  int varA = 111;
  printf("| [深度 1] 进入 funcA, varA 的地址: %p\n\n", (void *)&varA);

  printf("| --- funcA 内部：调用 funcA1 ---\n");
  funcA1();

  printf("\n| --- funcA 内部：调用 funcA2 ---\n");
  funcA2();
}

int main() {
  int m = 0;
  printf("[深度 0] 进入 main, 变量 m 的地址: %p\n\n", (void *)&m);

  funcA();
  printf("\n");
  funcB();

  return 0;
}
