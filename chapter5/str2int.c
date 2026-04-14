#include <stdio.h>
#include <string.h>

/**
 * 递归将字符串前 n 个字符转换为整数
 * @param s 数字字符串
 * @param n 当前处理的字符数量
 * @return  对应的整数值
 */
int str_to_int(const char *s, int n) {
  // 基本情况：只有一个字符，直接转换
  if (n == 1) {
    return s[0] - '0';
  }

  // 递归情况：前 n-1 位的结果 * 10，再加上第 n 位的数字
  return str_to_int(s, n - 1) * 10 + (s[n - 1] - '0');
}

int main() {
  const char *s = "13531";
  int len = strlen(s);
  int result = str_to_int(s, len);
  printf("字符串 \"%s\" 转换结果为：%d\n", s, result); // 输出：13531
  return 0;
}
