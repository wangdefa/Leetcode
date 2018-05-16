#include<vector>
#include<queue>
#include <iostream>
#include <iomanip>  
#include "assert.h"
#include "stdint.h"

class Sort
{
    public:
        std::vector<uint32_t> m_data;

    public:
        Sort(){}
        Sort(std::vector<uint32_t>& data) : m_data(data){}
        
        void BubbleSort()
        {
            // stable sort algorithm
            std::size_t sz = m_data.size();
            for (std::size_t i = 0; i < sz; i++)
            {
                for (std::size_t j = sz - 1; j > i; j--)
                {
                    if (m_data[j] < m_data[j - 1])
                    {
                        uint32_t tmp = m_data[j];
                        m_data[j] = m_data[j - 1];
                        m_data[j - 1] = tmp;
                    }
                }
            }
        }

        void SelectionSort()
        {
            std::size_t min_index = 0;
            for (std::size_t i = 0; i < m_data.size(); i++)
            {
                // find the index of the min in range [i, m_data.size
                min_index = i;
                for (std::size_t j = i + 1; j < m_data.size(); j++)
                {
                    if (m_data[min_index] > m_data[j])
                    {
                        min_index = j;
                    }
                }

                // swap the two element
                uint32_t tmp = m_data[i];
                m_data[i] = m_data[min_index];
                m_data[min_index] = tmp;
            }
        }

        void QuickSort(std::size_t begin, std::size_t end)
        {
            auto Partition = [](std::vector<uint32_t>& data, std::size_t i, std::size_t j)
            {
                std::size_t pivot = data[i];
                
                // do the partition
                while (i < j)
                {
                    while (j > i && data[j] >= pivot) j--;
                    data[i] = data[j];

                    while (j > i && data[i] <= pivot) i++;
                    data[j] = data[i];
                }
                data[i] = pivot;
                return i;
            };

            // special case
            if (end - begin <= 1) 
            {
                return; // one element or less
            }
            std::size_t pivot = Partition(m_data, begin, end - 1);
            QuickSort(begin, pivot); // [begin, pivot)
            QuickSort(pivot + 1, end); // [pivot + 1, end)
        }

        void MergeSort(std::size_t begin, std::size_t end)
        {
            // special case
            if (end - begin <= 1) 
            {
                return; // one element or less
            }

            // normal case
            std::size_t mid = begin + ((end - begin) >> 1);
            std::size_t begin_backup = begin;
            MergeSort(begin, mid); // [begin, mid)
            MergeSort(mid, end); // [mid, end)

            // Merge the result
            std::queue<uint32_t> tmp_res;
            std::size_t mid_backup = mid;
            while (begin < mid_backup && mid < end)
            {
                if (m_data[begin] <= m_data[mid])
                {
                    tmp_res.push(m_data[begin++]);
                }
                else
                {
                    tmp_res.push(m_data[mid++]);
                }
            }
            
            if (mid == end)
            {
                while(begin < mid_backup)
                {
                    tmp_res.push(m_data[begin++]);
                }
            }
            if (begin == mid_backup)
            {
                while(mid < end)
                {
                    tmp_res.push(m_data[mid++]);
                }
            }
            while(begin_backup < end)
            {
                m_data[begin_backup++] = tmp_res.front();
                tmp_res.pop();
            }
        }
};