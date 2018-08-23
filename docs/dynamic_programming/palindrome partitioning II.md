[TOC]





# Palindrome Partitioning II

---

## Problem description

 Given a string *s*, partition *s* such that every substring of the partition is a palindrome.

Return the minimum cuts needed for a palindrome partitioning of *s*.

**Example:**

```
Input: "aab"
Output: 1
Explanation: The palindrome partitioning ["aa","b"] could be produced using 1 cut.
```

You can see more in [Leetcode 132](https://leetcode.com/problems/palindrome-partitioning-ii/description/).

## Algorithm description and certification

题意解析：

1. 输入为一个任意的字符串 str，长度为 $n$；
2. 在字符串当中插入 $k$ 个隔板，从而将原字符串分为 $k+1$ 个子串，并且这些子串均是回文子串；
3. 求隔板的最小数目 $k$；

### Dynamic programming

设数组 $status[i]$ 表示将 $str[0:i)$ 切分为回文子串的最小切分数；那么可以有如下的 递推方程(将字符串拆分为 $str[0:j],  str[j+1:i)$ 两个部分)：
$$
\begin{equation}
status[i]=\left\{
\begin{array}{rcl}
min (status[j] + 1) & & {0 \leq j < i-1  \and str[j+1, i) \text{ is palindrome}}\\
0 & & { str[0, i)  \text{ is palindrome}}
\end{array} \right.
\end{equation}
$$

因此，可以定义： $status[0] = 0$；

因此，还必须求出每一段可能的子串是否为 回文子串；可以设定一个二维数组 $is\_palindrome[n][n]$ ，其中$is\_palindrome[i][j]$ 表示 $str[i, j]$ 是否为回文子串；此时，可以先选定对称轴为 某个元素 或者 某两个元素的中间，然后不断往两端进行扩展，算法的时间复杂度为 $O(n^2)$。

对于前面的递推方程，时间复杂度为 $O(n^2)$，此算法的时间复杂度为： $O(n^2)$；空间复杂度为：$O(n^2)$。

伪代码如下：

```cpp
minCut(s):
	// Special case
	if (s.empty()) return 0;
	
	// Initialize
	n = s.size();
	status[n] = {INT_MAX};
	is_palindrome[n][n] = {false};
	
	// Get the is_palindrome array
	for axis = [0, n):
        for axis_bias = [0, 1]: // use this to deal with the axis=0.5 or so
            for (len=0;;len++)
                axis1 = axis-len;
                axis2 = axis+axis_bias+len;
                if axis2 < n && axis1 >= 0 && s[axis2] == s[axis1]:
                    is_palindrome[axis1][axis2] = true;
                else
                    break;
    
    // Get the final result
    for i = [0, n):
        if is_palindrome[0][i]:
            status[i] = 0; 
            continue;
        for j = [0, i): // str[0:j] str[j+1:i)
            if is_palindrome[j+1][i]:
            	status[i] = min(status[i], status[j] + 1);     
    
    // return the result
    return status[n-1];
```

### Code

```cpp
int32_t minCut(string s) {
    // Special case
    if (s.empty()) return 0;

    // Initialize
    int32_t n = s.size();
    vector<int32_t> status(n, INT_MAX); // status[i] = minCut(str[0, i]);
    vector<vector<bool>> is_palindrome(n, vector<bool>(n, false));

    // Get the is_palindrome array
    for (int32_t axis = 0; axis < n; axis++) {
    	// use this to deal with the axis=0.5 or so
        for (int32_t axis_bias = 0; axis_bias <= 1; axis_bias++) { 
            for (int32_t len = 0;; len++) {
                int32_t axis1 = axis - len;
                int32_t axis2 = axis + axis_bias + len;
                if (axis2 < n && axis1 >= 0 && s[axis2] == s[axis1])
                    is_palindrome[axis1][axis2] = true;
                else
                    break;
            }
        }
    }

    // Get the final result
    for (int32_t i = 0; i < n; i++) {
        if (is_palindrome[0][i]) {
            status[i] = 0;
            continue;
        }
        for (int32_t j = 0; j < i; j++) { // str[0:j] str[j+1:i)
            if (is_palindrome[j + 1][i])
                status[i] = min(status[i], status[j] + 1);
        }
    }

    // Return the result
    return status[n - 1];
}
```

### BFS

在此，仅仅给出 广度优先搜索 的思路；

1. 如上述的dynamic programming 一样，首先或者 $is\_palindrome$ 数组；
2. 然后，从首字母开始，一直往下走，求最小的步数(每次的步长只能取 $is\_palindrome$ 为 true 所对应的步长)；

## Reference

# Longest Common Subsequence 

---

## Problem desciption

Given two strings, find the longest common subsequence (*LCS*).

Your code should return the length of *LCS*.

For `"ABCD"` and `"EDCA"`, the *LCS* is `"A"` (or `"D"`, `"C"`), return `1`.

For `"ABCD"` and `"EACB"`, the *LCS* is `"AC"`, return `2`.

You can get more info in [Lintcode 77](https://www.lintcode.com/problem/longest-common-subsequence/description);

## Algorithm description and certification

经典的动态规划题目：

1. 建立 $lcs[m+1][n+1]$ 数组，其中 $lcs[i][j]$ 表示 $A[0:i]) 与字符串 B[0, j)$ 之间的最长公共子序列；
2. 递推方程如下：$lcs[i][j] = max(lcs[i-1][j], lcs[i][j-1], A[i]== B[j] ? lcs[i-1][j-1]+1 : 0)$；

### Code

```cpp
class Solution {
public:
    /**
     * @param A: A string
     * @param B: A string
     * @return: The length of longest common subsequence of A and B
     */
    int longestCommonSubsequence(string &A, string &B) {
        // write your code here
        if (A.empty() || B.empty()) return 0;
        
        // Initialize
        uint32_t m = A.size();
        uint32_t n = B.size();
        vector<vector<uint32_t> > lcs(m+1, vector<uint32_t>(n+1, 0));
        
        // Iter
        for (uint32_t i = 1; i <= m; i++){
            for (uint32_t j = 1; j <= n; j++){
                if (A[i-1] == B[j-1]) lcs[i][j] = max(lcs[i][j], 1 + lcs[i-1][j-1]);
                lcs[i][j] = max(lcs[i][j], lcs[i-1][j]);
                lcs[i][j] = max(lcs[i][j], lcs[i][j-1]);
            }
        }        
        
        // Return 
        return lcs[m][n];
    }
};
```

## Reference

