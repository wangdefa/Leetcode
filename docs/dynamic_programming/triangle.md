[TOC]

# Triangle

---

## Problem description

Given a triangle, find the minimum path sum from top to bottom. Each step you may move to adjacent numbers on the row below.

For example, given the following triangle

```
[
     [2],
    [3,4],
   [6,5,7],
  [4,1,8,3]
]
```

The minimum path sum from top to bottom is `11` (i.e., **2** + **3** + **5** + **1** = 11).

**Note:**

Bonus point if you are able to do this using only *O*(*n*) extra space, where *n* is the total number of rows in the triangle.

You may see this question in [Leetcode 120](https://leetcode.com/problems/triangle/description/).

## Algorithm description and certification

Goal: 找一条从上到下的路径，使得整条路径上的数加起来最小；

定义一个长度为 $n$ 的数组 $status[n]$，用其来记录 走到每一层各个节点 的最短路径；假设已经得到了第 i 层的状态数组$status$，那么第 i + 1 层的各个状态为：
$$
\begin{equation}
status[j]=
\begin{cases}
status[j] + triangle[i][j] & \text{j=0}\\
status[j-1] + triangle[i][j] & \text{j=i}\\
min(status[j], status[j-1]) + triangle[i][j] & \text{else} 
\end{cases}
\end{equation}
$$
在第一层时，初始化 $status[0] = triangle[0][0]$；

### Code

```cpp
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        // special case
        if (triangle.empty()) return 0;
        
        // initialize
        vector<int> status(triangle.size(), INT_MAX);
        status[0] = triangle[0][0]; // init the first row
        for (uint32_t i = 1; i < triangle.size(); i++){
            for (int32_t j = i; j >= 0; j--){ // 采用逆循环，确保status数组不被覆盖
                if (j == 0) status[j] += triangle[i][j];
                else if (j == i) status[j] = status[j-1] + triangle[i][j];
                else status[j] = min(status[j], status[j-1]) + triangle[i][j];
            }
        }               ; 
        return *std::min_element(status.begin(), status.end());
    }
};
```

## Reference

