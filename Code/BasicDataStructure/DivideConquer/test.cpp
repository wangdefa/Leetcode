#include <iomanip>
#include <iostream>
#include "divide_conquer.h"
#include "stdint.h"

void Serilize(std::vector<uint32_t> &data) {
  std::cout << "vector:\t";
  for (auto d : data) {
    std::cout << d << "\t";
  }
  std::cout << std::endl;
}

int main() {
  // input
  std::vector<uint32_t> vec{1, 2, 2, 3, 4, 6, 6, 6, 13, 18};
  SearchRange search_range(vec);
  std::cout << search_range.LowerBound(6) << std::endl;  // 5
  std::cout << search_range.LowerBound(7) << std::endl;  // 8
  std::cout << search_range.UpperBound(6) << std::endl;  // 7
  std::cout << search_range.UpperBound(7) << std::endl;  // 7

  std::vector<float> data{8.02, 7.43, 4.57, 5.39};
  LongestLine longest_line(data, 11);
  std::cout << longest_line.LongestSegement() << std::endl;

  return 0;
}
