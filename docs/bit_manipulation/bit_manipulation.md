### Bit Manipulation
[TOC]

这一系列的题，其处理的技巧性较强；但是只要熟悉了套路，基本上也还好。

#### Single Number

------

##### Problem description

Given a **non-empty** array of integers, every element **appears *twice* except for one**. Find that single one.
Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?
You may see this problem in [Leetcode 136](https://leetcode.com/problems/single-number/description/).

**Example 1:**

```
Input: [2,2,1]
Output: 1
```

**Example 2:**

```
Input: [4,1,2,1,2]
Output: 4
```

##### Algorithm description and certification

给定任何一个数 $x$，我们总有： **x  ^ x = 0， x ^ 0 = x**； 鉴于除了一个我们需要找的数$x_i$以外，其他的数全部出现了两次，因此仅需对数组遍历一遍并且依次进行抑或操作，即可得到要找的数：$x_i$；

```cpp
res = 0;
for x_i : nums
	res ^= x_i;
return res;
```

##### Code

```cpp
int singleNumber(vector<int>& nums) {
    int res = 0;
    for (auto x_i : nums)
        res ^= x_i;
    return res;
}
```

##### Reference



#### Single Number II

Given a **non-empty** array of integers, every element appears *three* times except for one, which appears exactly once. Find that single one.
Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?

**Example 1:**

```
Input: [2,2,3,2]
Output: 3
```

**Example 2:**

```
Input: [0,1,0,1,0,1,99]
Output: 99
```

##### Algorithm description and certification

与题目 single number 类似，若我们能找到一个运算，使得 $c \# c \# c = 0$，即可实现 $O(n)$ 时间复杂度，同时将空间复杂度维持在 $O(1)$；

对于输入数据的每一个 bit，对其分别进行相加，那么每一个 bit 的和是一个 $3n + 1$的形式，在此，我们仅仅需要对其取模，即可得到我们要找的那个数的 当前这个 bit 的值。

```cpp
// Get the sum of each bit
len = 32; // 在此以32bit的数据为例
for x_i : nums
	for b in [0, len)
        sum[b] += ((x_i >> b) & 0x1)

// Get result
for b in [0, len)
    res |= ((sum[b] % 3) << b); 
return res;
```

##### Code

```cpp
int singleNumber(std::vector<int> &nums) {
    int len = 32; // 在此以32bit的数据为例
    uint32_t sum[32] = {0};
    for (int x_i : nums)
        for (int b = 0; b < len; b++)
            sum[b] += ((x_i >> b) & 0x1);
    // Get result
    int res = 0;
    for (int b = 0; b < len; b++)
        res |= ((sum[b] % 3) << b);
    return res;
}
```

##### Reference



#### Single Number III

Given an array of numbers `nums`, in which exactly **two elements** appear only once and all the other elements appear exactly twice. Find the two elements that appear only once. You may find this problem in [Leetcode 260](https://leetcode.com/problems/single-number-iii/description/)

**Example:**

```
Input:  [1,2,1,3,2,5]
Output: [3,5]
```

**Note**:

1. The order of the result is not important. So in the above example, `[5, 3]` is also correct.
2. Your algorithm should run in **linear runtime** complexity. Could you implement it using only **constant space **complexity?

##### Algorithm description and certification

在这个题当中，因为仅仅有两个数据仅仅出现了一次，其他的都出现了两次；设仅仅出现一次的数分别为： x1, x2，与 Single Number 这个题类似，全部遍历一遍进行抑或即可得到 x1 ^ x2；

紧接着，因为 x1 $\neq$ x2，那么x1 ^ x2 $\neq$ 0；此时我们若取出 x1 ^ x2 的一个为 1 的 bit，并且根据这个 bit 将原来的数组分为两组；那么我们就可以将原题转换为两个 Single Number 这样的题（因为这样对原数组进行划分，x1, x2 必然会分到两个不同的数组，而且在两个不同的数组当中，其他的数出现的次数仍然保持为 2 次）；

```cpp
// Get x1 ^ x2
xor_res = 0;
for x_i : nums
	xor_res ^= x_i;

// Get each number
num1 = num2 = 0;
lowest_valid_bit = xor_res ^ (xor_res & (xor_res - 1)); // Get the lowest valid bit
for x_i : nums
	if x_i & lowest_valid_bit == 0
        num1 ^= x_i;
	else 
        num2 ^= x_i;

return {num1, num2};
```

##### Code

```cpp
std::vector<int> SingleNumberIII(std::vector<int> &nums) {
    // Get x1 ^ x2
    int xor_res = 0;
    for (auto x_i : nums)
        xor_res ^= x_i;

    // Get each number
    int num1 = 0, num2 = 0;
    int lowest_valid_bit = xor_res ^ (xor_res & (xor_res - 1)); // Get the lowest valid bit
    for (auto x_i : nums) {
        if ((x_i & lowest_valid_bit) == 0)
            num1 ^= x_i;
        else
            num2 ^= x_i;
    }

    return std::vector<int>{num1, num2};
}
```

##### Reference



#### O(1) check power of 2

Using O(*1*) time to check whether an integer *n* is a power of 2, O(*1*) 时间复杂度。You may see this problem [here](https://www.lintcode.com/problem/o1-check-power-of-2/description).

##### Algorithm description and certification

检查一个数是否是 2 的整数次幂，这个题的解法较多；

第一种是取出去掉这个数的最低为1的有效位，然后与原来的输入进行与运算，如果不为0，则不是；

第二种是将这个数转换为 double (数据可以完整的保留下来，然后查看其mantissa是否为0，指数是否满足指定要求)；

##### Code

```cpp
if (x <= 0) return false; // 当 x <= 0时，此时肯定不满足
return (x & (x - 1)) == 0; // 移除最低有效位后的结果
```

##### Reference



####  Unique Binary Search Trees

Given *n*, how many structurally unique **BST's** (binary search trees) that store values 1 ... *n*? You may see this problem in [Leetcode 96](https://leetcode.com/problems/unique-binary-search-trees/description/).

**Example:**

```
Input: 3
Output: 5
Explanation:
Given n = 3, there are a total of 5 unique BST's:

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3
```

##### Algorithm description and certification

在 {1， 2， ... j，... i }个数当中，若我们选择以 j 为根，那么整个平衡二叉树可以分解为三块，左子树，根，右子树分别包含的元素为：$[1, j), [j, j], (j, i]$，若我们用 $counter[x]$ 表示大小为 x 的平衡二叉树的个数，那么以 j 为根的平衡二叉树的个数为： $counter[j-1] * count[i-j]$ ；因此我们可以有如下的递推公式：

$counter[i] = \sum_{j=1}^{i} counter[j - 1] * counter[i - j]$

当 $j = i 或者 j = 1$ 时，会遇到 counter[0] 的情况，我们不妨将 counter[0] 设为 1；

```cpp
if (n <= 0) return -1;
	
counter[0] = 1;
for i in [1, n]:
	for (j = 1; j <= i; j++)
        counter[i] += counter[j-1] * counter[i-j];
return counter[n];
```

很明显，算法的时间复杂度为 $O(n)$；

##### Code

```cpp
int NumTrees(int n) {
    // special case
    if (n <= 0) return -1;

    // dp
    std::vector<int> counter(n + 1, 0);
    counter[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            counter[i] += counter[j - 1] * counter[i - j];
        }
        // std::cout << counter[i] << std::endl;
    }
    return counter[n];
}
```

##### Reference

#### Majority Number III

Given an array of integers and a number k, the majority number is the number that occurs **more than 1/k** of the size of the array, find it. You may see this problem in [lintcode-48](https://www.lintcode.com/problem/majority-number-iii/description).

eg: Given `[3,1,2,3,2,3,3,4,4,4]` and `k=3`, return `3`.

Limitations: $O(n)$ time and $O(k)$ extra space.

##### Algorithm description and certification

对于输入数组 $A$ 而言，设其数组的大小为 $len$，那么我们要找的这些数在数组 $A$ 当中出现的次数大于：$\frac {len} {k}$ ，设这些数组成的集合为：$Majority(A)$。那么若我们能从数组 $A$ 当中取出 $k$ 个**不同数**的话，若把这 $k$ 个数直接删除，得到删除后的数组为 $A_1$，那么我们要找的答案 $Majority(A) \subset Majority(A_1)$。

对于上述推断，可以有如下的证明：

1. 若 $a\in Majority(A)$，设其在数组 $A$ 当中出现的次数为 $Count(a\_in\_A)$ ；
2. 根据定义，总有： $Count(a\_in\_A) > \frac{len}{k}$；
3. 因为 $B$ 是从 $A$ 当中剔除 $k$ 个不同的数之后的数组，那么在数组 $B$ 当中，那么总有如下不等式： 
   $Count(a\_in\_B) \geq Count(a\_in\_A) - 1 > \frac{len}{k} - 1$
4. 此时数组 $B$ 共含有 $B_{len} = \frac{len}{k} - k$ 个元素，并且我们有：
   $\frac {Count(a\_in\_B)} {B_{len}} > ({\frac{len}{k} - 1}) \div (len - k) = \frac {1} {k}$
5. 也就是说： $Majority(A) \subset Majority(A_1)$；

因此，可以每次选择 $k$ 个不同的数，然后将其直接消去，并且在剩下的数组里面找答案的候选。找到所有的候选元素后，还需要对原数组进行一次遍历，以确认这些候选元素的确时符合出现的次数大于 len/k 的 (因为这些元素可能不满足需求)。

```cpp
// the code is more clear here
```

##### Code

Talk is easy, show me the code.

```cpp
std::vector<int> MajorityElement(std::vector<int> &nums, int k) {
    // find all the number which have at least 1/k,
    std::vector<int> res;
    if (nums.empty()) return res;

    // Get the candidate
    std::unordered_map<int, int> data_cnt;
    for (int d : nums) {
        // Already have this one, we should add the cnt here
        if (data_cnt.find(d) != data_cnt.end()) {
            data_cnt[d]++;
            continue;
        }

        // Not enough k different data, insert this one into table
        if (data_cnt.size() < k - 1) {
            data_cnt[d] = 1; // init
            continue;
        }

        // Erase k different data
        for (auto p = data_cnt.begin(); p != data_cnt.end();) {
            if (p->second == 1)
                data_cnt.erase(p++); // be careful when erase the table
            else {
                p->second--;
                p++;
            }
        }
    }

    // Verify the candidate
    for (auto &p : data_cnt)
        p.second = 0; // reset the counter
    for (int d : nums)
        if (data_cnt.find(d) != data_cnt.end())
            data_cnt[d]++; // Get the real counter
    for (auto p : data_cnt)
        if (p.second > nums.size() / k)
            res.push_back(p.first); // get the result
    return res;
}
```

##### Reference

[Majority number III](https://algorithm.yuanbin.me/zh-hans/math_and_bit_manipulation/majority_number_iii.html)

