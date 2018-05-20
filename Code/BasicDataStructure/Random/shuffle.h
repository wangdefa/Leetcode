#include <stdint.h>
#include <time.h>
#include <vector>
#include "stdlib.h"

void Shuffle(std::vector<uint32_t> *src) {
  srand((unsigned)time(NULL));
  const uint32_t sz = src->size();
  for (std::size_t i = 0; i < sz; i++) {
    uint32_t r = rand() % (sz - i);
    uint32_t tmp = (*src)[r];
    (*src)[r] = (*src)[sz - i - 1];
    (*src)[sz - i - 1] = tmp;
  }
}