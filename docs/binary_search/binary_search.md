## Find index

[TOC]



### First Position of Target 

给定一个排好序的升序数组$nums$，一个需要找的数据$target$，寻找其在数组当中第一次出现的位置，如果找不到，返回 -1。eg:
$\{1 ,2 ,3 ,4 ,5\}, 3$ ， return 2
$\{1 ,2 ,3 ,4 ,5\}, 0$ ， return -1
对于题目的详细说明，可以参考Lintcode 里面的[find position of target](https://www.lintcode.com/problem/first-position-of-target/description).

#### Algorithm description and certification

假设给定的数组为 $nums$, 长度为 $sz$, 需要找的数为 $target$.

1. 特殊情况： 当数组为空时，直接返回-1；
2. 对于其他情况进行折半查找；

假设需要进行折半查找的范围是$[i, j)$, 中间位置为$mid$。

1. 当$nums[mid] \geq target$, 那么我们需要查找的位置可以缩减到区间 $[i, mid+1)$；
2. 当$nums[mid] < target$, 查找的区间可以缩减到 $[mid+1, j)$。
3. 最终$i+1 = j$时，意味着查找的区间只剩下一个元素，此时只需要判断其是否等于target，如果等于则返回i，否则返回 -1。

需要注意的是，由于每次都将区间$[i, j)$划分为两个区间$[i, mid+1), [mid+1, j)$，为了防止死循环，在计算$mid$时，如果区间$[i, j)$只有两个元素，eg: $i=1, j= 3$, 那么我们必须使得$mid+1=2$，从而得到两个一样长度的子区间$[1, 2), [2, 3)$。因此，$mid = i + (j-1-i) \div 2$

```cpp
// special case
if (sz == 0) return -1; 

// binary search
i = 0, j = sz;
while (i + 1 < j)
    mid = i + ((j - i - 1) >> 1);
	if (nums[mid] >= target) j = mid + 1;
	else i = mid + 1；
if (nums[i] == target) return i;
else return -1;
```

#### Code

```cpp
// find position of the target, return the first index of the target in O(lgn)
int32_t FindPosition(std::vector<int32_t> &nums, int32_t target) {
    // 1 2 3 4 5, 3 -> return 2  (find the pos)
    // 1 2 3 4, 4   -> return -1  (not found)
    if (nums.empty()) return -1; // not exist

    // binary search
    int32_t i = 0;
    int32_t j = nums.size(); // find the target in [i, j)
    while (i + 1 < j) {      // exit when we have only 1 element
        uint32_t mid = i + ((j - 1 - i) >> 1);
        if (nums[mid] >= target)
            j = mid + 1;
        else
            i = mid + 1;
    }

    // return the position
    if (nums[i] == target)
        return i;
    else
        return -1;
}
```

#### Reference

[first position of target](https://algorithm.yuanbin.me/zh-hans/binary_search/first_position_of_target.html)



### Search Insert position
给定一个升序数组$nums$， target，寻找将target插入到数组nums当中的位置。如果数据已经在数组$nums$当中，则将数据插入到尽可能靠前的位置。
eg:
$\{1, 2, 3, 4, 5\}, 3$， return 2;
$\{1, 2, 3, 4, 5\}, 6$， return 5;
$\{1, 2, 3, 4, 5\}, 0$， return 0;

#### Algorithm description and certification
假设给定的数组为 $nums$, 长度为 $sz$, 需要找的数为 $target$.

1. 特殊情况： 当数组为空时，直接返回 0；
2. 对于其他情况进行折半查找；

假设需要进行折半查找的范围是$[i, j)$, 中间位置为$mid$。

1. 当$nums[mid] \geq target$, 那么我们需要查找的位置可以缩减到区间 $[i, mid+1)$；
2. 当$nums[mid] < target$, 查找的区间可以缩减到 $[mid+1, j)$。
3. 最终$i+1 = j$时，意味着查找的区间只剩下一个元素，此时只需要判断此元素与target的大小关系，如果$nums[i] \geq target$则返回i，否则返回 $i+1$。

需要注意的是，由于每次都将区间$[i, j)$划分为两个区间$[i, mid+1), [mid+1, j)$，为了防止死循环，在计算$mid$时，如果区间$[i, j)$只有两个元素，eg: $i=1, j= 3$, 那么我们必须使得$mid+1=2$，从而得到两个一样长度的子区间$[1, 2), [2, 3)$。因此，$mid = i + (j-1-i) \div 2$

```cpp
// special case
if (sz == 0) return 0; 

// binary search
i = 0, j = sz;
while (i + 1 < j)
    mid = i + ((j - i - 1) >> 1);
	if (nums[mid] >= target) j = mid + 1;
	else i = mid + 1；
if (nums[i] >= target) return i;
else return i + 1;
```
#### Code

```cpp
// return the insert index of the target in O(lgn)
int32_t FindPosition(std::vector<int32_t> &nums, int32_t target) {
    // 1 2 3 4 5, 3 -> return 2  (find the pos)
    // 1 2 3 4, 4   -> return 3  
    if (nums.empty()) return 0; 

    // binary search
    int32_t i = 0;
    int32_t j = nums.size(); // find the target in [i, j)
    while (i + 1 < j) {      // exit when we have only 1 element
        uint32_t mid = i + ((j - 1 - i) >> 1);
        if (nums[mid] >= target)
            j = mid + 1;
        else
            i = mid + 1;
    }

    // return the position
    if (nums[i] >= target)
        return i;
    else
        return i + 1;
}
```

代码与first position of target 几乎一模一样，仅仅在修改了返回值以及返回条件。

#### Reference



### Search for a range

给定一个数组$nums$，其长度为$sz$，现在给定一个$target$，需要返回这个数在$nums$当中出现开始下标、结束下标。若不存在，则返回$\{-1, -1\}$.

>  eg:
> nums = {1, 2, 3, 3, 4, 5} , target = 3;   return {2, 3}
> nums = {1, 2, 3, 3, 4, 5} , target = 6;   return {-1, -1}

#### Algorithm description and certification

套用前面[找第一次出现的位置](#first-position-of-target)这种逻辑，我们仅仅需要实现**找最后一次出现的位置**即可。
假设需要进行折半查找的范围是$[i, j)$, 中间位置为$mid$。

1. 当$nums[mid] > target$，查找区间可以缩减到： $[i, mid)$；
2. 当$nums[mid] \leq target$，查找区间可以缩减到： $[mid, j)$；
3. 最终$i+1 = j$时，意味着查找的区间只剩下一个元素，此时只需要判断其是否等于target，如果等于则 i 即为最后一次出现的位置，否则返回 -1。

对于中间位置 $mid$ 的计算，考虑极端情况（最终的数组当中仅剩下两个元素）： $i=1, j= 3$, 那么我们必须使得$mid=2$，从而得到两个一样长度的子区间$[1, 2), [2, 3)$。因此，$mid = i + (j-i) \div 2$

```cpp
// we only give the code of finding the last position of target
if (sz == 0) return -1; // special case

// binary search
i = 0, j = sz;
while (i + 1 < j)
    mid = i + ((j - i) >> 1);
	if (nums[mid] > target) j = mid;
	else i = mid；
if (nums[i] == target) return i;
else return -1;
```

#### Code

```cpp
// find last position of the target, return the last index of the target in O(lgn)
int32_t FindLastPosition(std::vector<int32_t> &nums, int32_t target) {
    // 1 2 3 4 5, 3 -> return 2  (find the pos)
    // 1 2 3 4, 4   -> return -1  (not found)
    if (nums.empty()) return -1; // not exist

    // binary search
    int32_t i = 0;
    int32_t j = nums.size(); // find the target in [i, j)
    while (i + 1 < j) {      // exit when we have only 1 element
        uint32_t mid = i + ((j - i) >> 1);
        if (nums[mid] > target)
            j = mid;
        else
            i = mid;
    }

    // return the position
    if (nums[i] == target)
        return i;
    else
        return -1;
}

std::vector<int> searchRange(std::vector<int> &nums, int target) {
    std::vector<int> res(2, -1);
    res[0] = FindFirstPosition(nums, target);
    if (res[0] == -1) return res;
    res[1] = FindLastPosition(nums, target);
    return res;
}
```

对于FindFirstPosition这个函数的源码，可以参考[这里](#first-position-of-target)。

#### Reference



### First Bad Version

给定一个 bool 数组$nums$，其组成规则为：前面一直为false，一旦遇到了为true的元素，后面一直为true。找出第一次为true的下标。

>eg:
>{false, false, false, true, true} ,  return 3
>{false, true, true} ,  return 1
>{false, false, false} ,  return -1

#### Algorithm description and certification

与 Find position of target 类似，假设需要进行折半查找的范围是$[i, j)$, 中间位置为$mid$。

1. 当$nums[mid] = true$，查找区间可以缩减到： $[i, mid + 1)$；
2. 当$nums[mid] = false$，查找区间可以缩减到： $[mid + 1, j)$；
3. 最终$i+1 = j$时，意味着查找的区间只剩下一个元素，此时只需要判断其是否为$true$，如果等于则 i 即为第一次出现true的位置，否则返回 -1。

对于中间位置 $mid$ 的计算，考虑极端情况（最终的数组当中仅剩下两个元素）： $i=1, j= 3$, 那么我们必须使得$mid=1$，从而得到两个一样长度的子区间$[1, 2), [2, 3)$。因此，$mid = i + (j-i-1) \div 2$

```cpp
// special case
if (sz == 0) return -1; 

// binary search
i = 0, j = sz;
while (i + 1 < j)
    mid = i + ((j - i - 1) >> 1);
	if (nums[mid]) j = mid + 1;
	else i = mid + 1；
if (nums[i]) return i;
else return -1;
```

#### Code

```cpp
// find first bad version in O(lgn)
int32_t FindFirstBadVersion(std::vector<bool> &nums) {
    if (nums.empty()) return -1; // not exist

    // binary search
    int32_t i = 0;
    int32_t j = nums.size(); // find the target in [i, j)
    while (i + 1 < j) {      // exit when we have only 1 element
        uint32_t mid = i + ((j - 1 - i) >> 1);
        if (nums[mid])
            j = mid + 1;
        else
            i = mid + 1;
    }

    // return the position
    if (nums[i])
        return i;
    else
        return -1;
}
```

以上code在leetcode里面提交时，会出现有一个case过不了，后面才发现是数据溢出了，所以在定义 (i, j) 这类下标时，今后还是尽量用uint_64吧。

#### Reference



### Search a 2D matrix

给定一个二维数组$matrix[row][col]$，$target$，返回 $target$ 是否在这个矩阵当中。这个矩阵有两条性质：

1. 对于任意的正整数$j, k, j+k \leq col$，$matrix[i][j] \leq matrix[i][j+k]$ ; 也就是说每一行是**非降序排列**；
2. 对于任意的正整数$i, i+1 \leq row$，$matrix[i+1][1] \geq matrix[i][col]$ ;也就是下一行的最小数大于等于上一行的最大数。

>matrix = [  [1,   3,  5,  7], 
>                 [10, 11, 16, 20],  
>                 [23, 30, 34, 50]] 
>target = 3;
>return true; 

#### Algorithm description and certification

可以看出，总整体上来看，这个数组就时一个非降序排列的数组，因为我们可以直接将其看为一维数组，并且采用二分法来求解。假设需要进行折半查找的范围是$[i, j)$, 中间位置为$mid$ , 其对应的下标为$r=mid/col, c = mid \% col$。

1. 当$matrix[r][c] = target$，return true；
2. 当$matrix[r][c] < target$，查找区间可以缩减到： $[mid + 1, j)$；
3. 当$matrix[r][c] > target$，查找区间可以缩减到： $[i, mid)$；

```cpp
// The input is totally empty
if (row == 0 || col == 0) return false;

// binary search for the target
i = 0, j = row * col;
while (i != j)
    mid = i + ((j - i) >> 2);
	r=mid/col, c = mid % col;
	if (matrix[r][c] == target) return true;
	if (matrix[r][c] < target) i = mid + 1;
	if (matrix[r][c] > target) j = mid;
return false; // the interval is empty and we didn't find the target
```

可以很容易看出，上述算法的时间复杂度为 $O(row \times col)$.

#### Code

```cpp
bool SearchMatrix(vector<vector<int>>& matrix, int target) {
    // The input is totally empty
    uint32_t row = matrix.size();
    if (row == 0 || matrix.front().size() == 0) return false;
    uint32_t col = matrix.front().size();

    // binary search for the target
    uint32_t i = 0, j = row * col;
    while (i != j){
        uint32_t mid = i + ((j - i) >> 2);
        uint32_t r=mid / col, c = mid % col;
        if (matrix[r][c] == target) return true;
        if (matrix[r][c] < target) i = mid + 1;
        if (matrix[r][c] > target) j = mid;
    }
    return false; // the interval is empty and we didn't find the target    
}
```

#### Reference



### Search 2D matrix II

这个题时 Search 2D matrix 这个题的变种，同样给定一个二维数组$matrix[row][col]$，$target$，返回 $target$ 在这个矩阵当中的出现**次数**。这个矩阵的性质如下：

1. 对于任意的正整数$j, k, j+k \leq col$，$matrix[i][j] \leq matrix[i][j+k]$ ; 也就是说每一行是**非降序排列**；
2. 对于任意的正整数$j, k, j+k \leq row$，$matrix[j][i] \leq matrix[j+k][i]$ ; 也就是说每一列是**非降序排列**；
3. 对于每一行，每一列，数据不重复；

> matrix = [  [1, 3, 5, 7],
> 		 [2, 4, 7, 8],
> 		 [3, 5, 9, 10]]
> target = 3;
> **return** 2;  // 因为出现的次数为2

要求时间复杂度保持在$O(row + col)$.

#### Algorithm description and certification

对于这个题，其解法比较巧妙。在此直接给出其解答方式：

1. 设起始坐标$(i, j) = (1, col)$；
2. 若$matrix[i][j] = target$, 计数器加 1；
3. 若$matrix[i][j] < target$, i++；
4. 若$matrix[i][j] > target$, j--；
5. 若 $i \neq row \text{ or } j \neq 1$, 返回第一步；

在下面直接给出源码，不在给伪代码；

#### Code

```cpp
bool searchMatrixII(vector<vector<int>>& matrix, int target) {
    // special case
    if (matrix.empty() || matrix.front().empty()) return 0;  

    // find the target
    uint32_t row = matrix.size(), col = matrix.front().size();
    int32_t i = 0, j = col - 1;
    uint32_t counter = 0;
    while (i < row && j >= 0){            
        if (matrix[i][j] > target) 
            j--;
        else if (matrix[i][j] < target) 
            i++;
        else{
            counter++;
            i++, j--; // since no duplicate ele in each row and col
        }
    }
    return counter;
}
```

注意： 在定义下标 i, j 的时候，一定要定义为有符号数，因为 j 在自减的过程当中肯定会溢出。如果定义为无符号整形，此时会溢出，从而导致数据的下标访问越界。

#### Reference



### Find Peak Element

给定一个数组 $nums$, 对于任意合法的下标 $i$， 我们有 $nums[i] \neq nums[i+1]$。定义$nums[-1] = nums[sz] = -\infty$，现在的**目标**是返回一个**局部峰值**的下标（可能存在多个局部峰值，只需要随便返回一个即可），局部峰值可以理解为 一个数比它左右的两个数都要大。
**Example 1:**

```
Input: nums = [1,2,3,1]
Output: 2
Explanation: 3 is a peak element and your function should return the index number 2.
```

关于更多题目的详细内容，请参考: [Leetcode 162](https://leetcode.com/problems/find-peak-element/description/).

#### Algorithm description and certification

由于$nums[-1] = nums[sz] = -\infty$，那么只要数组 $nums$不为空，那么局部峰值一定存在（对于不为空的数组，可以看出其一定是先有一个增加的过程，最后有一个减少的过程，不考虑中间的其他增加或者减少过程）。

1. 定义一个区间 $[i, j)=[0, sz)$，使得峰值一定落在这个区间内；
2. 获取中间下标 $mid=i + (j-i)  \div 2$，那么一定有 $mid \in [i,j)$；
3. 如果 $nums[mid -1] <  nums[mid] < nums[mid+1]$，那么峰值一定存在于区间$[mid+1, j)$；
4. 如果 $nums[mid -1] <  nums[mid] > nums[mid+1]$，那么直接返回 $mid$ 即可；
5. 如果 $nums[mid -1] >  nums[mid]$，那么峰值一定存在于区间 $[i, mid)$；

```cpp
i = 0;
j = nums.size();
while (i < j) // we still have element to handle
    mid = i + ((j - i) >> 1);
	if (nums[mid-1] < nums[mid] < nums[mid+1]) i = mid + 1； // increase
	else if (nums[mid-1] < nums[mid] > nums[mid+1]) return mid; // increase and descrease 
	else if (nums[mid-1] > nums[mid]) j = mid; // decrease then xxx
	else assert(false && "An bad question"); // no equal between two continorous data
return -1; // no peak here since the nums is empty
```

可以看出，算法直接采用了**二分查找**的方法，因此时间复杂度为$O(\lg n)$.

#### Code

```cpp
int FindPeakElement(std::vector<int> &nums) {
    auto GetNums = [&nums](int index) {
        if (index == -1 || index == nums.size()) return INT64_MIN; // look out
        return int64_t(nums[index]);
    };
    int i = 0;
    int j = nums.size();
    while (i < j) {                   // we still have element to handle
        int mid = i + ((j - i) >> 1); // mid belongs to [i, j)
        if (GetNums(mid - 1) < GetNums(mid) && GetNums(mid) < GetNums(mid + 1))
            i = mid + 1; // increase
        else if (GetNums(mid - 1) < GetNums(mid) && GetNums(mid) > GetNums(mid + 1))
            return mid;
        else if (GetNums(mid - 1) > GetNums(mid))
            j = mid; // decrease then xxx
        else
            assert(false && "An bad question"); // no equal between two continorous data
    }
    return -1; // no peak here since the nums is empty
}
```

请注意：在代码第2~5行当中，将原来的 int32_t 改为了 int64_t 只是为了用 **int64_t 的最小值**，因为其最小值是小于 int32_t 的最小值的；否则，当输入为 INT32_MIN 时，会出现 assert (代码第17行)。

#### Reference



### Search in Rotated Sorted Array

Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e., `[0,1,2,4,5,6,7]` might become `[4,5,6,7,0,1,2]`).

You are given a target value to search. If found in the array return its index, otherwise return `-1`.

You may assume no duplicate exists in the array.

Your algorithm's runtime complexity must be in the order of *O*(log *n*).

**Example 1:**

```
Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4
```

**Example 2:**

```
Input: nums = [4,5,6,7,0,1,2], target = 3
Output: -1
```

You may see this problem in [Leetcode 33](https://leetcode.com/problems/search-in-rotated-sorted-array/description/).

#### Algorithm description and certification

对于数组 $nums$ 来说，设当前需要在范围 $[i, j)$ 中寻找 $target$，当前还不清楚旋转点的具体位置，那么我们可以分如下情况进行讨论：

1. 取中间位置$mid = i + (j - i) \div 2$，若$nums[mid] = target$，直接return $mid$；

2. 若$nums[i] < nums[j-1]$，当前$nums$ 在 $[i,j)$范围内是一个**单调递增的数组**；

   a. 若 $nums[mid] < target$，搜索范围可以缩减到$[mid+1, j)$；

   b. 若 $nums[mid] > target$，搜索范围可以缩减到$[i, mid)$；

3. 若$nums[i] > nums[j-1]$，那么旋转点一定位于区间$[i, j)$ 之间；

   a. 若 $nums[mid] \geq nums[i]$, 那么数组在区间$[i , mid]$**单调递增**；

   ​	a). 若 $target \in [nums[i], nums[mid])$，则搜索范围可以缩减到$[i, mid)$；

   ​	b). 否则搜索范围可以缩减到：$[mid+1, j)$；

   b. 若 $nums[mid] \leq nums[j-1]$, 那么数组在区间$[mid , j-1]$**单调递增**；

   ​	a). 若 $target \in (nums[mid], nums[j-1]]$，则搜索范围可以缩减到$[mid+1, j)$；

   ​	b). 否则搜索范围可以缩减到：$[i, mid)$；

4. 若 $j > i$, 返回第一步，否则原题无解，返回 -1；

```cpp
i = 0, j = nums.size();
while (i < j)
	mid = i + ((j-i) >> 1);
	if (nums[mid] == target) return mid;
	if (nums[i] < nums[j-1]) 
        if (nums[mid] < target) i = mid + 1;
		else j = mid;
	else if (nums[i] > nums[j-1]) 
        if (nums[mid] >= nums[i])
            if (target >= nums[i] && target < nums[mid]) j = mid;
			else i = mid + 1;
		else // nums[mid] <= nums[j-1]
            if (target > nums[mid] && target <= nums[j-1]) i = mid + 1;
			else j = mid;
	else return (nums[i] == target ? i : -1); // only one ele
return -1; // no solution 
```

由于每此循环都可以将原来的区间减为一半，因此时间复杂度为 $O(\lg n)$； 此外，代码可以进行一定程度的合并，但是这里为了逻辑上的清晰，就将所有的都保留下来了。

* 化简

  对于第2, 3步，很明显第3步的逻辑包含了第2步当中的逻辑，因此我们可以仅仅采用第3步当中的逻辑，可得：

  ```cpp
  i = 0, j = nums.size();
  while (i < j)
  	mid = i + ((j-i) >> 1);
  	if (nums[mid] == target) return mid;
  	if (j - 1 = 1) return (nums[i] == target ? i : -1); // only one ele
      
  	// binary search
  	if (nums[mid] >= nums[i])
          if (target >= nums[i] && target < nums[mid]) j = mid;
  		else i = mid + 1;
  	else // nums[mid] <= nums[j-1]
          if (target > nums[mid] && target <= nums[j-1]) i = mid + 1;
  		else j = mid;
  return -1; // the array is empty
  ```

  化简后的源码如下所示。

#### Code

```cpp
int SearchRotatedArray(std::vector<int> &nums, int target) {
    int i = 0, j = nums.size();
    while (i < j) {
        int mid = i + ((j - i) >> 1);
        if (nums[mid] == target) return mid;
        if (i + 1 == j) return (nums[i] == target ? i : -1); // only one ele

        // binary search
        if (nums[mid] >= nums[i]) {
            if (target >= nums[i] && target < nums[mid])
                j = mid;
            else
                i = mid + 1;
        }
        else { // nums[mid] <= nums[j-1]
            if (target > nums[mid] && target <= nums[j - 1])
                i = mid + 1;
            else
                j = mid;
        }
    }
    return -1; // no solution
}
```

#### Reference



### Search in Rotated Sorted Array II

Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e., `[0,0,1,2,2,5,6]` might become `[2,5,6,0,0,1,2]`).

