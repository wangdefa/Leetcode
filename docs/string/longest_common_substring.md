[TOC]

#### Longest common substring

---

##### Problem description

给定两个字符串$s_1, s_2$，返回二者的最长公共子串的长度。
eg:
input: $s_1$ = "ABCD", $s_2$ = `"CBCED"`
output: 2, 因为"BC"是二者的最长公共子串，其长度为２。

##### Algorithm description and certification

设$s_1$的长度为$m$，$s_2$的长度为$n$，定义两个二维数组，其具体含义如下表：

| 数组名         | 数组行数 | 数组列数 | 解释                                                         |
| -------------- | -------- | -------- | ------------------------------------------------------------ |
| $lcss\_max$    | $m+1$    | $n+1$    | $lcss\_max_{{i+1}, {j+1}}$ : $s_1[0:i]$与$s_2[0:j]$之间的最长公共子串的长度 |
| $lcss\_suffix$ | $m+1$    | $n+1$    | $lcss\_suffix[i+1][j+1]$：　$s_1[0:i]$与$s_2[0:j]$之间的最长公共子后缀 |

为了后续写code方便，我们将数组$lcss\_max, lcss\_suffix$的第０行，第０列置为０；

因此对于最长公共子后缀，我们可以有如下的递推公式：
$$
\begin {equation}
\begin {aligned}

lcss\_suffix[i+1][j+1]&=\left\{
\begin{array}{rcl}
 lcss\_suffix[i][j] +1 & & {s_1[i]=s_2[j]}\\
0 & & {else}\\
\end{array} \right.\\

 \end {aligned}
 \end {equation}
$$
对于最长公共子串的递推公式如下：
$$
lcss\_max[i+1][j+1] = \max(lcss[i+1][j], lcss[i][j+1], lcss\_suffix[i+1][j+1])
$$
因此我们有如下伪代码：

```c++
m = s1.size();
n = s2.size();
lcss_max[m+1][n+1]; // row 0, column 0 should be initialized to 0
lcss_suffix[m+1][n+1]; // row 0, column 0 should be initialized to 0
for (i = 0; i < m; i++)
    for (j = 0; j < n; j++)
        // Get the longest common suffix
        if (s1[i] == s2[j])
            lcss_suffix[i+1][j+1] = lcss_suffix[i][j] + 1;
		else
            lcss_suffix[i+1][j+1] = 0;
		// Get max from the 3 choices
		lcss_max[i+1][j+1] = max(lcss_max[i][j+1], lcss_max[i+1][j]);
		lcss_max[i+1][j+1] = max(lcss_max[i+1][j+1], lcss_suffix[i+1][j+1]);

return lcss_max[m][n];
```

##### Code

Below is the code of the final version. But if you want to find what does the longest common substring is, you can save the first index of the substring in each iteration.

```cpp
uint32_t LongestCommonSubstring(std::string s1, std::string s2) {
  uint32_t m = s1.size();
  uint32_t n = s2.size();
  std::vector<std::vector<uint32_t> > lcss_max(
      m + 1, std::vector<uint32_t>(n + 1, 0));  // row 0, column 0 ->o 0
  std::vector<std::vector<uint32_t> > lcss_suffix(
      m + 1, std::vector<uint32_t>(n + 1, 0));  // row 0, column 0 ->o 0
  for (uint32_t i = 0; i < m; i++) {
    for (uint32_t j = 0; j < n; j++) {
      // Get the longest common suffix
      if (s1[i] == s2[j]) {
        lcss_suffix[i + 1][j + 1] = lcss_suffix[i][j] + 1;
      } else {
        lcss_suffix[i + 1][j + 1] = 0;
      }
      // Get max from the 3 choices
      lcss_max[i + 1][j + 1] = std::max(lcss_max[i][j + 1], lcss_max[i + 1][j]);
      lcss_max[i + 1][j + 1] =
          std::max(lcss_max[i + 1][j + 1], lcss_suffix[i + 1][j + 1]);
    }
  }
  return lcss_max[m][n];
}
```

##### Reference

[这里](https://algorithm.yuanbin.me/zh-hans/string/longest_common_substring.html)有一个更好的解法，其思想也是动态规划，但是其状态转移方程当中，$lcs[i][j]$是指以$s1[i], s2[2]$为最后一个元素的最长子串。