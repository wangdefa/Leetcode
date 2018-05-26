#include <iomanip>
#include <iostream>
#include <stack>
#include "assert.h"
#include "stdint.h"

int main() {
  // input
  std::stack<uint32_t> q;
  for (uint32_t i = 0; i < 10; i++) {
    q.push(i);  // insert element in the end of the queue
  }

  std::cout << q.top()
            << std::endl;  // get the element in the front of the queue
  q.pop();                 // pop out the element in the front of the queue
  std::cout << q.top() << std::endl;
  q.pop();
  std::cout << q.size() << std::endl;
  std::cout << q.empty() << std::endl;

  std::stack<uint32_t> p(q);
  std::cout << p.top()
            << std::endl;  // get the element in the front of the pueue
  p.pop();                 // pop out the element in the front of the pueue
  std::cout << p.top() << std::endl;
  p.pop();
  std::cout << p.size() << std::endl;
  std::cout << p.empty() << std::endl;
  return 0;
}