You are given a target value to search. If found in the array return `true`, otherwise return `false`.

**Example 1:**

```
Input: nums = [2,5,6,0,0,1,2], target = 0
Output: true
```

**Example 2:**

```
Input: nums = [2,5,6,0,0,1,2], target = 3
Output: false
```

**Follow up:**

- This is a follow up problem to [Search in Rotated Sorted Array](https://leetcode.com/problems/search-in-rotated-sorted-array/description/), where `nums` may contain duplicates.
- Would this affect the run-time complexity? How and why?

You may see this problem in [Leetcode 81](https://leetcode.com/problems/search-in-rotated-sorted-array-ii/description/).

#### Algorithm description and certification

对于数组 $nums$ 来说，设当前需要在范围 $[i, j)$ 中寻找 $target$，同样，当前还不清楚旋转点的具体位置，分如下情况进行讨论：

1. 取中间位置$mid = i + (j - i) \div 2$，

2. 若$nums[mid] = target$，直接return $mid$；

3. 若 $i+1=j$，return nums[i] == target; // 只剩一个元素

4. 若 $nums[mid] > nums[i]$, 那么数组在区间$[i , mid]$**单调递增**；

   a). 若 $target \in [nums[i], nums[mid])$，则搜索范围可以缩减到$[i, mid)$；

   b). 否则搜索范围可以缩减到：$[mid+1, j)$；

