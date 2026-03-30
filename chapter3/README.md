# 第3章：栈与队列

## 3.1 

`GetTop`操作也一般被称为`peek`。

后缀表达式的求解非常经典。但是由于C语言中并没有原生的字符串类型，在操作的时候稍显麻烦，比如不像Java/Python等语言方便地分隔字符串。`strtok`函数完成这个目的：

```c
#include <stdio.h>
#include <string.h>

void split(char *s) {
    char *token = strtok(s, " ");
    while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, " ");
    }
}

int main(void) {
    char str[] = "hello world this is C";
    split(str);
    return 0;
}
```

另一方面，如何高效求解有括号的中缀表达式`( 1 + ( ( 2 + 3 ) * ( 4 * 5 ) ) )`的值呢？E.W.Dijkstra提出了著名的**双栈算法**，使用一个栈存储操作数，另一个栈存储运算符。算法的核心思想是：*当遇到一个操作数时，将其压入操作数栈；当遇到一个运算符时，将其压入运算符栈；当遇到一个右括号时，从运算符栈中弹出一个运算符，并从操作数栈中弹出两个操作数，进行计算后将结果压回操作数栈*。

## 3.2

对于循环队列，另外一种关于`front`和`rear`的定义是：**front指向队头元素，rear指向队尾元素的下一个位置**。

![circular_queue](circle_queue.png)