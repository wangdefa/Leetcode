#include <iomanip>
#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include "assert.h"
#include "stdint.h"

// used to serilize the vector
template <class T>
void Serialize(std::vector<T> vec) {
  for (auto data : vec) {
    std::cout << data << std::endl;
  }
}

// Knapsack problem
// Description: https://en.wikipedia.org/wiki/Knapsack_problem
struct Node {
  int32_t goods_id;
  uint32_t count;
  Node* parent;
  uint32_t max_value;  // the max value we can get at the present node
  Node() {
    goods_id = -1;     // -1 means we didn't add any other goods here
    parent = nullptr;  // nullptr means it has no parents
    max_value = 0;
    count = 0;
  }
};

struct Goods {
  int32_t goods_id;
  uint32_t price;
  uint32_t weight;
  uint32_t count;
  Goods(uint32_t p, uint32_t w, uint32_t g, uint32_t c = 0) {
    price = p;     // the price of the goods
    weight = w;    // the
    goods_id = g;  // invalid goods
    count = c;
  }
  friend std::ostream& operator<<(std::ostream& out, Goods& obj) {
    std::cout << std::setw(12) << "goods_id"
              << "\t"
              << "weight"
              << "\t"
              << "price"
              << "\t"
              << "count";
    std::cout << std::setw(12) << obj.goods_id << "\t" << obj.weight << "\t"
              << obj.price << "\t" << obj.count;
  }
};

class Knapsack {
 private:
  std::vector<Goods> m_goods;  // means the overall goods we can choose
  uint32_t m_capacity;         // the capacity of the package

 public:
  std::vector<Goods> m_optimal_comb;  // the combination of the goods
  uint32_t m_max_value;               // the max value we can get

 public:
  // Constructor
  Knapsack(const std::vector<Goods>& goods, const uint32_t& capacity) {
    m_goods = goods;
    m_capacity = capacity;
  }

  // Solve the unbounded knapsack problem
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
};