5. 否则，若 $nums[mid] < nums[j-1]$, 那么数组在区间$[mid , j-1]$**单调递增**；

   a). 若 $target \in (nums[mid], nums[j-1]]$，则搜索范围可以缩减到$[mid+1, j)$；

   b). 否则搜索范围可以缩减到：$[i, mid)$；

6. 否则，若 $nums[i] = nums[mid]$，i++；

7. 否则，若 $nums[j] = nums[mid]$，j--；

8. 否则，$nums[mid] < nums[i] \text{ and } nums[mid] > nums[j-1]$ ，此时无解，返回 -1；

9. 若 $j>i$，返回第一步；否则返回 -1；

```cpp
i = 0, j = nums.size();
while (i < j)
	mid = i + ((j-i) >> 1);
	if (nums[mid] == target) return true;
	if (j - 1 = 1) return (nums[i] == target ? true : false); // only one ele
    
	// binary search
	if (nums[mid] > nums[i])
        if (target >= nums[i] && target < nums[mid]) j = mid;
		else i = mid + 1;
	else if (nums[mid] < nums[j-1])
        if (target > nums[mid] && target <= nums[j-1]) i = mid + 1;
		else j = mid;
	else if (nums[mid] == nums[i]) i++;
	else if (nums[mid] == nums[j - 1]) j--;
	else return false; // nums[mid] < nums[i] and nums[mid] > nums[j-1]
return false; // the array is empty
```

