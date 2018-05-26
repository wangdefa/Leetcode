#include "buy_stocks.h"

int main() {
  // input
  std::vector<int> src = {29, 19, 14, 33, 11, 5, 9, 23, 23, 33, 12, 5};
  BuyStocks test(src);

  // processing and display
  std::vector<int> res = test.maxProfit();  // display the input
  display(res);
  return 0;
}
