#include <stdint.h>
#include <time.h>
#include <vector>
#include "assert.h"
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

// Reservoir_sampling:
//  Reference: https://en.wikipedia.org/wiki/Reservoir_sampling
struct Node {
  uint32_t val;
  uint32_t weight;  // we will use this in weighted sampling
};
class ReservoiorSampling {
 private:
  std::vector<Node> m_data;  // used to save all the value and weight
  std::vector<Node> res;
  uint32_t m_k;  // the number of samples

 public:
  ReservoiorSampling(const std::vector<Node> &data, const uint32_t &k) {
    m_data = data;
    m_k = k;
  }
  void AlgorithmR() {
    // AlgorithmR:
    //  it is a sampling algorithm without taking the weight into consideration
    // Proof:
    //  Define the probability of element index (count from 0) i is still in the
    //  pool is p(i);
    //  if (i < m_k)
    //    p(i) = 1 * (m_k / (m_k+1)) * ((m_k+1) / (m_k+2)) *... ((n-1) / n)
    //         = m_k / n
    //  else
    //    p(i) = (m_k / (i+1)) * ((i+1) / (i+2)) *... ((n-1) / n) = m_k / n

    // Special case
    res.clear();
    if (m_k > m_data.size()) {
      assert(false && "Invalid sampling problem here.");
    }

    // Initialize
    for (uint32_t i = 0; i < m_k; i++) {
      res[i] = m_data[i];
    }

    // Load data from the disk and update the Node(data) in the pool
    srand((unsigned)time(NULL));
    for (uint32_t i = m_k; i < m_data.size(); i++) {
      uint32_t r = rand() % (i + 1);
      if (r < m_k) {
        res[r] = m_data[i];
      }
    }
  }

  void AlgorithmAChao() {
    // AlgorithmAChao:
    //  it is a sampling algorithm which takes the weight into consideration
  }
} ；