这种解法，在最坏的情况下，时间复杂度为 $O(n)$，最好的时间复杂度为：$O(\lg n)$。最坏的输入大致为：{1, 1, 1, 1, 1, 1,1, 1, 1, 2, 1, 1, 1,1,, 1, 1, 1, 1}, trarget = 2; 此时在每一轮迭代当中，i, j 移动的步长均为 1；

#### Code

```cpp
bool SearchRotatedArrayII(std::vector<int> &nums, int target) {
    int i = 0, j = nums.size();
    while (i < j) {
        int mid = i + ((j - i) >> 1);
        if (nums[mid] == target) return true;
        if (i + 1 == j) return (nums[i] == target ? true : false); // only one ele

        // binary search
        if (nums[mid] > nums[i]) {
            if (target >= nums[i] && target < nums[mid])
                j = mid;
            else
                i = mid + 1;
        }
        else if (nums[mid] < nums[j - 1]) {
            if (target > nums[mid] && target <= nums[j - 1])
                i = mid + 1;
            else
                j = mid;
        }
        else if (nums[mid] == nums[i])
            i++;
        else if (nums[mid] == nums[j - 1])
            j--;
        else
            return false; // nums[mid] < nums[i] and nums[mid] > nums[j-1]
    }
    return false; // no solution
}
```

