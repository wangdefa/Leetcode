#include <iostream>
#include <string>
#include "shuffle.h"

void Serilize(std::string desc, std::vector<Node> vec_node) {
	std::cout << desc << std::endl;
	for (auto data : vec_node) {
		std::cout << data.val << "(" << data.weight << ")" << "\t";
	}
	std::cout << std::endl;

}

int main(void) {
  // Set the random key
  srand((unsigned)time(NULL));

  // Test the shuffle algorithm
  std::vector<uint32_t> src{1, 2, 3, 4, 5, 6, 7, 8, 9};
  Shuffle(&src);
  std::cout << "Res of the shuffle algorithm:" << std::endl;
  for (auto data : src) {
    std::cout << data << "\t";
  }
  std::cout << std::endl;

  // Test the random sampling algorithm
  std::vector<Node> data;
  const uint32_t kEntryCount = 10;
  const uint32_t kSampleCount = 5;
  std::vector<std::string> src1{ "a", "b", "c", "d", "e", "f", "g", "h", "i", "j" };
  for (uint32_t i = 0; i < kEntryCount; i++) {
	Node node(rand() % 20, src1[i]);
    data.push_back(node);
  }
  Serilize("Input entry and it's weight:", data);
  ReservoiorSampling rs(data, kSampleCount);
  uint32_t counter_r[10] = { 0 };
  for (uint32_t i = 0; i < 200; i++)
  {
	  rs.AlgorithmR();
	  rs.CountResult(counter_r);
	  //rs.Serilize("Res of Algorithm R: ");
  }  
  for (auto count : counter_r) {
	  std::cout << count << "\t";
  }
  std::cout << std::endl;
  
  uint32_t counter_ares[10] = { 0 };
  for (uint32_t i = 0; i < 200; i++)
  {
	  rs.AlgorithmARes();
	  rs.CountResult(counter_ares);
	  //rs.Serilize("Res of Algorithm A-Res: ");
  }  
  for (auto count : counter_ares) {
	  std::cout << count << "\t";
  }
  std::cout << std::endl;
  
  return 0;
}