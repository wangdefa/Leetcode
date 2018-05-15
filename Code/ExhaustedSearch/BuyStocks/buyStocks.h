#include<vector>
#include<stack>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>
#include "assert.h"
#include "stdint.h"

void display(const std::vector<int32_t>& res)
{
	std::cout << "Vector: \t";
	for (auto single_res : res)
	{
		std::cout << single_res << "\t";
	}
	std::cout << std::endl;
}

class BuyStocks {
public:
	std::vector<int32_t> m_price;

	BuyStocks(std::vector<int32_t>& price)
	{
		m_price = price;
	}

	std::vector<int32_t> maxProfit() 
	{
		// Select the point of the first sell
		std::vector<int32_t> res(4, 0);		
		std::vector<int32_t> tmp_res(4, 0); // used to save the tmp result
		int64_t max_profit = 0; // the min profit is 0
		int32_t min_front = INT32_MAX;
		for (std::size_t b = 0; b < m_price.size(); b++)
		{
			// display(res);
			// find the max profit in the first phase, b is the first selling point
			int64_t profit_front = 0;
			if (min_front > m_price[b])
			{
				min_front = m_price[b];
				tmp_res[0] = b;
			}
			tmp_res[1] = b; // used to save the index of the present loop
			profit_front = m_price[b] - min_front;
			
			// find the max profit in the second phase
			int64_t profit_back = 0;
			int32_t min_back = INT32_MAX;
			int32_t min_back_index = b;
			for (std::size_t c = b; c < m_price.size(); c++)
			{
				// save the min_index and value
				if (min_back > m_price[c])
				{
					min_back = m_price[c];
					min_back_index = c;
				}

				// use c as the second selling point to get max profit
				if (max_profit < profit_front + m_price[c] - min_back)
				{
					tmp_res[2] = min_back_index;
					tmp_res[3] = c;
					max_profit = profit_front + m_price[c] - min_back;
					res = tmp_res;
				} 
			}
		}
		return res;
	}
};

