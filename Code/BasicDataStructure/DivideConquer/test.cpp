#include <iostream>
#include <iomanip>  
#include "divide_conquer.h"
#include "stdint.h"

void Serilize(std::vector<uint32_t>& data)
{
    std::cout << "vector:\t";
    for (auto d : data)
    {
        std::cout << d << "\t";
    }
    std::cout << std::endl;
}

int main()
{
	// input 
	std::vector<uint32_t> vec{1,2,2,3,4,6,6,6,13,18};
	SearchRange search_range(vec);
    std::cout << search_range.LowerBound(6) << std::endl;
    std::cout << search_range.LowerBound(7) << std::endl;
    std::cout << search_range.UpperBound(6) << std::endl;
    std::cout << search_range.UpperBound(7) << std::endl;

	return 0;
}
