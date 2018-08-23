[TOC]

# Permutations

---

## Problem description

Given a collection of **distinct** integers, return all possible permutations.

**Example:**

```
Input: [1,2,3]
Output:
[
  [1,2,3],
  [1,3,2],
  [2,1,3],
  [2,3,1],
  [3,1,2],
  [3,2,1]
]
```

You may see this problem in [Leetcode 46](https://leetcode.com/problems/permutations/description/)

## Algorithm description and certification

因为集合当中的所有元素均不一样，可以理解为输出为集合当中元素的 **全排列**。在此，考虑分别采用 DFS, BFS 的方式来实现。

### DFS

此处采用 DFS 算法时，考虑直接用递归的方式来实现。每次递归时，输入为一个数组 $nums$，大小为 $n$，加上需要进行全排列的 $range [0, end)$，从 end 开始往后的元素已经排列好。那么可以有如下的递推式：
$$
S(nums, end) = S(nums, end, 0) \cup  S(nums, end, 1)...\cup S(nums, end, end-1)
$$
其中 $S(nums, end)$ 表示子问题的解，$S(nums, end, k)$ 表示将 $nums[end-1]$ 与 $nums[k]$ 交换后所形成的子问题的解。当 $end=0$ 时，递归终止。伪代码如下：

```cpp
permute(nums, end)
    // The special case: we get one solution
    if end = 0 || end = 1 // only one element or none
        res.push_back(nums)
        return;
	
	for i = [0...end)
        // swap the element and solve the sub problem
        tmp = nums;
        swap(tmp[i], tmp[end-1]);
        permute(tmp, end-1);        
```

### Code

注意点：

1. 代码的第 9 行当中的递归终止条件，end = 0 这个条件可以 handle 输入为空的情况；此时最终的结果也仅仅是一个空集；
2. 代码第 14~22 行，始终将确定好位置的元素移到末尾，然后进行递归；
3. 从空间的复杂度来说，栈的深度为 $O(n)$，每一层的空间复杂度为 $O(n)$，若刨去最终节点所占用的空间，空间复杂度是： $O(n^2)$。

```cpp
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        permute(nums, nums.size());
        return res;
    }
    void permute(vector<int>& nums, uint32_t end) {
        // The special case: we get one solution
        if (end == 0 || end == 1){ // only one element or none
            res.push_back(nums);
            return;
        }

        for (uint32_t i = 0; i < end; i++){
            // swap the element and solve the sub problem
            vector<int> tmp = nums;
            int ex = tmp[i];
            tmp[i] = tmp[end-1];
            tmp[end-1] = ex;
            
            // solve the sub-problem
            permute(tmp, end-1);    
        }
    }
private:
    vector<vector<int>> res; 
};
```

### BFS

若采用 BFS 的解法，同样可以采用上述的递推式，只不过在队列当中，我们不会存储此时需要做全排列的数组大小，因为做大小为 $n$ 的全排列的数组数量是 1 个；需要做大小为 $n-1$ 的全排列的数组数量是 n 个；需要做大小为 $n-$ 2的全排列的数组数量是 $n \times (n-1)$ 个...只需用一个状态将其记住即可；伪代码如下：

```cpp
permute(nums)
    // Init
    res = [[]]; // an empty 2d array
	q.push(nums); // need to do permute
	sz = 1; // the size of the queue which have range [0, n) to permute
	end = nums.size(); // permute range [0, end)

	// BFS search
	while (!q.empty())
        for i = [0...sz)
            // Get the node
            node = q.front();
            q.pop();
                 
            // Get the result if we have at most 1 element to permute
            if end = 0 || end = 1
                 res.push(node);
                 continue;
            
            // Need to do permute since we have at least 2 element to permute
            for i = (end...0]
                swap(node[i], node[end-1]);
                q.push(node); 
         
         // update the sz and end
         sz *= end;
         end--;
```

### Code

注意点：

1. 代码的第 33~34 行不定不能忘记，因为我们是用这个来更新状态；写代码的时候可以考虑先写整体结构，再写里面的实现细节，从而不会陷入到细节当中而忘记了大体。

```cpp
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        // Init
        vector<vector<int>> res; // an empty 2d array
        queue<vector<int>> q;
        q.push(nums); // need to do permute
        int sz = 1; // the size of the queue which have range [0, n) to permute
        int end = nums.size(); // permute range [0, end)

        // BFS search
        while (!q.empty()){
            // this means we have sz node to do permute in the queue
            for (int loop = 0; loop < sz; loop++){
                // Get the node
                vector<int> node = q.front();
                q.pop();

                // Get the result if we have at most 1 element to permute
                if (end == 0 || end == 1){
                     res.push_back(node);
                     continue;
                }

                // Need to do permute since we have at least 2 element to permute
                for (int i = end - 1; i >= 0; i--){
                    int ex = node[i];
                    node[i] = node[end-1];
                    node[end-1] = ex;
                    q.push(node); 
                }
            }            
            sz *= end;
            end--;
         }
        
        return res;
    }
};
```

## Reference



# Permutations II

------

## Problem description

Given a collection of numbers that might **contain duplicates**, return all possible **unique permutations**.

**Example:**

```
Input: [1,1,2]
Output:
[
  [1,1,2],
  [1,2,1],
  [2,1,1]
]
```

You may see this problem in [Leetcode](https://leetcode.com/problems/permutations-ii/description/)

## Algorithm description and certification

与前一题相比较，这个题目当中的输入可能含有重复的元素，因此一个很直接的想法就是在上一题的基础上，加去去除重复元素的逻辑。在此，我们先对输入数据进行排序，然后直接借鉴 BFS 的逻辑，但是其递推式需要加上一个约束：若当前需要对 $nums[0, end)$ 进行全排列，这当中含有 $k$ 个互不相同的元素，那么其递推式如下所示：
$$
S(nums, end) =  S(nums, end, i)...\cup... S(nums, end,j)
$$
其中，$nums[i], nums[j]$ 是不相等的，一共有 $k$ 个。 此处为了简化逻辑，将数组当前需要进行 permute 的长度也存在队列当中，以下直接给出源代码：

### Code

注意：

1. 在去重的时候，为了简单起见，直接使用了一个 unordered_set；
2. 队列当中的每个元素均可以看作是一个子问题，合并所有子问题的解，即为最终的解；

```cpp
class Node {
  public:
    vector<int> nums;
    int len;
    Node() : len(0) {}
    Node(vector<int> nums_in, int len_in) : nums(nums_in), len(len_in) {}
};
class Solution {
  public:
    vector<vector<int>> permuteUnique(vector<int> &nums) {
        // Init
        vector<vector<int>> res; // an empty 2d array
        queue<Node> q;
        q.push(Node(nums, nums.size())); // need to do permute

        // BFS search
        while (!q.empty()) {
            // Get the node
            Node node = q.front();
            q.pop();

            // Get the result if we have at most 1 element to permute
            if (node.len == 0 || node.len == 1) {
                res.push_back(node.nums);
                continue;
            }

            // Need to do permute since we have at least 2 element to permute
            std::unordered_set<int> s;
            int len = node.len;
            for (int i = len - 1; i >= 0; i--) {
                if (s.find(node.nums[i]) != s.end()) continue;
                s.insert(node.nums[i]);
                int ex = node.nums[i];
                node.nums[i] = node.nums[len - 1];
                node.nums[len - 1] = ex;
                q.push(Node(node.nums, len - 1));
            }
        }

        return res;
    }
};
```

## Reference



# Next Permutations

------

## Problem description

Implement **next permutation**, which rearranges numbers into the lexicographically next greater permutation of numbers.

If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).

The replacement must be **in-place** and use only constant extra memory.

Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.

`1,2,3` → `1,3,2`
`3,2,1` → `1,2,3`
`1,1,5` → `1,5,1`

You may see this problem in [leetcode](https://leetcode.com/problems/next-permutation/description/)

## Algorithm description and certification

若我们详细观察下一个与上一个之间的联系(假如只有三个元素)，如下表所示：

| first element | second element | third element |
| ------------- | -------------- | ------------- |
| 1             | **2**          | **3**         |
| **1**         | 3              | **2**         |
| 2             | **1**          | **3**         |
| **2**         | **3**          | 1             |
| 3             | **1**          | **2**         |
| 3             | 2              | 1             |

即可得到如下的规律：

1. 从后往前看，若发现有后面元素 j 大于前面元素 i 的情况，将 i, j 进行交换，然后对 j 之后的元素进行升序排列即可； 
2. 若找不到后面的元素大于前面的元素，将整个数组进行升序排列即可 (对应最小元素)；

伪代码如下：

```cpp
nextPermutation(nums)
    // find the pos of the not ordered element    
    sz = nums.size();
	if (sz == 0 || sz == 1) return nums;
	
	// find i, j
    i = sz - 2; // when there is no reverse pair, i = -1
    for (; i >= 0 && nums[i] >= nums[i+1]; i--); 
    if (i == -1) 
        sort(nums.begin(), nums.end());
        return; // special case, get the minimum
    j = sz - 1; // since nums[i+1, sz) is in reverse order, find the first
    for (; j > i && nums[j] <= nums[i]; j--); //  j and nums[j] > nums[i]
	
	// swap and sort if needed
	swap(nums[i], nums[min]);
	sort(nums.begin() + i + 1, nums.end());
	return nums;        
```

### Code

注意：

1. 代码第 11 行，当整个数组逆序的时候，i = -1，此时不需要找 j，进行元素位置的调整；

```cpp
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        // find the pos of the not ordered element    
        int sz = nums.size();
        if (sz == 0 || sz == 1) return;
        
        // find i, j
        int i = sz - 2; // when there is no reverse pair, i = -1
        for (; i >= 0 && nums[i] >= nums[i+1]; i--);         
        if (i != -1){ // since nums[i+1, sz) is in reverse order, find the first
            int j = sz - 1; 
        	for (; j > i && nums[j] <= nums[i]; j--); //  j and nums[j] > nums[i]
            swap(nums, i, j);
        }
        sort(nums.begin() + i + 1, nums.end());
    }
    void swap(vector<int>& nums, int i, int j){
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
    }
};
```

## Reference

# Previous Permutations

---

## Problem description

Given a list of integers, which denote a permutation.

Find the previous permutation in ascending order.

The list may contains **duplicate integers**.

**Example**

For `[1,3,2,3]`, the previous permutation is `[1,2,3,3]`

For `[1,2,3,4]`, the previous permutation is `[4,3,2,1]`

You may see this problem in [Lintcode 51](https://www.lintcode.com/problem/previous-permutation/description)

## Algorithm description and certification

若我们详细观察下一个与上一个之间的联系(假如只有三个元素)，如下表所示：

| first element | second element | third element |
| ------------- | -------------- | ------------- |
| 3             | **2**          | **1**         |
| **3**             | 1              | **2**             |
| 2         | **3**          | **1**             |
| **2**             | **1**          | 3         |
| **1**         | **3**              | 2         |
| 1             | 2          | 3         |

即可得到如下的规律，与上一题几乎一样，仅仅需要改变排序、比较大小：

1. 从后往前看，若发现有后面元素 j **小于**前面元素 i 的情况，将 i, j 进行交换，然后对 j 之后的元素进行降序排列即可； 
2. 若找不到后面的元素大于前面的元素，将整个数组进行**降序**排列即可 (对应最小元素)；

### Code

```cpp
class Solution {
public:
    /*
     * @param nums: A list of integers
     * @return: A list of integers that's previous permuation
     */
    vector<int> previousPermuation(vector<int> &nums) {
        // write your code here
        // find the pos of the not ordered element    
        int sz = nums.size();
        if (sz == 0 || sz == 1) return nums;
        
        // find i, j
        int i = sz - 2; // when there is no reverse pair, i = -1
        for (; i >= 0 && nums[i] <= nums[i+1]; i--);         
        if (i != -1){ // since nums[i+1, sz) is in reverse order, find the first
            int j = sz - 1; 
        	for (; j > i && nums[j] >= nums[i]; j--); //  j and nums[j] < nums[i]
            swap(nums, i, j);
        }
        sort(nums.begin() + i + 1, nums.end(), [](int x, int y)->bool{return x > y;});
        return nums;
    }
    void swap(vector<int>& nums, int i, int j){
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
    }
};
```

## Reference



# Permutation Index

---

## Problem description

Given a permutation which contains no repeated number, find its index in all the permutations of these numbers, which are ordered in lexicographical order. The index begins at 1.

**Example**

Given [1,2,4], return 1.

You may see this problem in [Leetcode 197](https://www.lintcode.com/problem/permutation-index/description)

## Algorithm description and certification

题目的含义是： 给定一个数组，找这个数组在字典序当中的下标(也就是说若将所有的排列情况进行字典排序，当前数组应该是位于第几个)。还是以前面的例子看：

| first element | second element | third element |
| ------------- | -------------- | ------------- |
| 1             | **2**          | **3**         |
| **1**         | 3              | **2**         |
| 2             | **1**          | **3**         |
| **2**         | **3**          | 1             |
| 3             | **1**          | **2**         |
| 3             | 2              | 1             |

若输入为: 3，1，2，那么我们应该返回 5；

1. 当前可以将输入看成是： {3，1，2}由于其最高位为 3，后面还有两个元素(1,2)小于 3，那么在字典序当中，当最高位为 1、2时可能含有 2 × 2！ = 4个元素；
2. 固定最高位，输入可以被看成是 {1, 2}，采用同样的方法，比这个元素还小的组合个数为0；
3. 固定最高位3，次高位1，输入可以看做为 {2}，采用同样的方式，比这个元素还小的组合个数为 0；
4. 最后，我们加上元素本身，从而得到其下标，也就是 1 + 4 = 5；

对于这种思路，我们需要计算阶层，因此可以考虑采用迭代的方式，从最后一个元素开始进行计算；

### Code

注意：

1. 当数组为空时，我们应该如何处理？
2. 从最后一个元素开始进行扫描，直接将这个元素进行考虑元素；
3. 对于剩下的元素，不断更新阶层，然后扫描得到小于 nums[i] 的个数，并且与得到的阶层相乘；即为此层所能容纳的元素数量；

```cpp
class Solution {
public:
    /**
     * @param A: An array of integers
     * @return: A long integer
     */
    long long permutationIndex(vector<int> &A) {
        // write your code here
        int sz = A.size();
        long long counter = 0;
        long long base = 1;
        
        // get all the possible A which < A
        for (int64_t i = sz-1; i >= 0; i--){
            if (i == sz-1) {
                counter++;
                continue;
            }
            base *= (sz - i - 1);
            
            // find the count of A[j] < A[i] and j > i
            int count = 0;
            for (int64_t j = i + 1; j < sz; j++){
                if (A[j] < A[i]) count++;
            }
            counter += count * base;
        }
        
        return counter;
    }
};
```

## Reference

