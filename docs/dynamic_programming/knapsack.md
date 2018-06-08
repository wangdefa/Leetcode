## Knapsack

[TOC]

[背包问题](https://en.wikipedia.org/wiki/Knapsack_problem) 是一个典型的[组合优化问题](https://en.wikipedia.org/wiki/Combinatorial_optimization): 通过给定$n​$件可选物品的重量($weight​$)与价值($value​$)，以及背包的容量($volumn​$)；对于其中的某一件物品$i​$，其价值与重量分为$value_i, weight_i​$；找到物品的一种组合方式，使得在这些物品的总重量不超过给定的背包容量的前提下，这些物品的总价值($total\_value​$)达到最大。

这类问题大致可以分为三大类（通过对物品数量的限制进行划分），分别为：[无界背包问题](#unbounded-knapsack), [0-1 背包问题](#0-1-knapsack), [有界背包问题](#bounded-knapsack).

### Unbounded knapsack

---

#### Problem description

由于无界背包对于选择物品方面没有太多的限制，那么仅仅规定选择的数量$x_i$必须大于等于０即可，因此无界背包问题的形式化描述如下：
$$
\begin {aligned}
&{\mathop{argmax}_{x_i}} {\sum_{i=1}^n} value_i \times x_i \\
&\text{subject to } {\sum_{i=1}^n} {weight_i \times x_i}  \leq {volumn}  \text{ and }  x_i \geq 0  \text{ and } weight_i > 0
 \end{aligned}
$$

#### Algorithm description and certification

设$dp[v]$为背包容量为$v$时，整个背包所能存放物品的最大价值。那么我们可以有如下算法：

```cpp
dp[0].value = 0; // initialize
dp[0].goods = -1; // we didn't put any goods in
for (v = 1; v <= volumn; v++)
    dp[v].value = dp[v - 1].value; // in case of we can't put any other goods in
	dp[v].goods = dp[v - 1].goods; // the last goods
	for (i = 1; i <= n; i++)
        if (v - weight[i] >= 0)
        	dp[v] = max(dp[v], dp[v - weight[i]] + value[i]); // update the optimal value
			dp[v].goods = i; // we put the goods i into the backpack

// this is the max, if you want to know what you have put into you backpack
// you need to do backtrace.
return dp[volumn]; 
```

1. 当$v=0$时，所能容纳的最大价值$dp[0] =0$, 且此时没有任何物品被放入到背包当中；

2. 当$v=k$时，背包所能容纳的最大价值$dp[k] \geq dp[k-1]$。此外，由于背包的容量增大了$1$，还有机会将背包当中的物品换成另外一件更高价值的物品，因此我们对$n$件物品进行轮寻，并且将能够价值最大化的物品加入到背包当中。也因此，其递推公式为：
   $$
   \begin {aligned}
   &dp[0] = 0\\
   &dp[k]  = \mathop {max}_{weight_i \leq k}(dp[k-1], dp[k-weight_i]+value_i)
   \end {aligned}
   $$

3. 算法的时间复杂度为：$O(n \times volumn)$；当然，我们也可以用$volumn, weight_i$除以他们的最大公约数，从而使得算法更加快速。

#### Code

```cpp
  struct Goods {
    int32_t goods_id;
    uint32_t price;
    uint32_t weight;
  };
  
  void SolveUnboundedKnapsack() {
    // dp[w] means the max_value we can get, if capacity = w
    m_optimal_comb.clear();
    std::vector<Node> dp(m_capacity + 1);
    for (uint32_t w = 1; w <= m_capacity; w++) {
      // Algorithm description:
      //  dp[w] = max{dp[w-1], max_i(dp[w-w_i] + p_i)}
      dp[w] = dp[w - 1];  // important initialization
      for (uint32_t index = 0; index < m_goods.size(); index++) {
        Goods& goods = m_goods[index];
        // we can choose this goods
        if (w >= goods.weight) {
          uint32_t value = dp[w - goods.weight].max_value + goods.price;
          if (dp[w].max_value < value) {  // this choice is better
            // update the parent, max_value, goods_id
            dp[w].goods_id = goods.goods_id;  // we choose this goods
            dp[w].max_value = value;          // update the max_value we can get
            dp[w].parent = &dp[w - goods.weight];  // record it's parent
          }
        }
      }
    }

    // Backtrace to get the optimal combination
    Node* node = &dp[m_capacity];
    m_max_value = node->max_value;
    while (node->parent != nullptr) {
      m_optimal_comb.push_back(m_goods[node->goods_id]);
      node = node->parent;
    }
  }
```

此处的code与伪代码有一些不一样，主要区别在于：伪代码里面并没有保存当前最优背包策略的父节点，即最优子背包（因为我们已经记录了当前选择的最优物品，那么我们很自然的便可以得到最优子背包）。

#### Reference

[Wikipedia](https://en.wikipedia.org/wiki/Knapsack_problem)

### 0-1 knapsack

------

#### Problem description

对于0-1背包问题，其是有界背包问题的一种特殊形式，其规定每种物品**最多选择一次**，$x_i \geq 0 \text {   }\and x_i \leq 1$，因此0-1背包问题的形式化描述如下：
$$
\begin {aligned}
&{\mathop{argmax}_{x_i}} {\sum_{i=1}^n} value_i \times x_i \\
&\text{subject to } {\sum_{i=1}^n} {weight_i \times x_i}  \leq {volumn}  \text{ and }  1 \geq x_i \geq 0  \text{ and } weight_i > 0
 \end{aligned}
$$

#### Algorithm description and certification

设$dp[v][i]$为背包容量为$v$时，若我们仅仅考虑在物品$\{1, 2, 3...i\}$之间选择，整个背包所能存放物品的最大价值。那么我们可以有如下算法：

```cpp
dp[0][0 : n+1] = 0;
dp[0 : volumn+1][0] = 0;
for (v = 1; v <= volumn; v++) // loop from volumn = 1
    for (i = 1; i <= n; i++) // loop from good = 1
    	// we can only choose we put this goods(i) into our backpack or not(at most once)
        dp[v][i] = dp[v][i-1];
        if (v >= weight_i)
            dp[v][i] = max(dp[v][i], dp[v-weight_i][i-1] + value_i);
```

1. 当$i=0$或者$v=0$的时候，最大价值为０（对应着初始化的过程）；

2. 对于其他的情况，我们有如下的递推方程：
   $$
   \begin {aligned}
   dp[v][i]=max(dp[v][i-1], dp[v-weight_i][i-1]+value_i)
   \end {aligned}
   $$
   上式说明当背包的容量确定时，若增加一种可以选择的物品，为了使得背包中的物品价值最大化，我们唯一能做的只是选择这个物品一次，或者不选择这个物品；

3. 与无界背包问题一样，整个算法的时间复杂度为：$O(n \times volumn)$；当然，我们也可以用$volumn, weight_i$除以他们的最大公约数，从而使得算法更加快速。

#### Code

```cpp
  // Solve the 0/1 knapsack problem
  void SolveZeroOneKnapsack() {
    // dp[w][i]: means the max value we can get on the constrain of capacity = w
    //           only use the front i kinds of goods
    // So the tansfer equation is :
    //    dp[w][i] = max{dp[w - w_i][i - 1] + v_i, dp[w][i - 1]}
    //             1. we will use the ith goods;
    //             2. we won't use the ith goods;
    m_optimal_comb.clear();
    std::vector<Node> tmp(m_goods.size() + 1);
    std::vector<std::vector<Node> > dp(m_capacity + 1, tmp);
    for (uint32_t w = 1; w <= m_capacity; w++) {
      for (uint32_t i = 1; i <= m_goods.size(); i++) {
        dp[w][i] = dp[w][i - 1];
        uint32_t w_i = m_goods[i - 1].weight;
        uint32_t v_i = m_goods[i - 1].price;
        if (w >= w_i) {  // the weight is enough
          uint32_t value = dp[w - w_i][i - 1].max_value + v_i;
          if (dp[w][i].max_value < value) {
            dp[w][i].goods_id = m_goods[i - 1].goods_id;
            dp[w][i].parent = &dp[w - w_i][i - 1];
            dp[w][i].max_value = value;
          }
        }
      }
    }

    // Backtrace to get the goods we choose
    Node* node = &dp[m_capacity][m_goods.size()];
    m_max_value = node->max_value;
    while (node->parent != nullptr) {
      m_optimal_comb.push_back(m_goods[node->goods_id]);
      node = node->parent;
    }
  }
```

#### Reference

[Wikipedia](https://en.wikipedia.org/wiki/Knapsack_problem)

### Bounded knapsack

------

#### Problem description

对于有界背包问题，我们可以加上对于选择物品$i$次数的约束，$x_i \geq 0 \text {   }\and x_i \leq C_i$，因此无界背包问题的形式化描述如下：
$$
\begin {aligned}
&{\mathop{argmax}_{x_i}} {\sum_{i=1}^n} value_i \times x_i \\
&\text{subject to } {\sum_{i=1}^n} {weight_i \times x_i}  \leq {volumn}  \text{ and }  C_i \geq x_i \geq 0  \text{ and } weight_i > 0
 \end{aligned}
$$

#### Algorithm description and certification

设$dp[v][i]$为背包容量为$v$时，若我们仅仅考虑在物品$\{1, 2, 3...i\}$之间选择，整个背包所能存放物品的最大价值。那么我们可以有如下算法：

```cpp
dp[0][0 : n+1] = 0;
dp[0 : volumn+1][0] = 0;
for (v = 1; v <= volumn; v++) // loop from volumn = 1
    for (i = 1; i <= n; i++)  // loop from good = 1
    	// we can choose at most C[i] times for goods[i] into our backpack
        dp[v][i] = dp[v][i-1];
        for (c = 1; c <= C[i]; c++)
			if (v >= c * weight_i)
            	dp[v][i] = max(dp[v][i], dp[v-c*weight_i][i-1] + c*value_i);
			else
                break;
return dp[volumn][n];
```

#### Code

```cpp
  // Solve the bounded knapsack problem
  void SolveBoundedKnapsack() {
    // dp[w][i]: means the max value we can get on the constrain of capacity = w
    //           only use the front i kinds of goods
    // So the tansfer equation is :
    //    dp[w][i] = max{dp[w - k*w_i][i - 1] + k*v_i, dp[w][i - 1]}
    //             1. we will use the ith goods for k times, k <= count_i;
    //             2. we won't use the ith goods;
    m_optimal_comb.clear();
    std::vector<Node> tmp(m_goods.size() + 1);
    std::vector<std::vector<Node> > dp(m_capacity + 1, tmp);
    for (uint32_t w = 1; w <= m_capacity; w++) {
      for (uint32_t i = 1; i <= m_goods.size(); i++) {
        dp[w][i] = dp[w][i - 1];
        uint32_t w_i = m_goods[i - 1].weight;
        uint32_t v_i = m_goods[i - 1].price;
        uint32_t c_i = m_goods[i - 1].count;
        for (uint32_t c = 1; c <= c_i; c++) {
          if (w >= c * w_i) {  // the weight is enough
            uint32_t value = dp[w - c * w_i][i - 1].max_value + c * v_i;
            if (dp[w][i].max_value < value) {
              dp[w][i].goods_id = m_goods[i - 1].goods_id;
              dp[w][i].parent = &dp[w - w_i][i - 1];
              dp[w][i].max_value = value;
              dp[w][i].count = c;  // we choose this element c times
            } else {
              break;
            }
          } else {
            break;
          }
        }
      }
    }

    // Backtrace to get the goods we choose
    Node* node = &dp[m_capacity][m_goods.size()];
    m_max_value = node->max_value;
    while (node->parent != nullptr) {
      for (int32_t i = 0; i < node->count; i++) {
        m_optimal_comb.push_back(m_goods[node->goods_id]);
      }
      node = node->parent;
    }
  }
```

Below is  a test case of the before mentioned three knapsack problem.

```shell
Test case 2:
Random input of goods:
    goods_id	weight	price	count           0	3	4	2
    goods_id	weight	price	count           1	4	5	2
    goods_id	weight	price	count           2	2	3	2
Capacity: 10

Optimal combination of unbounded knapsack:
    goods_id	weight	price	count           2	2	3	2
    goods_id	weight	price	count           2	2	3	2
    goods_id	weight	price	count           2	2	3	2
    goods_id	weight	price	count           2	2	3	2
    goods_id	weight	price	count           2	2	3	2
Max value of unbounded knapsack: 15

Optimal combination of 0/1 knapsack:
    goods_id	weight	price	count           2	2	3	2
    goods_id	weight	price	count           1	4	5	2
    goods_id	weight	price	count           0	3	4	2
Max value of 0/1 knapsack: 12

Optimal combination of bounded knapsack:
    goods_id	weight	price	count           1	4	5	2
    goods_id	weight	price	count           0	3	4	2
    goods_id	weight	price	count           0	3	4	2
Max value of bounded knapsack: 13
```

#### Reference

[Wikipedia](https://en.wikipedia.org/wiki/Knapsack_problem)