#### Reference



### Find Minimum in Rotated Sorted Array

Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e.,  `[0,1,2,4,5,6,7]` might become  `[4,5,6,7,0,1,2]`).

Find the minimum element.

You may assume no duplicate exists in the array.

**Example 1:**

```
Input: [3,4,5,1,2] 
Output: 1
```

**Example 2:**

```
Input: [4,5,6,7,0,1,2]
Output: 0
```

You may see this problem in [Leetcode 153](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/description/).

#### Algorithm description and certification

对于数组 $nums$ 来说，设当前需要在范围 $[i, j)$ 中寻找最小值，由于当前还不清楚旋转点的具体位置，分如下情况进行讨论：

1. 取中间位置$mid = i + (j - i) \div 2$，

2. 若 $i+1=j$，return nums[i]; // 只剩一个元素

3. 若 $nums[i] < nums[j-1]$，数组在区间$[i , j)$**单调递增**，直接返回 $nums[i]$；

4. 否则必有：$nums[i] > nums[j-1]$

   a. 若 $nums[mid] >= nums[i]$, 那么最小值一定位于区间 $(mid, j)$；

   b. 否则必有 $nums[mid]  \leq nums[j-1]$, 那么最小值一定位于区间 $(i, mid]$；

5. 若 $j>i$，返回第一步；否则返回 INT_MIN 以表示数组为空；

