#include <iomanip>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include "assert.h"
#include "stdint.h"

int main() {
  // input
  std::unordered_map<uint32_t, std::string> q;
  for (uint32_t i = 0; i < 10; i++) {
    q.insert(std::make_pair(
        i, "hello_" +
               std::to_string(i)));  // insert element in the end of the queue
  }

  std::cout << q[9] << std::endl;  // get the element in the front of the queue
  q.erase(q.find(9));  // pop out the element in the front of the queue
  std::cout << q.size() << std::endl;
  std::cout << q.empty() << std::endl;

  std::unordered_set<std::string> set;
  set.insert("hello");
  set.insert("world");
  if (set.find("hello") != set.end()) {
    std::cout << "we find the hello." << std::endl;
    set.erase(set.find("hello"));
  }
  if (set.find("hello") != set.end()) {
    std::cout << "we find the hello." << std::endl;
  }
  std::cout << set.size() << std::endl;
  return 0;
}
