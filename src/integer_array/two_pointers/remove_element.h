#include "stdint.h"
#include <iostream>
#include <vector>

// Two pointer method to remove the element in nums if equals to val
//  If we find an invalid ele, we should find an valid ele from tail to replace it
uint32_t RemoveElement(std::vector<int32_t> nums, int32_t val) {
    uint32_t first = 0;            // the present ele we should scan
    uint32_t second = nums.size(); // the guard is used to find another valid ele

    while (first < second) {
        while (first < second && nums[first] != val)
            first++; // find the first index met nums[first]=val
        while (first < second && nums[second - 1] == val)
            second--; // find the second index met nums[second-1]!=val
        if (first != second)
            nums[first++] = nums[--second];
    }
    return first;
}