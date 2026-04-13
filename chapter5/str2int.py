def str_to_int(s: str) -> int:
    # 基本情况：只有一个字符，直接转换
    if len(s) == 1:
        return ord(s[0]) - ord("0")

    # 递归情况：去掉最后一个字符的子串 * 10，再加上最后一位
    return str_to_int(s[:-1]) * 10 + (ord(s[-1]) - ord("0"))


if __name__ == "__main__":
    s = "13531"
    print(f'字符串 "{s}" 转换结果为：{str_to_int(s)}')  # 输出：13531
