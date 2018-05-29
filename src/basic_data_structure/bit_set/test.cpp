#include "bit_set.h"

int main (void)
{
  std::vector<uint32_t> data{9, 8 , 7, 6, 5, 4, 3, 2, 1};
  Sort(&data);
  for (auto d : data)
  {
    std::cout << d << "\t";
  }

  return 0;
}