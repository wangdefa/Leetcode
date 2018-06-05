
#include <string>
#include "shuffle.h"

int main(void) {
  // Set the random key
  srand((unsigned)time(NULL));

  // Test the shuffle algorithm
  std::vector<uint32_t> src{1, 2, 3, 4, 5, 6, 7, 8, 9};
  Shuffle(&src);
  std::cout << "Res of the shuffle algorithm:" << std::endl;
  for (auto data : src) {
    std::cout << data << "\t";
  }
  std::cout << std::endl;

  ReservoiorSampling test;
  test.TestReservoiorSampling();
  return 0;
}