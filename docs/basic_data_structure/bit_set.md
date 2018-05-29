### bit set

In this part, we will focus on the bit set related algorithm, such as **sort of big data**, **search of big data**, **remove duplicate of big data**, **bloom filter**, etc.  
Bit set can be viewed as a kind of data structure just like the set. The difference is that bit set only saves several bit per element to indicate the status of the element. Just for an example, if we just want to do sorting on the data without duplicates, we can use 1 bit to indicate this element is exist or not. The length of the bit set is determined by the range of the element. So it is not a good choice in sparse data.

#### Sort/Search/Remove duplicates

  **Sort**: 使用 bit set 数据结构对数据进行排序，假设所有的数据不会重复；  
  **Search**: 使用 bit set 实现一个set数据结构，从而进行检测数据是否在集合当中；  
  **Remove duplicates**: 使用 bit set 实现一个set数据结构，从而对数据进行去重；  
  以上三种应用的方式都非常类似，以下仅仅以sort为例进行说明。

##### Problem description

给定一组不含重复元素的数据(**数据非常多, 难以放入内存**)以及其范围，给出其排列后的结果(**排序问题**)。  
eg.  
　　input: {1, 3, 2, 5}, 10   
　　output can be: {１, ２, ３, 5}

##### Algorithm description and certification

假设输入为： arr[n], ${arr[n]}\leq{N}$那么可以有如下算法：

  ```cpp
  // 1. Create the bit set data structure
  bitset<N> flag;
  for i = 0 ~ n:
    flag[arr[i]] = 1;
  for i = 0 ~ N:
    if flag[i] == 1:
      // this is the result after sort, it is nearly the same with the radix sort
      res.push_back(i);
  ```

##### Code

```cpp
void Sort(std::vector<uint32_t> *src) {
  // Create the bit set data structure
  const uint32_t N = 10;
  std::bitset<N> flag;
  for (std::size_t i = 0; i < src->size(); i++)
  {
    flag.set(i);
  }

  // Get the sorted result
  uint32_t cur_index = 0;
  for (std::size_t i = 0; i < N; i++)
  {
    if (flag.test(i))
    {
      (*src)[cur_index++] = i;
    }
  }
}

```

##### Test

Ignored.

##### Reference

[Bitmap in big data](https://www.cnblogs.com/yangjiannr/p/da-shu-ju-chu-libitmap.html)
