[TOC]

### Description

Given string `S` and a dictionary of words `words`, find the number of `words[i]` that is a subsequence of `S`.

```
Example :
Input: 
S = "abcde"
words = ["a", "bb", "acd", "ace"]
Output: 3
Explanation: There are three words in words that are a subsequence of S: "a", "acd", "ace".
```

**Note:**

- All words in `words` and `S` will only consists of lowercase letters.
- The length of `S` will be in the range of `[1, 50000]`.
- The length of `words` will be in the range of `[1, 5000]`.
- The length of `words[i]` will be in the range of `[1, 50]`.



### Algorithm and certification

这个题目是 [is subsequence](integer_array/is_subsequence.md) 的扩展，同样可以用 $\textcolor{blue}{two \, pointer}$ 的方法来解决。

设 $s$ 的长度为 $m$，$words$ 数组一共有 $n$ 个元素，元素的平均长度为 $l$；

* 直观解法

  最直观的解法莫过于对于 words 数组里面的每个字符串，均调用一次 is_subsequence 函数，如果是子序列，结果加 1；

  此算法的时间复杂度为：$O(n\times{max(m, l)}) = O(m \times n)$

  空间复杂度为：$O(1)$

  

* 加速解法

  对于较为直观的解法，考虑到字符串 $s$ 当中的每个字符均需要对比 $n$ 次，那么这里是否有简单的方法可以将其比较次数降为一次；

  对于 $words$ 当中的 $n$ 个元素，采用一个数组存储其当前需要进行对比的位置: ptr_table {ptr0, ptr1, ptr2...}

  对于这 $n$ 个需要进行对比的字符，建立一张表，从而可以用字符反查字符串在 $words$ 当中的 index，其结构为：char_to_index_table{character: {index0, index1, index2...}}

  具体的解法如下：

  1. 初始化 ptr_table 为全 0，指当前所有待比较的字符串的下标均为 0； 
  2. 初始化 ptr_s = 0；
  3. 利用 ptr_table 初始化 char_to_index_table；
  4. 获取 s[ptr_s]，然后用 char_to_index_table 来更新 ptr_table ；
  5. 用 ptr_table 更新 char_to_index_table；
  6. ptr_s++，如果发现没有到字符串 s 的末尾，返回第 4 步；
  7. 用 ptr_table 获取所有子序列的个数并返回；

伪代码如下：

```cpp
// Initialize
ptr_s = 0;
ptr_table = {0};
for i = [0, words.size())
    if words[i].size() != 0 
    	char_to_index_table[words[i][0]] = i;

// Iteration
do
    // update the ptr table
    index_array = {};
    for index in char_to_index_table[s[ptr_s]]
        ptr_table[index]++;
        index_array.push_back(index);
    
	// update the char_to_index_table
    char_to_index_table[s[ptr_s]].clear(); // clear the table 
    for index in index_array
    	if ptr_table[index] == words[index].size()
         	continue;
    	c = words[index][ptr_table[index]];
    	char_to_index_table[c].push_back(index);

    // update the ptr_s
    ptr_s++; // move the pointer of the string
while ptr_s < s.size();

// Get the count
count = 0;
for i = [0, ptr_table.size())
    if ptr_table[i] == words[i].size()
         count++;
return count;
```

可以看出，最外层的循环为 $m$，两个内层循环的平均个数应该为 $\frac {n}{27}$，因此最终的时间复杂度为：$O(\frac {m \times n}{27}) = O(m \times n)$，其常数因子要比第一种方式的要小；

ptr_table 占用的空间为 $O(n)$，char_to_index_table 的空间复杂度为 $O(n)$，因此最终的空间复杂度为 $O(n)$。



### Code

```cpp
class Solution {
public:
    int numMatchingSubseq(string S, vector<string>& words) {
        // Initialize
        uint32_t words_sz = words.size();
        uint32_t ptr_s = 0;
        vector<uint32_t> ptr_table(words_sz, 0);
        vector<vector<uint32_t> > char_to_index_table('z' - 'a' + 1, vector<uint32_t>(0));
        for (uint32_t i = 0; i < words_sz; i++)
            if (words[i].size() != 0)
                char_to_index_table[words[i][0] - 'a'].push_back(i);
        
        // Iteration
        do
        {
            // update the ptr table
            vector<uint32_t> index_array;
            for (uint32_t index : char_to_index_table[S[ptr_s] - 'a']){
                ptr_table[index]++;
                index_array.push_back(index);
            }

            // update the char_to_index_table
            char_to_index_table[S[ptr_s] - 'a'].clear(); // clear the table 
            for (uint32_t index : index_array){
                if (ptr_table[index] == words[index].size()) continue;
                char c = words[index][ptr_table[index]];
                char_to_index_table[c - 'a'].push_back(index);
            }
            
            // update the ptr_s
            ptr_s++; // move the pointer of the string
        }while (ptr_s < S.size());

        // Get the count
        int32_t count = 0;
        for (uint32_t i = 0; i < ptr_table.size(); i++)
            if (ptr_table[i] == words[i].size())
                 count++;
        return count;
    }
};
```



### Reference

[Leetcode 392](https://leetcode.com/problems/is-subsequence/description/)
