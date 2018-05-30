### Bit set

In this part, we will focus on the bit set related algorithm, such as **sort of big data**, **search of big data**, **remove duplicate of big data**, **bloom filter**, etc.  
Bit set 可以被视为集合（Set）这种数据结构， 但是二者之间的主要差异是Bit set 一般仅仅用几个bit来表示一个元素。

#### Sort/Search/Remove duplicates

  1. **Sort**: 使用 bit set 数据结构对数据进行排序，假设所有的数据不会重复；  
  2. **Search**: 使用 bit set 实现一个set数据结构，从而进行检测数据是否在集合当中；  
  3. **Remove duplicates**: 使用 bit set 实现一个set数据结构，从而对数据进行去重；  
  以上三种应用的方式都非常类似，以下仅仅以sort为例进行说明。

##### Problem description

给定一组不含重复元素的数据(**数据非常多, 难以放入内存**)以及其范围，给出其排列后的结果(**排序问题**)。  
eg.  
　　input: {1, 3, 2, 5}, 10   
　　output can be: {１, ２, ３, 5}

##### Algorithm description and certification

假设输入为： $arr[n]$, ${arr[n]}\leq{N}$那么可以有如下算法：

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


#### Bloom filter

Bloom filter与 Bit set非常类似，其一般被用于判断某个元素是否存在与某个集合当中。与Bit Set 不同的是，Bloom filter需要用多个比特来表示一个元素是否存在(多个元素也可以复用这些bit)。

##### Problem description

某些存储系统的设计中，会存在空查询缺陷：当**查询一个不存在的key**时，需要访问慢设备，导致效率低下。　
1. 对于某些系统，Value 保存在磁盘中，访问磁盘需要花费大量时间，然而使用布隆过滤器可以快速判断某个Key对应的Value是否存在，从而直接将空查询直接忽略，因此可以避免很多不必要的磁盘IO操作。 
2. 在前端系统当中，如果经常发生空查询操作，那么会引起大量不必要的服务器请求。

##### Algorithm description and certification

* 算法

```cpp
// １. 生成K个hash函数，每个函数能够独立地将key映射为一个整数
function<uint32_t(string)> hash[K];
bitset<N> flag; // 标志位清０

// 2. 插入所有的key
for (auto key : keys)
  for i = 0 ~ K:
    flag[hash[i](key)].set();

// 3. 查询是否存在
string key = "str need to search";
for i = 0 ~ K:
    if ! flag[hash[i](key)].test():
      return false; // failed the test
return true; // passed all the test
```

* 优缺点

1. 一个$key$仅仅由$K$个bit来表示，并且其他的元素还能复用这些比特，从而节省了空间；
2. 无法删除一个$key$,因为多个元素复用了存储空间；
3. 对于false positive, 算法有一定的误判概率。即某个元素本来不在集合当中，但是在判断的时候返回的是存在于集合当中。

* False positive的概率

$n$: 当前集合当中的元素个数；  
$K$: 相互独立的hash函数个数；  
$N$: 比特标志位的长度；  
$i$: 一个随机数，并且满足$i\in[0, N)$;  
$P(key)$: 某key不在集合当中，但是Bloom filter认为其在集合当中的概率;  
那么：  
$p(flag[i]=0)=(1-\frac{1}{N})^{Kn}$(1)  
$\therefore$ 若一个key不在集合当中，其由hash函数生成的随机下标所对应的flag是一个随机数；  
$P(key)=(1-p(flag[i]=0))^{K}=(1-(1-\frac{1}{N})^{Kn})^{K}$(2)  
$\therefore$ 当 $n,N\to\infty$，我们有：  
$P(key)=\lim\limits_{n,N\to\infty}(1-(1-\frac{1}{N})^{Kn})^{K}=(1-e^\frac{-Kn}{N})^{K}$(3)

* 最优hash函数个数$K$


##### Code

##### Test

##### Reference

  1. [布隆过滤器(Bloom Filter)详解](https://www.cnblogs.com/liyulong1982/p/6013002.html)
  2. [Wikipedia: Bloom Filter](https://en.wikipedia.org/wiki/Bloom_filter