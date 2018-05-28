#include <iostream>
#include "shuffle.h"

int main(void) {
  std::vector<uint32_t> src{1, 2, 3, 4, 5, 6, 7, 8, 9};
  Shuffle(&src);
  for (auto data : src) {
    std::cout << data << "\t";
  }
  std::cout << std::endl;

  //
  std::vector<Node> data;
  std::vector<uint32_t> src1{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
  for (uint32_t i = 0; i < 10; i++) {
    Node node;
    node.val = src1[i];
    node.weight = rand() % 20;
    data.push_back(node);
  }
  ReservoiorSampling rs(data, 3);
  rs.AlgorithmR();
  rs.Serilize();

  return 0;
}