[TOC]

枚举所有的子集，这种枚举问题一般采用 DFS 或者 BFS 来实现； DFS常见的实现方式为 递归与栈，BFS常见的实现方式为 队列。

# Subset

------

## Problem description

Given a set of **distinct** integers, *nums*, return all possible subsets (the power set).

**Note:** The solution set must not contain duplicate subsets.

**Example:**

```
Input: nums = [1,2,3]
Output:
[
  [3],
  [1],
  [2],
  [1,2,3],
  [1,3],
  [2,3],
  [1,2],
  []
]
```

You may see this problem in [Leetcode 78](https://leetcode.com/problems/subsets/description/).

## Algorithm description and certification

对于这类枚举的问题，很明显可以采用 DFS或者BFS的方式进行求解。根据题意有：

1. 输入为 $nums$，数组的长度为 $n$，输出为 $res[0:n]$，其中 $res[0:n]$ 表示用数组 $nums$当中的第 0～(n-1)个元素形成集合所包含的全部子集所构成的集合；
2. $nums$ 当中不包含任何重复的元素；

### DFS

对于DFS来说，一般情况下可以采用递归或者Stack进行实现，在此我们分别进行讨论。

#### 递归实现

对于长度为 $n$ 的集合 $nums$ 来说，有如下的递推式：
$$
res[i:n] = \{num[i], res[i+1:n]\} \cup \{res[i+1:n]\}
$$
式 1 的含义为：若我们找到了后面 $n-i$ 个数所形成集合的所有子集，那么最终的结果为：选择将第 i 个元素加入到所有的子集当中 或者 不加入到所有的自己当中；即可得到最终的结果。

伪代码如下：

```c++
subsets(nums, begin, end)
    // special case: the present interval is empty
    res = [[]]; // only contains a empty subset
    if begin == end
		return res;
	
	// get the result by recursive
	combs = subsets(nums, begin + 1, end);
	for comb : combs
		res.push_back(comb);
		res.push_back(comb.push_back(nums[begin]));
	
	// return the result
	return res;
```

* Code

```cpp
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        return subsets(nums, 0, nums.size());
    }
    
    vector<vector<int>> subsets(vector<int>& nums, uint32_t begin, uint32_t end){
        // special case: the present interval is empty
        vector<vector<int>> res(1, vector<int>()); // only contains a empty subset
        if (begin == end) return res;

        // get the result by recursive
        res = subsets(nums, begin + 1, end);
        uint32_t sz = res.size();
        int32_t num = nums[begin]; // get the first ele and delete it	
        vector<int> tmp;
        for (uint32_t i = 0; i < sz; i++){
            tmp = res[i];
            tmp.push_back(num);
            res.push_back(tmp);
        }
        
        // return the result
        return res;
    }
};
```

#### 栈

对于用栈来实现 DFS，其只不过是将上述的递归写法转换为栈的写法；对于栈当中的每一个元素，可以将其看作是一个具体的子问题，当我们解决了栈底的问题后，即可以得到结果，其具体的思路为：

在此，将子问题定义为：在已知$nums[i]$, $res[i+1:n]$ 的情况下，求 $res[i:n]$；伪代码如下：

```cpp
subsets(nums)
    // construct the sub problem
    res = [[]]; // only contain a empty subset
	n = nums.size();	 
	Stack s; 
	for num : nums
		s.push(num);
	
    // solve the sub-problem one by one
	while !s.empty()
		sz = res.size();
		num = s.top(); s.pop(); // get the first ele and delete it		
		for i = [0..sz)
            tmp = res[i];
			res.push_back(tmp.push_back(num));
	
	// return the result
	return res;
```

* Code

注意要点：

1. 在初始化 res 时，需要往里面添加一个 空集，因为空集是任何集合的子集；
2. 求解子问题的结果都存放在 res 当中；

```cpp
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        // construct the sub problem
        stack<int> s; 
        uint32_t n = nums.size(); 
        vector<vector<int>> res(1, vector<int>()); // only contains a empty subset
        for ( auto num : nums) s.push(num);

        // solve the sub-problem one by one
        while (!s.empty()){
            uint32_t sz = res.size();
            int32_t num = s.top(); s.pop(); // get the first ele and delete it	
            vector<int> tmp;
            for (uint32_t i = 0; i < sz; i++){
                tmp = res[i];
                tmp.push_back(num);
                res.push_back(tmp);
            }
		}
        
        // return the result
        return res;
    }
};
```

从这里来看，采用 栈 的写法略微显得更加复杂，但是这种写法可以有效的防止堆栈的溢出。

### BFS

对于BFS来说，其实现的大致原理与栈的实现方式类似，只不过将 递推式 写成了如下的形式：
$$
res[0:i+1] = \{num[i], res[0:i]\} \cup \{res[0:i]\}
$$
式 2 的含义为：若我们找到了前 i 个数所形成集合的所有子集 $res[0:i]$，那么最终的结果为：选择将第 i 个元素加入到所有的子集当中 或者 不加入到所有的子集当中，即可得到最终的结果。

但是此处每个子问题只是数组当中的单个元素，因此可以不用定义一个队列进行存储，伪代码如下：

```cpp
subsets(nums)
    // Initialize
    res = [[]]; // only contains a empty subset
	n = nums.size();
	
    // solve the sub-problem one by one
	for i = [0..n)
		sz = res.size();
		num = nums[i]; 	
		for j = [0..sz)
            tmp = res[j];
			res.push_back(tmp.push_back(num));
	
	// return the result
	return res;
```

* Code

注意要点：

1. 在初始化 res 时，需要往里面添加一个 空集，因为空集是任何集合的子集；

```cpp
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        // Initialize
        vector<vector<int>> res(1, vector<int>()); // only contains a empty subset
        uint32_t n = nums.size();

        // solve the sub-problem one by one
        for (uint32_t i = 0; i < n; i++){
            uint32_t sz = res.size();
            int32_t num = nums[i]; 
            vector<int> tmp;
            for (uint32_t j = 0; j < sz; j++){
                tmp = res[j];
                tmp.push_back(num);
                res.push_back(tmp);
            }
        }
        
        // return the result
        return res;
    }
};
```

## Reference





# Subset II

Given a collection of integers that might contain duplicates, **nums**, return all possible subsets (the power set).

**Note:** The solution set must not contain duplicate subsets.

**Example:**

```
Input: [1,2,2]
Output:
[
  [2],
  [1],
  [1,2,2],
  [2,2],
  [1,2],
  []
]
```

You may see this problem in [Leetcode 90](https://leetcode.com/problems/subsets-ii/description/)

## Algorithm description and certification

此题与 Subset 这个题比较像，二者的区别为：此题当中的集合可能含有重复的元素。在此，仅介绍此题的**广度优先搜索**的解法。

根据题意有：

1. 输入为 $nums$，数组的长度为 $n$，输出为 $res[0:n]$，其中 $res[0:n]$ 表示用数组 $nums$当中的第 0～(n-1)个元素形成集合所包含的全部子集所构成的集合；
2. $nums​$ 当中可能重复的元素；

若 $nums$ 是有序的，且 $nums[i]=nums[i+1]...=nums[i+k]$，那么可以有如下的递推式：
$$
res[0:i+k+1] = \{res[0:i]\} \cup \{num[i], res[0:i]\}\cup ... \{num[i]...num[i+k], res[0:i]\}
$$
式 3 的含义为：若有 $nums[i]=nums[i+1]...=nums[i+k]$，那么可以将这 k+1 个元素看成一个整体，其在最终的结果当中出现的次数可以为 0～(k+1) 次；

伪代码如下：

```cpp
subsetsWithDup(nums)
    // Initialize
    res = [[]]; // only contains a empty subset
	n = nums.size();
	sort(nums.begin(), nums.end());
	
    // solve the sub-problem one by one
	for (i = 0; i < n;)
        // the length of the equals
		k = 0; 
		past = nums[i]; 		
		while (i + k < n && past == nums[i+k]) k++;
		i += k;

		// append each possible count to the combinations
		sz = res.size();
        for l = [1:k+1)	
            tmp = vector<int>(l, past)
        	for j = [0..sz)          
                r = res[j];
                r.insert(r.end(), tmp.begin(), tmp.end());
				res.push_back(r);
	
	// return the result
	return res;
```

### Code

主要是需要注意一些边界条件：

1. 第 18 行的 for 循环应该从 1 开始，因为不包含此元素的集合已经给出；
2. 每次循环当中需要记得更新循环的条件，即第 26 行；

```cpp
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        // Initialize
        vector<vector<int>> res(1, vector<int>()); // only contains a empty subset
        uint32_t n = nums.size();
        std::sort(nums.begin(), nums.end());

        // solve the sub-problem one by one
        for (uint32_t i = 0; i < n;){
            // the length of the equals
            uint32_t k = 0; 
            int past = nums[i]; 		
            while (i + k < n && past == nums[i+k]) k++;

            // append each possible count to the combinations
            uint32_t sz = res.size();
            for (uint32_t l = 1; l < k + 1; l++){
                vector<int> tmp = vector<int>(l, past);
                for (uint32_t j = 0; j < sz; j++) {         
                    vector<int> r = res[j];
                    r.insert(r.end(), tmp.begin(), tmp.end());
                    res.push_back(r);
                }
            }
            i += k; // update the index
         }

        // return the result
        return res;
    }
};
```

## Reference

