#include <iostream>
#include <string>
#include <vector>
#include "assert.h"
#include "stdint.h"

class Kmp {
 private:
  std::string m_parttern;
  std::string m_text;
  std::vector<int32_t> m_next;

 public:
  Kmp(std::string parttern, std::string text) {
    m_parttern = parttern;
    m_text = text;
  }

  void CreateNext() {
    // next[i]: if we come across the mis-compare at the index i in parttern
    //          string, this is the next pos to compare in parttern.
    //          if next[i] = -1, we should move the text a step;
    assert(m_parttern.size() != 0 && "m_parttern is empty.");
    // create the next array
    m_next.clear();
    m_next.resize(m_parttern.size());
    m_next[0] = -1;  // the first element
    for (int32_t i = 1; i < m_next.size(); i++) {
      int32_t j = i - 1;
      while (m_next[j] != -1) {
        if (m_parttern[i - 1] == m_parttern[m_next[j]]) {
          m_next[i] = m_next[j] + 1;
          break;  // we have get the res for this pos
        } else {
          j = m_next[j];
        }
      }
      // if m_next[j] = -1, it means we can use the initalized value
    }

    // print
    std::cout << "The input parttern string and it's next array: " << m_parttern
              << std::endl;
    for (auto i : m_next) {
      std::cout << i << "\t";
    }
    std::cout << std::endl;
  }

  int32_t Find() {
    // return the first emerge index of the parttern string in text
    // if we can't find, return -1;
    int32_t i = 0;
    int32_t j = 0;
    while (i < m_text.size() && j < int32_t(m_parttern.size())) {
      if (j == -1 || m_text[i] == m_parttern[j]) {
        i++, j++;
        // std::cout << i << "\t" << j << std::endl;
      } else {
        j = m_next[j];
        // std::cout << i << "\t" << j << std::endl;
      }
    }

    // succeed in finding the result
    // std::cout << i << "\t" << j << std::endl;
    // std::cout << (1 < m_text.size()) << "\t" << (j < m_parttern.size())
    // << std::endl;
    if (j == m_parttern.size()) {
      return i - j;
    } else {
      return -1;
    }
  }
};