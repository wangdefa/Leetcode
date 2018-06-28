#include <algorithm>
#include <iostream>
#include <string>
#include "stdint.h"

std::string LongestPalindromeSubstring(const std::string &s) {
  int32_t beg = 0, end = 0;  // record the (begin, end) index
  uint32_t sz = s.size();    // it is an open domain
  for (int32_t axis = 0; axis < sz * 2 - 1; axis++) {
    int32_t beg_tmp, end_tmp;
    if (axis % 2 == 0) {
      beg_tmp = axis / 2 - 1;
      end_tmp = axis / 2 + 1;
    } else  // axis % 2 == 1
    {
      beg_tmp = axis / 2;
      end_tmp = axis / 2 + 1;
    }
    while (beg_tmp >= 0 && end_tmp < sz && s[beg_tmp] == s[end_tmp]) {
      beg_tmp--, end_tmp++;
    }
    if (end - beg <= end_tmp - beg_tmp) {
      beg = beg_tmp;
      end = end_tmp;
    }
  }
  return s.substr(beg + 1, end - beg - 1);
}

int32_t main(void) {
  std::string s = "babad";
  // std::cout << uint32_t(9) - 10 << std::endl;
  std::cout << LongestPalindromeSubstring(s) << std::endl;

  return 0;
}