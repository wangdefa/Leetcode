#include "combination_sum.h"

int main() {
  // input
  vector<int> src = {29, 19, 14, 33, 11, 5,  9,  23, 23, 33, 12, 9,  25,
                     25, 12, 21, 14, 11, 20, 30, 17, 19, 5,  6,  6,  5,
                     5,  11, 12, 25, 31, 28, 31, 33, 27, 7,  33, 31, 17,
                     13, 21, 24, 17, 12, 6,  16, 20, 16, 22, 5};
  int target = 28;
  Solution solution;

  // processing and display
  vector<vector<int> > res =
      solution.combinationSum(src, target);  // display the input
  display(res);
  return 0;
}
