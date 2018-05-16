#include<vector>
#include<queue>
#include <iostream>
#include <iomanip>  
#include "assert.h"
#include "stdint.h"

class SearchRange
{
    public:
        std::vector<uint32_t> m_data;

    public:
        SearchRange(){}
        SearchRange(std::vector<uint32_t>& data) : m_data(data){}
        
        // Explanation:
        //  1. Result will be in the range (i, j];
        //  2. if m_data[mid] < target, i = mid can guarantee the condition 1;
        //  3. if m_data[mid] >= target, j = mid can guarantee the condition 1;
        //  4. j = i + 1, when the loop is finished
        int32_t LowerBound(uint32_t target)
        {
            // Function:
            //      min index;
            //      s.t. m_data[index] >= target
            if (m_data.empty())
            {
                return -1;
            }

            int32_t i = -1; 
            int32_t j = m_data.size();
            while(i + 1 < j) // or it can be dead lock
            {
                int32_t mid = i + ((j - i) >> 1);
                if (m_data[mid] < target)
                {
                    i = mid; 
                }
                else
                {
                    j = mid;
                }
            }

            return j;
        }

        // Explanation:
        //  1. Result will be in the range [i, j); 
        //  2. if m_data[mid] > target, j = mid can guarantee the condition 1;
        //  3. if m_data[mid] <= target, i = mid can guarantee the condition 1;
        //  4. j = i + 1, when the loop is finished
        int32_t UpperBound(uint32_t target)
        {
            // Explanation:
            //      max index;
            //      s.t. m_data[index] <= target
            if (m_data.empty())
            {
                return -1;
            }

            int32_t i = -1;
            int32_t j = m_data.size();
            while (i + 1 < j)
            {
                int32_t mid = i + ((j - i) >> 1);
                if (m_data[mid] > target)
                {
                    j = mid; 
                }
                else
                {
                    i = mid;
                }
            }

            return i;
        }
};