```cpp
i = 0, j = nums.size();
while (i < j)
	mid = i + ((j-i) >> 1);
	if (nums[i] <= nums[j-1]) return nums[i]; // 等于号表示当前只有一个元素
	else if (nums[i] > nums[j-1]) 
        if (nums[mid] >= nums[i])
            i = mid + 1;
		else // nums[mid] <= nums[j-1]
            i++;
			j = mid + 1;
return INT_MIN; // no solution 
```

#### Code

```cpp
int FindMinInRotatedArray(std::vector<int> &nums) {
    int i = 0, j = nums.size();
    while (i < j) {
        int mid = i + ((j - i) >> 1);
        if (nums[i] <= nums[j - 1])
            return nums[i]; // only one element or ascending order
        else if (nums[i] > nums[j - 1]) {
            if (nums[mid] >= nums[i])
                i = mid + 1;
            else { // nums[mid] <= nums[j-1]
                i++;
                j = mid + 1;
            }
        }
    }
    return INT_MIN; // no solution
}
```

#### Reference



### Find Minimum in Rotated Sorted Array II

Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e.,  `[0,1,2,4,5,6,7]` might become  `[4,5,6,7,0,1,2]`).

Find the minimum element.

The array may **contain duplicates**.

**Example 1:**

```
Input: [1,3,5]
Output: 1
```

**Example 2:**

```
Input: [2,2,2,0,1]
Output: 0
```

**Note:**

- This is a follow up problem to [Find Minimum in Rotated Sorted Array](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/description/).
- Would allow duplicates affect the run-time complexity? How and why?

#### Algorithm description and certification

与 Find Minimum in Rotated Sorted Array 相比，这个题当中的数组 $nums$ 可能含有重复元素；设当前需要在范围 $[i, j)$ 中寻找最小值，由于当前还不清楚旋转点的具体位置，分如下情况进行讨论：

1. 取中间位置$mid = i + (j - i) \div 2$，

2. 若 $i+1=j$，return nums[i]，因为当前仅仅剩下一个元素；

3. 若 $nums[i]=nums[j-1]$，此时我们不妨将搜索区间更新为：$[i, j-1)$；

4. 否则，若 $nums[i] < nums[j-1]$，数组在区间$[i , j)$**单调递增**，直接返回 $nums[i]$；

5. 否则，必有：$nums[i] > nums[j-1]$

   a. 若 $nums[mid] >= nums[i]$, 那么最小值一定位于区间 $(mid, j)$；

   b. 否则，必有 $nums[mid]  \leq nums[j-1]$, 那么最小值一定位于区间 $(i, mid]$；

6. 若 $j>i$，返回第一步；否则返回 INT_MIN 以表示数组为空；

与不带重复元素的问题相比，仅仅加上了第3步：举个极端的例子：$nums = \{1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1\}$, 那么若我们采用二分的方法来寻找，最开始的 $mid=5$，但是此时我们有：$nums[0]=nums[n-1]=nums[mid]$，导致无法对原区间进行折半查找；此时，我们只能排除掉 $i, j$ 当中的一个，从而使得对于这类输入的时间复杂度达到了 $O(n)$;

因此，这种算法的时间复杂度在最坏情况下为$O(n)$, 平均为：$O(\lg n)$。

```cpp
i = 0, j = nums.size();
while (i < j)
	mid = i + ((j-i) >> 1);
	if (nums[i] < nums[j-1] || i == j-1) return nums[i]; // 单调递增或只有一个元素
	else if (nums[i] == nums[j-1]) i++; // 相等的情况
	else if (nums[i] > nums[j-1]) 
        if (nums[mid] >= nums[i])
            i = mid + 1;
		else // nums[mid] <= nums[j-1]
            i++;
			j = mid + 1;
return INT_MIN; // no solution 
```

#### Code

```cpp
int FindMinInRotatedArrayII(std::vector<int> &nums) {
    int i = 0, j = nums.size();
    while (i < j) {
        int mid = i + ((j - i) >> 1);
        if (i == j - 1 || nums[i] < nums[j - 1])
            return nums[i]; // only one element or ascending order
        else if (nums[i] == nums[j - 1])
            i++;
        else if (nums[i] > nums[j - 1]) {
            if (nums[mid] >= nums[i])
                i = mid + 1;
            else { // nums[mid] <= nums[j-1]
                i++;
                j = mid + 1;
            }
        }
    }
    return INT_MIN; // no solution
}
```

#### Reference



### Median of Two Sorted Arrays

There are two sorted arrays *A* and *B* of size *m* and *n* respectively. Find the **median** of the two sorted arrays.

**Example**

Given `A=[1,2,3,4,5,6]` and `B=[2,3,4,5]`, the median is `3.5`.

Given `A=[1,2,3]` and `B=[4,5]`, the median is `3`.

**Challenge**

The overall run time complexity should be O(log (m+n)).

