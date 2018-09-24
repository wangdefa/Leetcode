[TOC]

### Description

The [gray code](https://baike.baidu.com/item/%E6%A0%BC%E9%9B%B7%E7%A0%81/6510858?fr=aladdin) is a binary numeral system where two successive values differ in only one bit.

Given a non-negative integer *n* representing the total number of bits in the code, print the sequence of gray code. A gray code sequence must begin with 0.

**Example 1:**

```
Input: 2
Output: [0,1,3,2]
Explanation:
00 - 0
01 - 1
11 - 3
10 - 2

For a given n, a gray code sequence may not be uniquely defined.
For example, [0,2,3,1] is also a valid gray code sequence.

00 - 0
10 - 2
11 - 3
01 - 1
```

**Example 2:**

```
Input: 0
Output: [0]
Explanation: We define the gray code sequence to begin with 0.
             A gray code sequence of n has size = 2n, which for n = 0 the size is 20 = 1.
             Therefore, for n = 0 the gray code sequence is [0].
```



### Algorithm and certification

正整数 *n* 表示格雷码的长度，题意为：输出一种格雷码的序列，如下表所示：

| n    | gray code                                                    |
| ---- | ------------------------------------------------------------ |
| 0    | {0}                                                          |
| 1    | {0} + {1}                                                    |
| 2    | {00, 01} + {11, 10}                                          |
| 3    | {000, 001, 011, 010} + {110, 111, 101, 100}                  |
| 4    | {0000, 0001, 0011, 0010, 0110, 0111, 0101, 0100} + {1100, 1101, 1111, 1110, 1010, 1011, 1001, 1000} |
| n    | ......                                                       |

当 $n=0$ 时，此时作为 special case 进行输出，输出为 {0}；

当 $n=1$ 时，初始的基准为 {0, 1}；

当 $n=2$ 时，

1. 对于 $n=1$ 所得到的结果进行扩充，将高位填 0 得到 $L_1 = \{00, 01\}$，将高位填 1 得到 $L_2  = \{10, 11\}$；
2. 将 $L_2$ 进行反转，得到 $L_2 = \{11, 10\}$
3. 将 $L_2$ 级联到 $L_1$ 后面即可得到结果 $\{00, 01,11, 10\}$；

当  $n=3$ 时，可以采用类似 $n=2$ 时所采用的方法....

采用数学归纳法很容易证明这个方法的正确性，在此不再赘述。

伪代码如下：

```cpp
// Special case
if n = 0
    return {0};

// Iteration
res = {0, 1}; // n = 1
for i = [2, n]
	sz = res.size();
	for j = [sz, 1]
		res[sz + sz - j] = sz | res[j - 1];

// Return the result
return res;
```



### Code

```cpp
class Solution {
public:
    vector<int> grayCode(int n) {
        // Special case
        vector<int> res(1, 0);
        if (n == 0) return res;

        // Iteration
        res.push_back(1); // n = 1, res={0, 1}
        for (uint32_t i = 2; i <= n; i++){
            uint32_t sz = res.size();
            for (uint32_t j = sz; j > 0; j--)
                res.push_back(sz | res[j - 1]);
        }
        
        // Return the result
        return res;
    }
};
```



### Reference

[Leetcode 89](https://leetcode.com/problems/gray-code/description/)

