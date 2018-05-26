#include <cmath>
#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>
#include "assert.h"
#include "stdint.h"

class SearchRange {
 public:
  std::vector<uint32_t> m_data;

 public:
  SearchRange() {}
  SearchRange(std::vector<uint32_t> &data) : m_data(data) {}

  // Explanation:
  //  1. Result will be in the range (i, j];
  //  2. if m_data[mid] < target, i = mid can guarantee the condition 1;
  //  3. if m_data[mid] >= target, j = mid can guarantee the condition 1;
  //  4. j = i + 1, when the loop is finished
  int32_t LowerBound(uint32_t target) {
    // Function:
    //      min index;
    //      s.t. m_data[index] >= target
    if (m_data.empty()) {
      return -1;
    }

    int32_t i = -1;
    int32_t j = m_data.size();
    while (i + 1 < j)  // or it can be dead lock
    {
      int32_t mid = i + ((j - i) >> 1);
      if (m_data[mid] < target) {
        i = mid;
      } else {
        j = mid;
      }
    }

    return j;
  }

  // Explanation:
  //  1. Result will be in the range [i, j);
  //  2. if m_data[mid] > target, j = mid can guarantee the condition 1;
  //  3. if m_data[mid] <= target, i = mid can guarantee the condition 1;
  //  4. j = i + 1, when the loop is finished
  int32_t UpperBound(uint32_t target) {
    // Explanation:
    //      max index;
    //      s.t. m_data[index] <= target
    if (m_data.empty()) {
      return -1;
    }

    int32_t i = -1;
    int32_t j = m_data.size();
    while (i + 1 < j) {
      int32_t mid = i + ((j - i) >> 1);
      if (m_data[mid] > target) {
        j = mid;
      } else {
        i = mid;
      }
    }

    return i;
  }
};

class LongestLine {
 public:
  std::vector<float> m_data;
  uint32_t m_k;  // k segement

 public:
  LongestLine() {}
  LongestLine(std::vector<float> &data, uint32_t k) : m_data(data), m_k(k) {}

  // Explanation:
  //  1. Result will be in the range [i, j);
  //  2. if m_data[mid] met the constraint, i = mid can guarantee the condition
  //  1;
  //  3. if m_data[mid] don't met the constraint, j = mid can guarantee the
  //  condition 1;
  //  4. j <= i + 0.001, when the loop is finished
  float LongestSegement() {
    // max i;
    //  s.t. sum_x(floor(m_data[x] / i)) >= m_k
    float i = 0.0;
    float j = 0.0;
    for (auto length : m_data) {
      assert(length >= 0.0);
      j = j > length ? j : length;
    }

    // the constrain is: sum_x(floor(m_data[x] / i)) >= m_k
    auto MetConstraint = [](const std::vector<float> &data, const uint32_t &k,
                            const float &i) {
      uint32_t max_segement = 0;
      for (auto length : data) {
        max_segement += floor(length / i);
      }
      return max_segement >= k;
    };
    while (i + 0.001 < j) {
      float mid = i + (j - i) / 2;
      if (MetConstraint(m_data, m_k, mid)) {
        i = mid;
      } else {
        j = mid;
      }
    }
    return round(i * 100) / 100;
  }
};