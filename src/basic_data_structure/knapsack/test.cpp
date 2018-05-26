#include <stdlib.h>
#include "knapsack.h"

int main() {
  // Testcase  1:
  // input of repeated backpack problem
  srand((unsigned)time(NULL));
  std::vector<Goods> goods;
  uint32_t capacity = 23;
  const uint32_t goods_num = 5;
  for (uint32_t i = 0; i < goods_num; i++) {
    // price, weight, goods_id
    uint32_t weight = rand() % 20 + 1;
    goods.push_back(Goods(weight + rand() % 20, weight + 2, i));
  }
  Knapsack knapsack(goods, capacity);

  // Check the input and output
  std::cout << "Test case 1:" << std::endl;
  std::cout << "Random input of goods:" << std::endl;
  Serialize(goods);
  std::cout << "Capacity: " << capacity << std::endl;
  std::cout << "Optimal combination of unbounded knapsack:" << std::endl;
  knapsack.SolveUnboundedKnapsack();
  Serialize(knapsack.m_optimal_comb);
  std::cout << "Max value of unbounded knapsack: " << knapsack.m_max_value
            << std::endl;
  std::cout << "Optimal combination of 0/1 knapsack:" << std::endl;
  knapsack.SolveZeroOneKnapsack();
  Serialize(knapsack.m_optimal_comb);
  std::cout << "Max value of 0/1 knapsack: " << knapsack.m_max_value
            << std::endl;

  //   Test case 2:
  goods.clear();
  goods.push_back(Goods(4, 3, 0));
  goods.push_back(Goods(5, 4, 1));
  goods.push_back(Goods(3, 2, 2));
  capacity = 7;
  Knapsack knapsack1(goods, capacity);

  // Check the input and output
  std::cout << std::endl << "Test case 2:" << std::endl;
  std::cout << "Random input of goods:" << std::endl;
  Serialize(goods);
  std::cout << "Capacity: " << capacity << std::endl;
  std::cout << "Optimal combination of unbounded knapsack:" << std::endl;
  knapsack1.SolveUnboundedKnapsack();
  Serialize(knapsack1.m_optimal_comb);
  std::cout << "Max value of unbounded knapsack: " << knapsack1.m_max_value
            << std::endl;
  std::cout << "Optimal combination of 0/1 knapsack:" << std::endl;
  knapsack1.SolveZeroOneKnapsack();
  Serialize(knapsack1.m_optimal_comb);
  std::cout << "Max value of 0/1 knapsack: " << knapsack1.m_max_value
            << std::endl;
  return 0;
}
