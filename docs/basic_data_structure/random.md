### Random

In this part, we will focus on the random algorithm, such as shuffle, reservoir sample problems.

#### Shuffle

##### Problem description

给定一组数据，给出这组数据的一个随机排列(**排列问题**)。  
eg.  
　　input: {1, 3, 2, 5}   
　　output can be: {2, 3, 1, 5} or {5, 2, 1, 3}...

##### Algorithm description and certification

假设输入为： arr[n], 那么可以有如下算法：

  ```c
  for i = 1 ~ n:
    j = rand() % (n - i + 1)
    swap(arr[j], arr[n - i])
  ```

  1. 在第一轮循环当中，随机数$$j \in [0, n)$$, 那么有： $$P(j) = \frac{1}{n}$$ 
  2. 交换arr[j]与arr[n-i], 从而将arr[j]作为洗出来的第一张牌放在最后，从而得知，每一张牌放在最后的概率均为$$P(j) = \frac{1}{n}$$；
  3. 在第i轮循环选中了最初数组当中的元素k，那么有：$$P(k) = \frac{1}{n-i+1} \times \prod_{j=0}^{i-2}\frac{n-j-1}{n-j} = \frac{1}{n}$$ 

##### Code

```cpp
void Shuffle(std::vector<uint32_t> *src) {
  srand((unsigned)time(NULL));
  const uint32_t sz = src->size();
  for (std::size_t i = 0; i < sz; i++) {
    uint32_t r = rand() % (sz - i);
    uint32_t tmp = (*src)[r];
    (*src)[r] = (*src)[sz - i - 1];
    (*src)[sz - i - 1] = tmp;
  }
}
```

##### Test

Ignored.

##### Reference

[Data structure and algorithm lintcode/leetcode](https://algorithm.yuanbin.me/zh-hans/basics_algorithm/probability/shuffle.html)

#### Reservoir Sample

##### Problem description

给定一组数据，从中进行不放回的随机抽取$$k$$个数(**组合问题**)。  
eg.  
　　input: {1, 3, 2, 5}，　k = 2;   
　　output can be: {2, 3} or {1, 3}...

##### Algorithm description and certification

假设输入为：　$$ arr[sz] $$, $$k$$, 并且$$ {k}\leq{sz} $$可以有如下算法：

```cpp
// initialize
assert(k <= sz);
res[0:k] = arr[0:k]; // 区间为：　[0, k)
for (i = k; i < sz; i++)
  r = rand() % (i + 1);
  if (r < k)
    res[r] = arr[i];
```

1. 若 $$ sz=k $$, 那么初始化会搞定这个问题，即每个元素都会被选中;
2. 若 $$ sz=(k+1) $$, 那么当 $$ i=k $$时，新元素被加入到结果当中的概率为：　$$\frac{k}{k+1}$$, 已经放入结果当中的元素继续存在于结果当中的概率也为：$$\frac{k}{k+1}$$;
3. 当 $$ sz > \left(k+1\right) $$, 同理可以推出上述结果。

##### Code

```cpp
void AlgorithmR() {
  res.clear();
  m_res.resize(m_k);
  assert(m_k < m_data.size() && "Invalid sampling problem here.");
  // Initialize
  for (uint32_t i = 0; i < m_k; i++) {
    res[i] = m_data[i];
  }
  // Load data from the disk and update the Node(data) in the pool
  srand((unsigned)time(NULL));
  for (uint32_t i = m_k; i < m_data.size(); i++) {
    uint32_t r = rand() % (i + 1);
    if (r < m_k) {
      res[r] = m_data[i];
    }
  }
}
```

##### Test

Ignored.

##### Reference
Also, there are some other extension of the sampling algorithm, just like **weighted sampling algorithm**, you can refer to [Wikipedia](https://en.wikipedia.org/wiki/Reservoir_sampling) for more information.

