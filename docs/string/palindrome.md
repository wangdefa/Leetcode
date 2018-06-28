[TOC]

#### Is palindrome

---
##### Problem description

给定一个字符串$s$，仅仅考虑其中的英文字母（大小写都考虑），判断其是否是回文字符串(对于空串，我们假设其为一个回文字符串)。
eg:

1. $s$ = "A man, a plan, a canal: Panama", $s$ 为一个回文字符串；
2. $s$ = "A man", $s$ 不是一个回文字符串；

##### Algorithm description and certification

此题比较简单，直接采用两个指针ptr1, ptr2，一个从前往后扫描，一个从后往前扫描即可。

##### Code
```cpp
bool IsPalindrome(const std::string &s) {
  if (s.empty()) return true;
  uint32_t ptr1 = 0;
  uint32_t ptr2 = s.size() - 1;
  auto IsChar = [](char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
  };
  while (ptr1 < ptr2) {
    while (ptr1 < ptr2 && !IsChar(s[ptr1])) ptr1++; // find a valid char
    while (ptr1 < ptr2 && !IsChar(s[ptr2])) ptr2--; // find a valid char
    if (s[ptr1] == s[ptr2] || 
        std::fabs(s[ptr1] - s[ptr2]) == std::fabs('a' - 'A')) {
      // std::cout << s[ptr1] << "\t" << s[ptr2] << std::endl;
      ptr1++, ptr2--;
    } else {
      return false; // not equal, so it is not a palindrome
    }
  }
  return true;
}
```

##### Reference

...

#### Longest palindrome substring

---

##### Problem description

给定一个字符串$s$, 找出其最长的回文子串（可能有多个，只需要能够返回一个即可）。
eg:
$s$ = "abbac", return "abba";

##### Algorithm description and certification

###### Method 1

对于每一个回文子串$sub\_s$，其必定有一个**对称中心**$x$；一方面，我们穷举其对称中心，一共有$O(n)$个；对于每一个对称中心，找出以此为中心的最长回文子串，时间复杂度为$O(n)$；故最终的时间复杂度为$O(n^2)$.

| axis   | 0    | 1    | 2    | 3    | 4    | 5    | 6    | 7    | 8    |
| ------ | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| string | s[0] |      | s[1] |      | s[2] |      | s[3] |      | s[4] |

从上面的表可以看出，当对称轴axis为偶数时，下一个需要比较的是：$s[axis/2-1], s[axis/2+1]$; 当对称轴$axis$为奇数时，下一个需要比较的是：$s[axis/2], s[axis/2+1]$。因此有如下伪代码：

```cpp
beg = end = 0; // record the (begin, end) index of longest palindrome substring
sz = s.size(); // it is an open domain
for (axis = 0; axis < sz * 2 - 1; axis++)
    if (axis % 2 == 0)
        beg_tmp = axis / 2 - 1;
		end_tmp = axis / 2 + 1;
	else // axis % 2 == 1
        beg_tmp = axis / 2;
		end_tmp = axis / 2 + 1;
    while (beg_tmp >= 0 && end_tmp < sz && s[beg_tmp] == s[end_tmp]) 
        beg_tmp--, end_tmp++;
	if (end - begin <= beg_tmp - end_tmp)
        beg = beg_tmp;
		end = end_tmp;
return s.sub_string(beg+1, end-begin-1);
```

###### Method 2

另外一个$O(n)$的算法，可以参考[这里](https://www.felix021.com/blog/read.php?2040)。

##### Code

```cpp
std::string LongestPalindromeSubstring(const std::string &s) {
  int32_t beg = 0, end = 0;  // record the (begin, end) index
  uint32_t sz = s.size();    // it is an open domain
  for (int32_t axis = 0; axis < sz * 2 - 1; axis++) {
    int32_t beg_tmp, end_tmp;
    if (axis % 2 == 0) {
      beg_tmp = axis / 2 - 1;
      end_tmp = axis / 2 + 1;
    } else  // axis % 2 == 1
    {
      beg_tmp = axis / 2;
      end_tmp = axis / 2 + 1;
    }
    // find the longest palindrome substring(axis)
    while (beg_tmp >= 0 && end_tmp < sz && s[beg_tmp] == s[end_tmp]) {
      beg_tmp--, end_tmp++;
    }
    // update the longest substring if needed
    if (end - beg <= end_tmp - beg_tmp) {
      beg = beg_tmp;
      end = end_tmp;
    }
  }
  return s.substr(beg + 1, end - beg - 1); // begin pos, length
}
```

##### Reference

[最长回文子串](https://algorithm.yuanbin.me/zh-hans/string/longest_palindromic_substring.html)