#include "stdint.h"
#include <iostream>
#include <vector>

// find the kth number in nums[i~j)
int32_t FindKth(std::vector<int32_t> &nums, uint32_t k, uint32_t i, uint32_t j) {
    std::cout << i << "\t" << j << "\t" << k << std::endl;
    if (k == 1) return nums[i];

    // partition
    int32_t pivot = nums[i];
    uint32_t first = i;
    uint32_t second = j - 1;
    while (first < second) {
        while (first < second && nums[second] >= pivot)
            second--;
        nums[first] = nums[second];
        while (first < second && nums[first] < pivot)
            first++;
        nums[second] = nums[first];
    }
    nums[first] = pivot;

    // find in the first part or the second part
    if (first - i >= k)
        return FindKth(nums, k, i, first); //find in the interval [i, first)
    else if (first - i == k + 1)
        return nums[first];
    else
        return FindKth(nums, k - (first - i) - 1, first + 1, j); //find in the interval [first + 1, j)
}

// We can do find the kth number
int32_t FindMedian(std::vector<int32_t> &nums) {
    // 1 2 3 4 5 -> return 3
    // 1 2 3 4   -> return 2
    if (nums.empty()) return 0; // we need to handle this situation
    return FindKth(nums, (nums.size() + 1) / 2, 0, nums.size());
}

int32_t main() {
    std::vector<int32_t> nums = {1};
    std::cout << FindMedian(nums) << std::endl;
    return 0;
}