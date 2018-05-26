### Random

In this part, we will focus on the random algorithm, such as shuffle, reservoir sample problems.

#### Shuffle

##### Problem description

给定一组数据，给出这组数据的一个随机排列。  
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

{%ace edit=true, lang='c_cpp'%}
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
{%endace%}

##### Test

Ignored.

##### Reference

[Data structure and algorithm lintcode/leetcode](https://algorithm.yuanbin.me/zh-hans/basics_algorithm/probability/shuffle.html)

#### Reservoir Sample

{%ace edit=true, lang='c_cpp'%}
void AlgorithmR() {
  // AlgorithmR:
  //  it is a sampling algorithm without taking the weight into consideration
  // Proof:
  //  Define the probability of element index (count from 0) i is still in the
  //  pool is p(i);
  //  if (i < m_k)
  //    p(i) = 1 * (m_k / (m_k+1)) * ((m_k+1) / (m_k+2)) *... ((n-1) / n)
  //         = m_k / n
  //  else
  //    p(i) = (m_k / (i+1)) * ((i+1) / (i+2)) *... ((n-1) / n) = m_k / n
  // Special case
  res.clear();
  if (m_k > m_data.size()) {
    assert(false && "Invalid sampling problem here.");
  }
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
{%endace%}
