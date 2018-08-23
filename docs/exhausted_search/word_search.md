[TOC]



# Word search

---

## Problem description

Given a 2D board and a word, find if the word exists in the grid.

The word can be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell **may not be used more than once**.

**Example:**

```
board =
[
  ['A','B','C','E'],
  ['S','F','C','S'],
  ['A','D','E','E']
]

Given word = "ABCCED", return true.
Given word = "SEE", return true.
Given word = "ABCB", return false.
```

You may see this problem in [Leetcode 79](https://leetcode.com/problems/word-search/description/)

## Algorithm description and certification

题意：

1. 给定了一个 2D 的 board, 每个格子上有一个字母；
2. 给定一个字符串，可以从任意位置开始，判断这个字符串是否在表格当中（每个格子只能走一次，下一个格子必须属于上一个格子的四邻域）；

采用类似走迷宫的解法进行穷举。

1. 因为起始点是不确定的，因此把所有的点都当做可能的起始点进行遍历；
2. 由于每个格子只能走一次，采用一个 2D flag 数组进行标记此格子是否已经走过；
3. 在每一个节点，先判断当前是否已经找全字符串，若已经找全，则退出；否则将对应格子的标记位置为 true, 然后朝其 上下左右 四个方向进行递归遍历；

时间复杂度大致为： $O(m \times n \times l)$；$m \times n$ 是 board 的大小，$l$ 是字符串的长度；

### Code

```cpp
class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        vector<vector<bool>> flag(board.size(), 
                                  vector<bool>(board.front().size(), false));
        for (int32_t i = 0; i < board.size(); i++){
            for (int32_t j = 0; j < board[i].size(); j++){
                if (exist(board, flag, i, j, word, 0)) return true;
            }
        }
        return false;
    }
    
    bool exist(vector<vector<char>>& board, vector<vector<bool>>& flag, int x, int y, 
               string word, int beg) {
        if (beg == word.size()) return true;
        if (x < 0 || y < 0 || x >= board.size() || y >= board.front().size()) 
            return false; // excceed the index
        if (flag[x][y] == true || board[x][y] != word[beg]) return false; // this is used
               
        flag[x][y] = true;
        bool res = (exist(board, flag, x-1, y, word, beg+1) ||
                    exist(board, flag, x+1, y, word, beg+1) ||
                    exist(board, flag, x, y-1, word, beg+1) ||
                    exist(board, flag, x, y+1, word, beg+1));
        flag[x][y] = false;
        return res;
    }   
};
```



## Reference



# Word search II

---

## Problem description

Given a 2D board and a list of words from the dictionary, find all words in the board.

Each word must be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.

**Example:**

```
Input: 
words = ["oath","pea","eat","rain"] and board =
[
  ['o','a','a','n'],
  ['e','t','a','e'],
  ['i','h','k','r'],
  ['i','f','l','v']
]

Output: ["eat","oath"]
```

**Note:**
You may assume that all inputs are consist of lowercase letters `a-z`. You may see this problem in [Leetcode 212](https://leetcode.com/problems/word-search-ii/description/)

## Algorithm description and certification

与 Word search 相比，当前问题仅仅加入了更多的字符串需要进行寻找；

### 蛮力搜索

比较简单的思路即为在前一个问题的基础上，对于每一个字符串均进行一次遍历，即可得到能找到的字符串，但是这种做法会超时；时间复杂度为 $O(m\times n \times l \times k)$，k 为字符串的个数。

### Code

```cpp
class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        vector<string> res;
        auto new_end=unique(words.begin(),words.end()); 
        words.erase(new_end,words.end()); // remove the dulplicates
        
        for (auto word : words){
            if (exist(board, word)) res.push_back(word);
        }
        return res;
    }
    
    bool exist(vector<vector<char>>& board, string word) {
        vector<vector<bool>> flag(board.size(), 
                                  vector<bool>(board.front().size(), false));
        for (int32_t i = 0; i < board.size(); i++){
            for (int32_t j = 0; j < board[i].size(); j++){
                if (exist(board, flag, i, j, word, 0)) return true;
            }
        }
        return false;
    }
    
    bool exist(vector<vector<char>>& board, vector<vector<bool>>& flag, 
               int x, int y, string word, int beg) {
        if (beg == word.size()) return true;
        if (x < 0 || y < 0 || x >= board.size() || y >= board.front().size()) 
            return false; // excceed the index
        if (flag[x][y] == true || board[x][y] != word[beg]) return false; // this is used
               
        flag[x][y] = true;
        bool res = (exist(board, flag, x-1, y, word, beg+1) ||
                    exist(board, flag, x+1, y, word, beg+1) ||
                    exist(board, flag, x, y-1, word, beg+1) ||
                    exist(board, flag, x, y+1, word, beg+1));
        flag[x][y] = false;
        return res;
    }       
};
```

### Trie 树

采用前缀树来对所有的字符串进行检索，这样可以直接排除掉一些重复的检索。如：“aaaab” , "aaaac"，这两个字符串，对于其前缀 “aaaa”, 相较于蛮力算法，此处仅仅需要做一次匹配。

略. For more information, you can refer to [here](https://segmentfault.com/a/1190000008877595).



## Reference

