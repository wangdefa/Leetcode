#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>
#include "assert.h"
#include "stdint.h"

void Serilize(std::string infor, const std::vector<uint32_t>& vec) {
  std::cout << infor << ":\t";
  for (const uint32_t& data : vec) {
    std::cout << data << "\t";
  }
  std::cout << std::endl;
}

int main() {
  // In c++, we can use heap to realize the priority queue.
  // input
  std::vector<uint32_t> vec{9, 8, 7, 6, 5, 4, 3, 2, 1};
  Serilize("The initial vector", vec);
  auto cmp = [](uint32_t x, uint32_t y) { return x > y; };
  std::make_heap(vec.begin(), vec.end(), cmp);
  Serilize("The vector after make_heap", vec);
  std::pop_heap(vec.begin(), vec.end(), cmp);
  std::pop_heap(vec.begin(), vec.end() - 1, cmp);
  Serilize("The vector after pop_heap", vec);
  vec.pop_back();
  vec.pop_back();
  std::sort_heap(vec.begin(), vec.end(), cmp);  // not stable
  Serilize("The vector after sort_heap", vec);
  return 0;
}