You may see this problem in [Leetcode 4](https://leetcode.com/problems/median-of-two-sorted-arrays/description/).

#### Algorithm description and certification

这个题是一个典型的二分搜索的题目，首先我们考虑寻找这个数组合并后第 $k$ 大的数，设数组 $nums1, nums2$ 的长度分别为： $sz1, sz2$，寻找的区间即为：$[beg1, sz1), [beg2, sz2)$，最开始时：$beg1=beg2=0$；

1. 若 $beg1 \neq sz1 \text{ and } beg2 \neq sz2 \text{ and } k \neq 1$，进入第二步，否则跳至第7步；
2. 计算数组 $nums1$ 的指针移动量：$offset1= min((k>>1) -1, sz - beg1-1)$；// 进行**二分查找**
3. 计算数组 $nums2$ 的指针移动量：$offset2= $min(k - offset1 - 2, sz2 - beg2 - 1)； 
4. 若 $nums1[beg1+offset1] > nums2[beg2+offset2]$，那么第 k 大的数一定不会落在$nums2$的区间：$[beg2, beg2+offset2]$，因此可以有：$beg2=beg2+offset2 +1， k=k-offset2 -1$；
5. 否则，第k大的数一定不会落在$nums1$的区间：$[beg1, beg1+offset1]$，因此可以有：$beg1=beg1+offset1 +1, k=k-offset1 -1$；
6. 返回第 1 步；
7. 若 $k=1$，返回 $min(nums1[beg1], nums2[beg2])$； // 小心数组越界
8. 否则，若$beg1 \neq sz1$，返回$nums1[beg1+k-1]$；
9. 否则，必有 $beg2 \neq sz2$，返回$nums2[beg2+k-1]$；

按照如上方式即可找到第 $k$ 大的数，稍微进行扩展即可实现找中位数，见源码。

```cpp
beg1 = beg2 = 0;
sz1 = nums1.size();
sz2 = nums2.size();
k = (sz1 + sz2) / 2 + (sz1 + sz2) % 2;
has_next = ((sz1 + sz2) % 2 == 1 ? 0 : 1); // 总个数为偶数时，需要找下一个元素
while (sz1 != beg1 && sz2 != beg2 && k != 1) // not overflow
	offset1 = min((k >> 1) - 1, sz1 - beg1 - 1); // if k=2, offset is 0
	offset2 = min(k - offset1 - 2, sz2 - beg2 - 1); // if k is 2, offset is 0;
	if (nums1[beg1+offset1] > nums2[beg2+offset2])
        beg2 = beg2 + offset2 + 1；
        k = k - offset2 - 1；
    else
    	beg1 = beg1 + offset1 + 1；
        k = k - offset1 - 1；
// calculate the res， 这部分逻辑简单，但是写出来却比较繁琐，建议直接看源码。
```

#### Code

```cpp
double FindMedianSortedArrays(std::vector<int> &nums1, std::vector<int> &nums2) {
    uint32_t beg1 = 0;
    uint32_t beg2 = 0;
    uint32_t sz1 = nums1.size();
    uint32_t sz2 = nums2.size();
    uint32_t k = (sz1 + sz2) / 2 + (sz1 + sz2) % 2;
    uint32_t has_next = ((sz1 + sz2) % 2 == 1 ? 0 : 1);// 总个数为偶数时，需要找下一个元素
    while (sz1 != beg1 && sz2 != beg2 && k != 1) {                    // not overflow
        uint32_t offset1 = std::min((k >> 1) - 1, sz1 - beg1 - 1);    // k=2, offset1 = 0
        uint32_t offset2 = std::min(k - offset1 - 2, sz2 - beg2 - 1); // k=2, offset2 = 0
        if (nums1[beg1 + offset1] > nums2[beg2 + offset2]) {
            beg2 = beg2 + offset2 + 1;
            k = k - offset2 - 1;
        }
        else {
            beg1 = beg1 + offset1 + 1;
            k = k - offset1 - 1;
        }
    } 
    
    // calculate the res, 为了简单，我们这里定义nums1[sz1] = nums2[sz2] = +INF
    auto GetData = [](std::vector<int> &nums, uint32_t index) {
        if (index == nums.size()) return INT64_MAX;
        return int64_t(nums[index]);
    };
    // 当 k=1 时，直接取两个数组当中的更小者
    if (k == 1) {
        if (has_next == 1) {
            double median = std::min(GetData(nums1, beg1), GetData(nums2, beg2));
            GetData(nums1, beg1) > GetData(nums2, beg2) ? beg2++ : beg1++;
            median += std::min(GetData(nums1, beg1), GetData(nums2, beg2));
            return median / 2.0;
        }
        else
            return std::min(GetData(nums1, beg1), GetData(nums2, beg2));
    }
    // 若有一个数组为空，不要忘记把 k 给加上
    else if (sz1 == beg1) {
        if (has_next == 1) {
            return (nums2[beg2 + k - 1] + nums2[beg2 + k]) / 2.0;
        }
        else
            return nums2[beg2 + k - 1];
    }
    else if (sz2 == beg2) {
        if (has_next == 1) {
            return (nums1[beg1 + k - 1] + nums1[beg1 + k]) / 2.0;
        }
        else
            return nums1[beg1 + k - 1];
    }
    else
        assert(false && "Bug.");
}
```

#### Reference



### Sqrt

Implement `int sqrt(int x)`.

Compute and return the square root of *x*, where *x* is guaranteed to be a non-negative integer.

Since the return type is an integer, the decimal digits are truncated and only the integer part of the result is returned.

**Example 1:**

```
Input: 4
Output: 2
```

**Example 2:**

```
Input: 8
Output: 2
Explanation: The square root of 8 is 2.82842..., and since 
             the decimal part is truncated, 2 is returned.
```

You may see this problem in [Leetcode 69](https://leetcode.com/problems/sqrtx/description/).

#### Algorithm description and certification

设我们的输入为一个 int 型的数据 $x$，由于时做开方，那么其有效的输入范围为：$[0, 0x7fffffff]$，也就是说结果的范围会落在区间 $[0, 0x10000]$。在这个区间内，我们进行有效的二分查找，可以明显看出，最多通过16次迭代便可以找出结果。

1. 设 $i=0,j=0x10000$；
2. 如果 $i<j$，$mid=i+(j-i+1) \div 2$，否则转入第6步；
3. 若 $mid \times mid > x$，那么搜索区间可以缩减为：$[i, mid)$；
4. 否则，若 $mid \times mid < x$，搜索区间可以被缩减为：$[mid, j]$；// 结果仍然可能是 $mid$
5. 否则，返回 $mid$；
6. 返回 $i$； // 此时区间仅有一个有效元素

注意：在第3，4步当中，我们把搜索区间分别缩减到$[i, mid)，[mid, j]$，因此为了防止可能的死循环，在计算$mid$时，若当前区间的有效数据个数为偶数时，我们总是取靠后的那一个。 eg，当$[i, j] = [1, 2]$时，$mid=2$，从而使得在第3,4步当中，无论走哪一步，都能将原区间缩减到只有一个元素。

```cpp
i = 0, j = 0x10000;
while (i != j)
    mid = ((j - i + 1) >> 1) + i;
	if (mid * mid > x)
        j = mid - 1;
	else if (mid * mid < x)
        i = mid;
	else // mid * mid = x
        return mid;
return i; // only 1 element
```



#### Code

```cpp
int mySqrt(int x) {
    if (x < 0) assert(false && "Invalid input x.");
    uint32_t i = 0, j = 0x10000;
    while (i != j){
        uint64_t mid = ((j - i + 1) >> 1) + i; // 防止溢出
        if (mid * mid > x)
            j = mid - 1;
        else if (mid * mid < x)
            i = mid;
        else // mid * mid = x
            return mid;
    }
    return i; // only 1 element   
}
```

#### Reference



### Wood cut

Given n pieces of wood with length `L[i]` (integer array). Cut them into small pieces to guarantee you could have equal or more than k pieces with the same length. What is the longest length you can get from the n pieces of wood? Given L & k, return the maximum length of the small pieces.

You couldn't cut wood into float length.If you couldn't get >= *k* pieces, return `0`.
**Example**

For `L=[232, 124, 456]`, `k=7`, return `114`.

**Challenge**

O(n log Len), where Len is the longest length of the wood.

#### Algorithm description and certification

这个题可以直接采用二分搜索的方式直接去搜索最大长度 $max\_len$。

1. 确认可行的**搜索区间** $[i, j]$：$max\_len \in [0, argmax_i(L_i)]$；
2. 若 $i < j$，那么原来的区间里面还最少有两个元素，进入第3步；否则进入第7步；
3. 设 $mid = i + (j-i +1)\div 2$；
4. 若 能将原来的所有 wood cut 成最少 $k$ 段长度为 $mid$ 的wood，那么搜索区间可以缩减到：$[mid, j]$；
5. 否则，搜索区间可以缩减到：$[i,mid-1]$；
6. 返回到第2步；
7. 因为 $i =j$，所以我们只需要返回 $i$ 即可。

```c++
i = 0; 
j = max(L); // j为数组L中的最大值
while (i < j)
    mid = i + ((j - i + 1) >> 1);
	if (ValidLength(L, k, mid)) // 这个函数表示长度选为mid时，能将L最少划分为k段
        i = mid;
	else 
        j = mid - 1;
return i;
```

注意：自己可以去推一下这儿在算 $mid$ 时为什么把需要加 1。理由跟前面各种题目类似（最后只剩下两个元素的时候，这种拆分方式需要确保两个区间各包含一个元素）。

#### Code

```cpp
int WoodCut(std::vector<int> &L, int k) {
    // the combination of L, k, length is valid or not
    auto ValidLength = [](std::vector<int> &L, int k, uint32_t length) {
        uint32_t segment = 0;
        for (auto wood : L) {
            segment += wood / length;
            if (segment >= k)
                return true;
        }
        return false;
    };
    
    // special case 
	if (L.empty()) return 0;
    
    // binary search for the max length
    uint32_t i = 0;
    uint32_t j = *std::max_element(L.begin(), L.end()); // j为数组L中的最大值
    while (i < j) {
        uint32_t mid = i + ((j - i + 1) >> 1);
        if (ValidLength(L, k, mid)) // 这个函数表示长度选为mid时，能将L最少划分为k段
            i = mid;
        else
            j = mid - 1;
    }
    return i;
}
```

#### Reference



### Summary

对于这些二分搜索的题目来说，有以下几点需要注意：

1. 在计算 mid （中间元素的下标） 时，需要考虑到最后**只剩下两个元素**的时候，是否还能将原区间划分为各包含一个元素的区间，否则会有死循环的风险，如 [wood cut](#wood-cut) 这个题）；
2. 中间元素如果能在下一轮迭代中剔除的话，尽量剔除（这样便不会出现第一个问题）；
3. 为了加快速度，对于最开始的搜索区间，有时候可以采用一定的方法进行优化(如 [sqrt(x)](#sqrt) 这个题)；
4. 对于某些条件较为复杂的问题，最好是将其各个分支均列出来，从而得到清晰的逻辑（最后，如果想要简化代码，再对逻辑进行合并，如 [Search in rotated sorted array](#search-in-rotated-sorted-array) 等）。