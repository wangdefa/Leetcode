#include <iostream>
#include <string>
#include <vector>
#include "stdint.h"

bool IsAnagrams(std::string s1, std::string s2) {
  // Special case
  if (s1.size() != s2.size()) {
    return false;
  }

  // Using hash map to count the character
  const uint32_t kCharSize = 256;
  int32_t char_count[kCharSize] = {0};
  for (uint32_t i = 0; i < s1.size(); i++) {
    char_count[s1[i]]++;
    char_count[s2[i]]--;
  }
  // Judge the two string have the same character or not
  for (uint32_t i = 0; i < kCharSize; i++) {
    if (char_count[i] != 0) {
      return false;
    }
  }
  return true;
}

bool CompareStr(std::string s1, std::string s2) {
  // Using hash map to count the character
  const uint32_t kCharSize = 256;
  int32_t char_count[kCharSize] = {0};
  for (uint32_t i = 0; i < s1.size(); i++) {
    char_count[s1[i]]++;
  }
  for (uint32_t i = 0; i < s2.size(); i++) {
    char_count[s2[i]]--;
  }
  // Judge the two string have the same character or not
  for (uint32_t i = 0; i < kCharSize; i++) {
    if (char_count[i] < 0) {
      return false;
    }
  }
  return true;
}

// Method 1:
std::vector<std::vector<std::string>> GroupAnagrams(
    std::vector<std::string> src) {
  std::vector<std::vector<std::string>> result;
  // special case
  if (src.size() < 1) {
    return result;
  }

  std::vector<std::string> vec(1, src.front());
  result.push_back(vec);
  for (uint32_t i = 1; i < src.size(); i++) {
    bool i_merged = false;
    // Loop all the group until i have found the group
    for (uint32_t j = 0; j < result.size(); j++) {
      if (IsAnagrams(src.at(i), result.at(j).front())) {
        result[j].push_back(src.at(i));
        i_merged = true;
        break;
      }
    }
    // if i didn't find group, create his own group
    if (!i_merged) {
      std::vector<std::string> vec(1, src.at(i));
      result.push_back(vec);
    }
  }
  return result;
}
int main(void) {
  // is anagrams
  std::cout << "1.Test is anagrams." << std::endl;
  std::string s1 = "abcd";
  std::string s2 = "dcba";
  std::cout << s1 << " and " << s2 << " is anagrams ?" << std::endl;
  std::cout << (IsAnagrams(s1, s2) ? "Yes" : "No") << std::endl;

  // compare string
  std::cout << "\n\n2.Test compare string." << std::endl;
  s1 = "abcd";
  s2 = "dcba";
  std::cout << s1 << " contains " << s2 << " ?" << std::endl;
  std::cout << (CompareStr(s1, s2) ? "Yes" : "No") << std::endl;

  s1 = "abcdd";
  s2 = "dcbaa";
  std::cout << s1 << " contains " << s2 << " ?" << std::endl;
  std::cout << (CompareStr(s1, s2) ? "Yes" : "No") << std::endl;

  s1 = "abcd";
  s2 = "dcb";
  std::cout << s1 << " contains " << s2 << " ?" << std::endl;
  std::cout << (CompareStr(s1, s2) ? "Yes" : "No") << std::endl;

  // group anagrams
  auto serilize = [](std::vector<std::vector<std::string>> res) {
    for (auto vec : res) {
      std::cout << "New group: ";
      for (auto str : vec) {
        std::cout << str << "\t";
      }
      std::cout << std::endl;
    }
  };
  std::cout << "\n\n3.Test group anagrams." << std::endl;
  std::vector<std::string> src = {"eat", "tea", "tan", "ate", "nat", "bat"};
  serilize(GroupAnagrams(src));
}