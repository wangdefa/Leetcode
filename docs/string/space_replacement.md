[TOC]
#### Space Replacement

------

##### Problem description

给定一个字符串$s$, 其中含有若干空格，对于每一个空格，将其替换为"%sp"。要求其空间复杂度为$O(1)$, 原先的字符串$s$足够存下最终替换后的结果。
eg:
$s$ = " ab c ", return "%spab%spc%sp"。

##### Algorithm description and certification

1. 设$s$的长度为：$l$，从前往后扫描一遍字符串$s$, 记录其中空格字符个数$c$;
2. 计算最终的字符串长度：$l+2c$；重新分配当前字符串空间；
3. 从后往前扫描，将空格替换为字符串。

```cpp
// Get the new length of the string
l = s.size();
c = 0;
space = ' ';
for (i = 0; i < l; i++)
    if (s[i] == space)
        c++;

// reallocate the string s
s.resize(l + 2 * c);

// replace the space with %sp
j = l + 2 * c - 1;
i = l - 1;
for (; i >= 0; i--)
    if (s[i] == space)
        s[j--] = 'p';
		s[j--] = 's';
		s[j--] = '%';
	else
        s[j--] = s[i];

return l + 2 * c; // the new length of the string
```

##### Code

```cpp
int32_t ReplaceSpace(std::string &s) {
  // Replace the space with %sp in string s
  // Get the new length of the string
  uint32_t len = s.size();
  uint32_t count = 0;
  char space = ' ';
  for (int32_t i = 0; i < len; i++)
    if (s[i] == space) count++;

  // reallocate the string s
  s.resize(len + 2 * count);

  // replace the space with %sp
  int32_t j = len + 2 * count - 1;
  int32_t i = len - 1;
  for (; i >= 0; i--)
    if (s[i] == space) {
      s[j--] = 'p';
      s[j--] = 's';
      s[j--] = '%';
    } else {
      s[j--] = s[i];
    }
  return len + 2 * count;  // the new length of the string
}
```

##### Reference

...