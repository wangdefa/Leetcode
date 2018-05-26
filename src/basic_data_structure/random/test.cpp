#include <iostream>
#include "shuffle.h"

int main(void) {
  std::vector<uint32_t> src{1, 2, 3, 4, 5, 6, 7, 8, 9};
  Shuffle(&src);
  for (auto data : src) {
    std::cout << data << "\t";
  }
  std::cout << std::endl;
  return 0;
}