#include "heap.h"

class Node {
 public:
  int32_t val;

  Node() : val(0) {}
  Node(int32_t x) : val(x) {}
  bool operator<(const Node& other) const { return val < other.val; }
};

int main() {
  // Initialize the heap
  std::vector<Node> data;
  for (uint32_t i = 0; i < 10; i++) {
    data.push_back(Node(10 - i));
  }
  std::function<bool(Node, Node)> cmp = [](Node x, Node y) { return x < y; };
  Heap<Node> test(data.begin(), data.end(), cmp);
  test.Serilize("heap_vis_init");

  // Test insert
  test.Insert(Node(0));
  test.Serilize("heap_vis_insert");

  // Test delete
  test.Delete();
  test.Serilize("heap_vis_delete");
  return 0;
}
