#include <stdint.h>
#include <time.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include "assert.h"
#include "stdlib.h"

template <class T>
void Serilize(std::string desc, std::vector<T> vec) {
  std::cout << desc << "\t";
  for (auto data : vec) {
    std::cout << data << "\t";
  }
  std::cout << std::endl;
}

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
class Node {
 public:
  std::string val;
  double weight;

  Node() {}
  Node(double w, std::string v) : weight(w), val(v) {}

  bool operator<(const Node &src) { return this->weight > src.weight; }
  friend std::ostream &operator<<(std::ostream &out, const Node &ref) {
    out << ref.val << "(" << ref.weight << ")";
    return out;
  }
};
class ReservoiorSampling {
 private:
  std::vector<Node> m_data;  // used to save all the value and weight
  std::vector<Node> m_res;
  uint32_t m_k;  // the number of samples

 public:
  ReservoiorSampling() {}
  ReservoiorSampling(const std::vector<Node> &data, const uint32_t &k) {
    m_data = data;
    m_k = k;
  }

  // un-weighted sampling algorithm
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
    m_res.clear();
    m_res.resize(m_k);
    assert(m_k < m_data.size() && "Invalid sampling problem here.");

    // Initialize
    for (uint32_t i = 0; i < m_k; i++) {
      m_res[i] = m_data[i];
    }

    // Load data from the disk and update the Node(data) in the pool
    for (uint32_t i = m_k; i < m_data.size(); i++) {
      uint32_t r = rand() % (i + 1);
      if (r < m_k) {
        m_res[r] = m_data[i];
      }
    }
  }

  void AlgorithmAChao() {
    // AlgorithmAChao:
    //  it is a sampling algorithm which takes the weight into consideration
  }

  // weighted sampling algorithm
  void AlgorithmARes() {
    // AlgorithmARes:
    //  it is a sampling algorithm which takes the weight into consideration
    // Initialize
    m_res.clear();
    assert(m_k < m_data.size() && "Invalid sampling problem here.");
    for (uint32_t index = 0; index < m_k; index++) {
      double r_i =
          pow(rand() / double(RAND_MAX), 1 / double(m_data[index].weight));
      m_res.push_back(Node(r_i, m_data[index].val));
    }
    std::make_heap(m_res.begin(), m_res.end());

    // Update
    for (uint32_t index = m_k; index < m_data.size(); index++) {
      double r_i =
          pow(rand() / double(RAND_MAX), 1 / double(m_data[index].weight));
      if (r_i > m_res.front().weight) {
        std::pop_heap(m_res.begin(), m_res.end());  // delete operation of heap
        m_res.pop_back();  // we use the vector to delete
        m_res.push_back(Node(r_i, m_data[index].val));
        std::push_heap(m_res.begin(), m_res.end());
      }
    }
  }

  void SerilizeResult(std::string desc) {
    std::cout << desc;
    for (auto data : m_res) {
      std::cout << data.val << "(" << data.weight << ")"
                << "\t";
    }
    std::cout << std::endl;
  }

  // Count the result after do the reservoior sampling
  void CountResult(uint32_t *counter) {
    for (auto res : m_res) {
      if (res.val == "a") {
        *(counter + 0) += 1;
      } else if (res.val == "b") {
        *(counter + 1) += 1;
      } else if (res.val == "c") {
        *(counter + 2) += 1;
      } else if (res.val == "d") {
        *(counter + 3) += 1;
      } else if (res.val == "e") {
        *(counter + 4) += 1;
      } else if (res.val == "f") {
        *(counter + 5) += 1;
      } else if (res.val == "g") {
        *(counter + 6) += 1;
      } else if (res.val == "h") {
        *(counter + 7) += 1;
      } else if (res.val == "i") {
        *(counter + 8) += 1;
      } else if (res.val == "j") {
        *(counter + 9) += 1;
      }
    }
  }

  void TestReservoiorSampling() {
    // Define the random sampling problem
    std::vector<Node> data;
    const uint32_t kEntryCount = 10;
    const uint32_t kSampleCount = 5;
    std::vector<std::string> src1{"a", "b", "c", "d", "e",
                                  "f", "g", "h", "i", "j"};
    for (uint32_t i = 0; i < kEntryCount; i++) {
      Node node(rand() % 10 + 1, src1[i]);
      data.push_back(node);
    }
    std::cout << "Input entry and it's weight:" << std::endl;
    Serilize("Entry & weight", data);
    ReservoiorSampling rs(data, kSampleCount);
    const uint32_t num_test_case = 100000 / 5;

    // Test the algorithm R
    uint32_t counter_r[10] = {0};
    for (uint32_t i = 0; i < num_test_case; i++) {
      rs.AlgorithmR();
      rs.CountResult(counter_r);
      // rs.Serilize("Res of Algorithm R: ");
    }
    std::cout << "AlgorithmR"
              << "\t";
    for (auto count : counter_r) {
      std::cout << count / double(5 * num_test_case) << "\t";
    }
    std::cout << std::endl;

    // Test the algorithm A-Res
    uint32_t counter_ares[10] = {0};
    for (uint32_t i = 0; i < num_test_case; i++) {
      rs.AlgorithmARes();
      rs.CountResult(counter_ares);
    }
    std::cout << "AlgorithmA-Res"
              << "\t";
    for (auto count : counter_ares) {
      std::cout << count / double(5 * num_test_case) << "\t";
    }
    std::cout << std::endl;
  }
};