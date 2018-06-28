### Anagrams

[TOC]

#### Two string is anagrams or not

------

##### Problem description

给定两个字符串，返回二者是否是一组**变位词**(anagrams: 两个字符串，其中一个可以通过打乱另外一个字符串的字符顺序而得到)。
eg:
| s1    | s2    | result |
| ----- | ----- | ------ |
| 12345 | 32145 | true   |
| 12345 | 12346 | false  |

##### Algorithm description and certification

* 思路

  采用hash map对字符的词频进行计数，若两个字符串的字符词频一致，则返回true。因为只需要扫描一遍两个字符串，因此**时间复杂度**为$O(n)$；因为字符的个数为256(考虑ascii码)，所以**空间复杂度**为$O(1)$。

* 伪代码

  ```cpp
  bool IsAnagrams (string s1, string s2)
      // Special case
      if (s1.size() != s2.size())
          return false;
  
  	// Using hash map to count the character
  	kCharSize = 256;
  	char_count[kCharSize] = {0};
  	for (i = 0; i < s1.size(); i++)
          char_count[s1[i]]++;
  		char_count[s2[i]]--;
  	// Judge the two string have the same character or not
  	for (i = 0; i < kCharSize; i++)
          if (char_count[i] != 0)
              return false;
  	return true;
  ```

##### Code

```cpp
bool IsAnagrams(std::string s1, std::string s2) {
  // Special case
  if (s1.size() != s2.size()) {
    return false;
  }

  // Using hash map to count the character
  const uint32_t kCharSize = 256;
  int32_t char_count[kCharSize] = {0};
  for (uint32_t i = 0; i < s1.size(); i++) {
    char_count[s1[i]]++;
    char_count[s2[i]]--;
  }
  // Judge the two string have the same character or not
  for (uint32_t i = 0; i < kCharSize; i++) {
    if (char_count[i] != 0) {
      return false;
    }
  }
  return true;
}
```

##### Reference

[Two strings are anagrams](https://algorithm.yuanbin.me/zh-hans/string/two_strings_are_anagrams.html)

#### Compare two strings

---

##### Problem description

给定两个字符串s1, s2，判断s2中的**所有字符**(重复的字符需要重复考虑)是否都在s1当中出现(假设所有的字符均是ascii码字符)。
eg:
| s1   | s2    | result |
| ---- | ----- | ------ |
| 1234 | 3214  | true   |
| 1234 | 12344 | false  |
| 1234 | 123   | true   |

##### Algorithm description and certification

* 思路

  采用hash map对字符的词频进行计数(思路与判断两个字符串是否是Anagrams一样)，计数方式为：

  1. 若字符来自于s1，则字符对应的计数器加１；

  2. 若字符来自于s2，则字符对应的计数器减１；

  3. 遍历整个hash map，若存在字符的计数小于０，则返回false；否则返回true。

     只需要扫描一遍两个字符串，因此**时间复杂度**为$O(n)$；
     字符的个数为256(ascii码)，因此**空间复杂度**为$O(1)$。

* 伪代码

  ```cpp
  bool CompareStr (string s1, string s2)
  	// Using hash map to count the character
  	kCharSize = 256;
  	char_count[kCharSize] = {0};
  	for (i = 0; i < s1.size(); i++)
          char_count[s1[i]]++;
  	for (i = 0; i < s2.size(); i++)
  		char_count[s2[i]]--;
  	// Judge the two string have the same character or not
  	for (i = 0; i < kCharSize; i++)
          if (char_count[i] < 0)
              return false;
  	return true;
  ```

##### Code

```c++
bool CompareStr(std::string s1, std::string s2) {
  // Using hash map to count the character
  const uint32_t kCharSize = 256;
  int32_t char_count[kCharSize] = {0};
  for (uint32_t i = 0; i < s1.size(); i++) {
    char_count[s1[i]]++;
  }
  for (uint32_t i = 0; i < s2.size(); i++) {
    char_count[s2[i]]--;
  }
  // Judge the two string have the same character or not
  for (uint32_t i = 0; i < kCharSize; i++) {
    if (char_count[i] < 0) {
      return false;
    }
  }
  return true;
}
```

##### Reference

[Two strings are anagrams](https://algorithm.yuanbin.me/zh-hans/string/two_strings_are_anagrams.html)

#### Group anagrams

---

##### Problem description

给定一组字符串，将属于变位词的字符串化为一组，这样形成多个组。
eg:
input: {"eat", "tea", "tan", "ate", "nat", "bat"}
output: {{"eat", "tea", "ate"}, {"tan", "nat"}, {"bat"}} 
可以看到，上面的字符串被划分成了三组，每一组内部的字符串均为变位词。

##### Algorithm description and certification

* 思路

  采用两层for循环，第一层针对所有的字符串，第二层针对所有的变位词组；；

  1. 从所有的字符串当中取出一个字符串；

  2. 从所有的变位词组当中取出一个变位词组；

  3. 对于当前的字符串，
     若找到其所属的变位词组，将字符串加入到此变位词组；
     若未找到其所属的变位词组，则新建立一个变位词组(仅仅包含当前一个字符串)。

     两层循环的时间复杂度为$O(n^2)$，判断两个词是否是变位词的时间复杂度为$O(L)$，因此**时间复杂度**为$O(n^2L)$.
     若不考虑最终结果所占用空间，空间复杂度仅仅受判断两个词是否是变位词的影响，因此**空间复杂度**为$O(1)$。

* 伪代码

  整个code比较简单，建议直接看src code。

##### Code

```c++
std::vector<std::vector<std::string>> GroupAnagrams(std::vector<std::string> src) {
  std::vector<std::vector<std::string>> result;
  // special case
  if (src.size() < 1) {
    return result;
  }

  std::vector<std::string> vec(1, src.front());
  result.push_back(vec);
  for (uint32_t i = 1; i < src.size(); i++) {
    bool i_merged = false;
    // Loop all the group until i have found the group
    for (uint32_t j = 0; j < result.size(); j++) {
      if (IsAnagrams(src.at(i), result.at(j).front())) {
        result[j].push_back(src.at(i));
        i_merged = true;
        break;
      }
    }
    // if i didn't find group, create his own group
    if (!i_merged) {
      std::vector<std::string> vec(1, src.at(i));
      result.push_back(vec);
    }
  }
  return result;
}
```

##### Reference

[Leetcode 49: Group Anagrams](https://leetcode.com/problems/group-anagrams/description/)
[Group anagrams](https://algorithm.yuanbin.me/zh-hans/string/group_anagrams.html)
此外，我们还可以采用空间换时间的策略，对于每一个字符串，建立一个pair，分别存储其value以及对字符串自身排序后的value(不妨称之为sorted_value)；然后以sorted_value为key，扫描一遍字符串数组（将key相同的字符串进行合并），即可得到结果。时间复杂度为：$O(nL \log{L})$。