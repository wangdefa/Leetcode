[TOC]

#### Rotate string

---

##### Problem description

给定字符串$s$, 偏移量$k$，将字符串$s$按照偏移量$k$进行翻转，需要保证空间复杂度为O(1)。
eg:

| 字符串(string) | 偏移量(offset) | 结果(result) |
| -------------- | -------------- | ------------ |
| abcdefg        | 3              | efgabcd      |
| abcdefg        | 0              | abcdefg      |
| abcdefg        | 1              | bcdefga      |
| abcdefg        | 10             | efgabcd      |

##### Algorithm description and certification

这个问题的解答方式比较tricky。举个如下的例子会比较容易说明：
$s="abcdefg", offset = 3$, 先将字符串$s$划分为两个子串$s_1, s_2$，然后分别对$s_1,s_2$进行翻转，最后将二者拼接在一起进行一次翻转即可(在此基础上，可以对翻转进行一系列的扩充)：

| State             | $s$      | $s_1$ | $s_2$ |
| ----------------- | -------- | ----- | ----- |
| 初始状态          | abcd efg | abcd  | efg   |
| $s_1,s_2$进行翻转 | dcba gfe | dcba  | gfe   |
| 对$s$进行翻转     | efg abcd | xxx   | xxx   |

```cpp
sz = s.size();
offset = offset % sz;
// rotate the s1 = s[0 : sz-offset]
// rotate s2 = s[sz-offset : sz]
// rotate s[0 : sz]
```

##### Code

```cpp
void Rotate(std::string &s, int32_t i, int32_t j) {
  // rotate the s[i:j)
  j--;
  for (; i < j; ++i, --j) {
    char tmp = s[i];
    s[i] = s[j];
    s[j] = tmp;
  }
}
void RotateString(std::string &s, uint32_t offset) {
  if (s.empty) {
    return;
  }
  uint32_t sz = s.size();
  offset = offset % sz;
  Rotate(s, 0, sz - offset);
  Rotate(s, sz - offset, sz);
  Rotate(s, 0, sz);
}
```

##### Reference

[Rotate string](https://algorithm.yuanbin.me/zh-hans/string/rotate_string.html)

#### Reverse words in string
---

##### Problem description

给定一段字符串$s$，其中含有多个单词$word$，各个词之间用一个或者多个空格隔开，对这个字符串进行逐单词翻转。
eg:

| input string $s$             | output string     |
| ---------------------------- | ----------------- |
| "   the  sky is      blue  " | "blue is sky the" |
| "the sky is blue"            | "blue is sky the" |

1. 各个单词之间用一个或者多个空格分开，但是最后的结果当中，各个单词之间仅仅用一个空格分开；
2. 字符串$s$的头尾均可能包含空格，但是结果字符串的头尾不能包含空格；
3. 单词之间的顺序需要进行翻转；
4. 空间复杂度需要控制在O(1)；

##### Algorithm description and certification

借用rotate string方法的核心思想，我们先将各个单词进行原地翻转；然后对整个字符串进行翻转； 最后对一些多余的空字符进行剔除即可；如下面这个例子：

| Step                         | String $s$                   |
| ---------------------------- | ---------------------------- |
| 1. inital string s           | "   the  sky is      blue  " |
| 2. rotate each word in place | "   eht  yks si      eulb  " |
| 3. rotate the whole string   | "   blue      is sky  the  " |
| 4. remove the useless space  | "blue is sky the"            |

以下直接给出源代码，不在给出伪代码。

##### Code

```cpp
void RotateStringByWord(std::string &s) {
  // 1. reverse each word
  int32_t beg = -1;
  int32_t end = -1;
  uint32_t sz = s.size();
  char space = ' ';
  for (int32_t i = 0; i < sz; i++) {
    // 1.1 find the beginning of a word
    if (s[i] != space && beg == -1) {
      beg = i;
      continue;
    }
    // 1.2 find the end and reverse
    if ((s[i] == space || i == sz - 1) && beg != -1) {
      end = i;
      Rotate(s, beg, end);
      beg = end = -1;
    }
  }

  // 2. Rotate the whole string
  Rotate(s, 0, sz);

  // 3. Remove useless space
  uint32_t j = 0;
  for (uint32_t i = 0; i < sz;) {
    // 3.1 remove all the heading space
    if (j == 0 && s[i] == space) {
      i++;
      continue;
    }
    // 3.2 add the valid character
    if (s[i] != space) {
      s[j++] = s[i++];
    }
    // 3.3 Add a space if needed.
    else {
      while (i < sz && s[i] == space) i++;
      if (i == sz) break;  // remove all the tail space
      s[j++] = space;
    }
  }

  // 4. Resize the string
  s.resize(j);
}
```

##### Reference
[Reverse string word by word](https://algorithm.yuanbin.me/zh-hans/string/reverse_words_in_a_string.html)