#include <iostream>
#include <string>
#include "stdint.h"

// 这两个都比较简单，不再进行描述

uint32_t LastWordLength(std::string str) {
  uint32_t len = 0;
  for (uint32_t i = 0; i < str.size();) {
    // find the first valid character
    while (i < str.size() && str[i] == ' ') i++;
    uint32_t first = i;

    // find the second valid character
    while (i < str.size() && str[i] != ' ') i++;
    len = (i - first == 0) ? len : (i - first);
  }
  return len;
}

std::string CountAndSay(uint32_t n) {
  // special case
  if (n == 1) {
    return "1";
  }

  // deduce
  std::string last_res = CountAndSay(n - 1);
  uint32_t first = 0;
  uint32_t second = 1;
  std::string res = "";
  while (first < last_res.size()) {
    while (second < last_res.size() && last_res[second] == last_res[first])
      second++;
    res += std::to_string(second - first) + last_res[first];
    first = second;
  }
  return res;
}