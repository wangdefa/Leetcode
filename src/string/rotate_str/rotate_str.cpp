#include <algorithm>
#include <iostream>
#include <string>
#include "stdint.h"

void Rotate(std::string &s, int32_t i, int32_t j) {
  // rotate the s[i:j)
  j--;
  for (; i < j; ++i, --j) {
    char tmp = s[i];
    s[i] = s[j];
    s[j] = tmp;
  }
}
void RotateString(std::string &s, uint32_t offset) {
  if (s.empty()) {
    return;
  }
  uint32_t sz = s.size();
  offset = offset % sz;
  Rotate(s, 0, sz - offset);
  Rotate(s, sz - offset, sz);
  Rotate(s, 0, sz);
}
void RotateStringByWord(std::string &s) {
  // 1. reverse each word
  int32_t beg = -1;
  int32_t end = -1;
  uint32_t sz = s.size();
  char space = ' ';
  for (int32_t i = 0; i < sz; i++) {
    // 1.1 find the beginning of a word
    if (s[i] != space && beg == -1) {
      beg = i;
      continue;
    }
    // 1.2 find the end and reverse
    if ((s[i] == space || i == sz - 1) && beg != -1) {
      end = i;
      Rotate(s, beg, end);
      beg = end = -1;
    }
  }

  // 2. Rotate the whole string
  std::cout << s << std::endl;
  Rotate(s, 0, sz);
  std::cout << s << std::endl;

  // 3. Remove useless space
  uint32_t j = 0;
  for (uint32_t i = 0; i < sz;) {
    // 3.1 remove all the heading space
    if (j == 0 && s[i] == space) {
      i++;
      continue;
    }
    // 3.2 add the valid character
    if (s[i] != space) {
      s[j++] = s[i++];
    }
    // 3.3 Add a space if needed.
    else {
      while (i < sz && s[i] == space) i++;
      if (i == sz) break;  // remove all the tail space
      s[j++] = space;
    }
  }

  // 4. Resize the string
  s.resize(j);
}
bool IsPalindrome(const std::string &s) {
  if (s.empty()) return true;
  uint32_t ptr1 = 0;
  uint32_t ptr2 = s.size() - 1;
  auto IsChar = [](char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
  };
  while (ptr1 < ptr2) {
    while (ptr1 < ptr2 && !IsChar(s[ptr1])) ptr1++;
    while (ptr1 < ptr2 && !IsChar(s[ptr2])) ptr2--;
    if (s[ptr1] == s[ptr2] ||
        std::fabs(s[ptr1] - s[ptr2]) == std::fabs('a' - 'A')) {
      // std::cout << s[ptr1] << "\t" << s[ptr2] << std::endl;
      ptr1++, ptr2--;
    } else {
      return false;
    }
  }
  return true;
}

int32_t ReplaceSpace(std::string &s) {
  // Replace the space with %sp in string s
  // Get the new length of the string
  uint32_t len = s.size();
  uint32_t count = 0;
  char space = ' ';
  for (int32_t i = 0; i < len; i++)
    if (s[i] == space) count++;

  // reallocate the string s
  s.resize(len + 2 * count);

  // replace the space with %sp
  int32_t j = len + 2 * count - 1;
  int32_t i = len - 1;
  for (; i >= 0; i--)
    if (s[i] == space) {
      s[j--] = 'p';
      s[j--] = 's';
      s[j--] = '%';
    } else {
      s[j--] = s[i];
    }
  return len + 2 * count;  // the new length of the string
}

int32_t main(void) {
  std::string s = "abcdefg";
  std::cout << "Original str is: \t" << s << std::endl;
  RotateString(s, 6);
  std::cout << "Rotate str is: \t" << s << std::endl;

  s = "   the  sky is      blue  ";
  RotateStringByWord(s);
  std::cout << s << std::endl;

  s = "A man, a plan, a canal: Panama";
  std::cout << IsPalindrome(s) << std::endl;

  s = "race a car";
  std::cout << IsPalindrome(s) << std::endl;

  s = " b ab ad  ";
  // std::cout << uint32_t(9) - 10 << std::endl;
  std::cout << ReplaceSpace(s) << std::endl;
  std::cout << s << std::endl;
  return 0;
}