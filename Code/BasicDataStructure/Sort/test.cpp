#include <iomanip>
#include <iostream>
#include "sort.h"
#include "stdint.h"

void Serilize(std::vector<uint32_t>& data) {
  std::cout << "vector:\t";
  for (auto d : data) {
    std::cout << d << "\t";
  }
  std::cout << std::endl;
}

int main() {
  // input
  std::vector<uint32_t> vec{9, 8, 7, 6, 5, 1, 2, 3, 4};
  Sort sort(vec);
  // sort.BubbleSort();
  // sort.SelectionSort();
  // sort.QuickSort(5, sort.m_data.size());
  sort.MergeSort(1, sort.m_data.size());
  Serilize(sort.m_data);
  return 0;
}
