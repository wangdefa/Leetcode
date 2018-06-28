[TOC]

#### Wildcard matching

------

##### Problem description

给定一个字符串$s$，模式串$p$，返回二者是否匹配。其中模式串$p$当中可能含有‘？’, '*'。其中‘？’表示匹配任意一个字符；‘\*’表示匹配０个或者任意多个字符。
eg:

| s       | p        | result |
| ------- | -------- | ------ |
| abcdefg | abcd*g   | true   |
| abcdefg | abcd*??g | true   |

##### Algorithm description and certification

###### DFS

设立两个指针i, j，分别指向$s, p$当前需要比较的字符。

1. 若模式串当前字符为普通字符，如果s[i] = p[j]，则 i++, j++；
2. 若模式串当前字符为‘？’，则匹配一个字符，即 i++, j++；
3. 若当前需要匹配的字符为'*'，在此有多种选择，可以选择匹配０个或者多个字符，可以直接枚举出这些选择（采用DFS）。

```cpp
bool IsMatch(string s, string p, uint32_t i, uint32_t j)
	while (i < s.size() && j < p.size())
        if (s[i] == p[j] || p[j] == '?')
            i++, j++; // present char is matching
		else if (p[j] == '*') // match 0 or any length string
            len = 0;
			while (; len <= s.size() - i; len++)
                if (IsMatch(s, p, i+len, j+1))
                    return true;
			return false; // all the possible match is useless
        else
        	return false; // present char is not matching
	while (j < p.size() && p[j] == '*') j++; // Remove useless *	
	if (s.size() == i && p.size() == j) return true;
	else return false;
```



###### DP

定义数组$dp[s.size()+1][p.size()+1]$，其中$dp[i][j]$表示$s[0:i], p[0:j]$能否匹配，那么可以有如下的递推关系：
$$
\begin {aligned}
&dp[0][0] = true\\
&dp[i+1][j+1]
&=\left\{
\begin{array}{rcl}
dp[i][j] & & {p[j]=s[i]}\\
dp[i][j] & & {p[j]='?'}\\
dp[i][j+1] \text{  } \or \text{  } dp[i+1][j] & &  {p[j]='*'}\\
false & & else
\end{array} \right.\\

\end {aligned}
$$

1. 对于$dp[0][:]$，初始化时的递推关系如下：
   $$
   \begin {aligned}
   
   &dp[0][j+1]
   &=\left\{
   \begin{array}{rcl}
   false\\
   dp[0][j]  & &  {p[j]='*'}\\
   \end{array} \right.\\
   
   \end {aligned}
   $$
   对于$dp[:][0]$，初始化为：$dp[1:][0]=false$. 

2. 对于上述的递推公式中的第三条，可以解释为：如果$p[j]='*'$，那么这个字符有两个选择，匹配或者不匹配当前字符$s[i]$。只要匹配成功就算成功。

eg: s = "xaylm3", p = "x?y*3"，其递推过程如下表([参考](https://www.youtube.com/watch?v=3ZDZ-N0EPV0))。

| xxx  | xxx  | 0     | 1     | 2     | 3     | 4     | 5     |
| ---- | ---- | ----- | ----- | ----- | ----- | ----- | ----- |
|      |      |       | x     | ?     | y     | *     | 3     |
| 0    |      | true  | false | false | false | false | false |
| 1    | x    | false | true  | false | false | false | false |
| 2    | a    | false | false | true  | false | false | false |
| 3    | y    | false | false | false | true  | true  | false |
| 4    | $l$  | false | false | false | false | true  | false |
| 5    | m    | false | false | false | false | true  | false |
| 6    | 3    | false | false | false | false | true  | true  |

此外，我们需要注意的是：在进行递推前，将pattern串当中所有连续的'\*'替换为一个'\*'。算法的时间复杂度为$O(m \times n)$, 空间复杂度为$O(m \times n)$, 但是如果我们每次都仅仅保留两行或者两列，空间复杂度可以降为：$O(min(m, n))$.

```c++
bool IsMatch(string s, string p)
    sz_s = s.size();
	sz_p = p.size();
    
	// Remove all the continuous * in pattern string
	j = 0;
	for (i = 1; i < sz_p; i++)
        if (j == 0 || p[i] != '*' || p[j-1] != '*')
            p[j++] = p[i]; // this i is valid
	p.resize(j);
	sz_p = j;

	// Init the first row and column of the dp
	dp[0][0] = true;
	for (i = 1; i <= sz_p) // first row
        dp[0][i] = (p[i] == '*' ? dp[0][i-1] : false);
	for (i = 1; i <= sz_s)
        dp[i][0] = false;
	
	// Infer
	for (i = 1; i <= sz_s; i++)
        for (j = 1; j <= sz_p; j++)
        	if (s[i-1] == p[j-1] || p[j-1] == '?')
            	dp[i][j] = dp[i-1][j-1]; // present char is matching
			else if (p[j-1] == '*') // match 0 or any length string
                dp[i][j] = (dp[i-1][j] || dp[i][j-1]);
        	else
        		return false; // present char is not matching
	return dp[sz_s][sz_p];
```



###### Else

[这里](http://yucoding.blogspot.com/2013/02/leetcode-question-123-wildcard-matching.html)有一个特别巧妙的解法，空间复杂度为$O(1)$，时间复杂度为$O(n)$。

##### Code

这里仅仅给出了动态规划解法的code。

```cpp
bool IsMatch(std::string s, std::string p) {
  uint32_t sz_s = s.size();
  uint32_t sz_p = p.size();

  // Remove all the continuous * in pattern string
  uint32_t j = 0;
  for (uint32_t i = 0; i < sz_p; i++) {
    if (j == 0 || p[i] != '*' || p[j - 1] != '*') {
      p[j++] = p[i];  // this i is valid
    }
  }
  p.resize(j);
  sz_p = j;

  // Init the first row and column of the dp
  std::vector<bool> tmp(sz_p + 1, false);
  std::vector<std::vector<bool>> dp(sz_s + 1, tmp);
  dp[0][0] = true;                        // init the first
  for (uint32_t i = 1; i <= sz_p; i++) {  // first row
    dp[0][i] = (p[i - 1] == '*' ? dp[0][i - 1] : false);
  }

  // Infer
  for (uint32_t i = 1; i <= sz_s; i++) {
    for (uint32_t j = 1; j <= sz_p; j++) {
      if (s[i - 1] == p[j - 1] || p[j - 1] == '?') {
        dp[i][j] = dp[i - 1][j - 1];  // present char is matching
      } else if (p[j - 1] == '*') {   // match 0 or any length string
        dp[i][j] = (dp[i - 1][j] || dp[i][j - 1]);
      } else {
        dp[i][j] = false;  // present char is not matching
      }
    }
  }
  return dp[sz_s][sz_p];
}
```

##### Test

##### Reference

[Dynamic programming for wildcard](https://www.youtube.com/watch?v=3ZDZ-N0EPV0)

[wildcard matching](https://algorithm.yuanbin.me/zh-hans/string/wildcard_matching.html)