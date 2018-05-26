#include "huffman_tree.h"

int main() {
  // Initialize the huffman tree
  std::unordered_map<std::string, uint32_t> input_freq;
  input_freq.insert(std::make_pair("I", 100));
  input_freq.insert(std::make_pair("am", 30));
  input_freq.insert(std::make_pair("a", 50));
  input_freq.insert(std::make_pair("Chinese", 5));
  input_freq.insert(std::make_pair(",", 100));
  input_freq.insert(std::make_pair("how", 20));
  input_freq.insert(std::make_pair("about", 70));
  input_freq.insert(std::make_pair("you", 200));
  input_freq.insert(std::make_pair("!", 50));
  HuffmanTree test(input_freq);
  test.Serilize("huffman_tree");
  return 0;
}
