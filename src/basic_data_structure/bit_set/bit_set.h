#include <bitset>
#include <vector>
#include <iostream>

void Sort(std::vector<uint32_t> *src) {
  // Create the bit set data structure
  const uint32_t N = 10;
  std::bitset<N> flag;
  for (std::size_t i = 0; i < src->size(); i++)
  {
    flag.set(i);
  }
  
  // Get the sorted result
  uint32_t cur_index = 0;
  for (std::size_t i = 0; i < N; i++)
  {
    if (flag.test(i))
    {
      (*src)[cur_index++] = i;
    }
  }
}
