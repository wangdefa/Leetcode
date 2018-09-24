[TOC]

### Description

Given a string **s** and a string **t**, check if **s** is subsequence of **t**.

You may assume that there is only lower case English letters in both **s** and **t**. **t** is potentially a very long (length ~= 500,000) string, and **s** is a short string (<=100).

A subsequence of a string is a new string which is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (ie, `"ace"` is a subsequence of `"abcde"` while `"aec"` is not).

**Example 1:**
**s** = `"abc"`, **t** = `"ahbgdc"`

Return `true`.

**Example 2:**
**s** = `"axc"`, **t** = `"ahbgdc"`

Return `false`.

**Follow up:**
If there are lots of incoming S, say S1, S2, ... , Sk where k >= 1B, and you want to check one by one to see if T has its subsequence. In this scenario, how would you change your code?



### Algorithm and certification

这个题目可以用典型的 $\textcolor{blue}{two \, pointer}$ 的方法来解决。

其中一个指针 *ptr_s* 指向字符串 *s*，另外一个指针 *ptr_t* 指向字符串 *t：

1. 若 *s[ptr_s] = t[ptr_t]*，那么将指针 *ptr_s* , *ptr_t* 往后移；
2. 若 *s[ptr_s] ！= t[ptr_t]*，仅仅移动指针 *ptr_t*；
3. 直到两个指针当中，有一个指针指向了字符串的末尾；
4. 若 *ptr_s = s.size()* , 返回 true，否则返回 false。

伪代码如下：

```cpp
ptr_s = 0;
ptr_t = 0;
while ptr_s < s.size() && ptr_t < t.size()
	if (s[ptr_s] == t[ptr_t]) 
        ptr_s++; // move the pointer of the parttern
	ptr_t++; // move the pointer of the text
return ptr_s == s.size();
```



### Code

```cpp
class Solution {
public:
    bool isSubsequence(string s, string t) {
        uint32_t ptr_s = 0;
        uint32_t ptr_t = 0;
        while ( ptr_s < s.size() && ptr_t < t.size()){
            if (s[ptr_s] == t[ptr_t]) 
                ptr_s++;
            ptr_t++;
        }        
        return ptr_s == s.size();
    }
};
```



### Reference

[Leetcode 392](https://leetcode.com/problems/is-subsequence/description/)

