#include "assert.h"
#include "limits.h"
#include "stdint.h"
#include <algorithm>
#include <iostream>
#include <vector>

// find position of the target, return the first index of the target in O(lgn), except the sort
int32_t FindFirstPosition(std::vector<int32_t> &nums, int32_t target) {
    // 1 2 3 4 5, 3 -> return 2  (find the pos)
    // 1 2 3 4, 4   -> return -1  (not found)
    std::sort(nums.begin(), nums.end());
    if (nums.empty()) return -1; // not exist

    // binary search
    int32_t i = 0;
    int32_t j = nums.size(); // find the target in [i, j)
    while (i + 1 < j) {      // exit when we have only 1 element
        uint32_t mid = i + ((j - 1 - i) >> 1);
        if (nums[mid] >= target)
            j = mid + 1;
        else
            i = mid + 1;
    }

    // return the position
    if (nums[i] == target)
        return i;
    else
        return -1;
}

// find last position of the target, return the last index of the target in O(lgn), except the sort
int32_t FindLastPosition(std::vector<int32_t> &nums, int32_t target) {
    // 1 2 3 4 5, 3 -> return 2  (find the pos)
    // 1 2 3 4, 4   -> return -1  (not found)
    std::sort(nums.begin(), nums.end());
    if (nums.empty()) return -1; // not exist

    // binary search
    int32_t i = 0;
    int32_t j = nums.size(); // find the target in [i, j)
    while (i + 1 < j) {      // exit when we have only 1 element
        uint32_t mid = i + ((j - i) >> 1);
        if (nums[mid] > target)
            j = mid;
        else
            i = mid;
    }

    // return the position
    if (nums[i] == target)
        return i;
    else
        return -1;
}

// search for a range
std::vector<int> searchRange(std::vector<int> &nums, int target) {
    std::vector<int> res(2, -1);
    res[0] = FindFirstPosition(nums, target);
    if (res[0] == -1) return res;
    res[1] = FindLastPosition(nums, target);
    return res;
}

// find first bad version in O(lgn)
int32_t FindFirstBadVersion(std::vector<bool> &nums) {
    if (nums.empty()) return -1; // not exist

    // binary search
    int32_t i = 0;
    int32_t j = nums.size(); // find the target in [i, j)
    while (i + 1 < j) {      // exit when we have only 1 element
        uint32_t mid = i + ((j - 1 - i) >> 1);
        if (nums[mid])
            j = mid + 1;
        else
            i = mid + 1;
    }

    // return the position
    if (nums[i])
        return i;
    else
        return -1;
}

int FindPeakElement(std::vector<int> &nums) {
    auto GetNums = [&nums](int index) {
        if (index == -1 || index == nums.size()) return INT64_MIN;
        return int64_t(nums[index]);
    };
    int i = 0;
    int j = nums.size();
    while (i < j) {                   // we still have element to handle
        int mid = i + ((j - i) >> 1); // mid belongs to [i, j)
        if (GetNums(mid - 1) < GetNums(mid) && GetNums(mid) < GetNums(mid + 1))
            i = mid + 1; // increase
        else if (GetNums(mid - 1) < GetNums(mid) && GetNums(mid) > GetNums(mid + 1))
            return mid;
        else if (GetNums(mid - 1) > GetNums(mid))
            j = mid; // decrease then xxx
        else
            assert(false && "An bad question"); // no equal between two continorous data
    }
    return -1; // no peak here since the nums is empty
}

int SearchRotatedArray(std::vector<int> &nums, int target) {
    int i = 0, j = nums.size();
    while (i < j) {
        int mid = i + ((j - i) >> 1);
        if (nums[mid] == target) return mid;
        if (i + 1 == j) return (nums[i] == target ? i : -1); // only one ele

        // binary search
        if (nums[mid] >= nums[i]) {
            if (target >= nums[i] && target < nums[mid])
                j = mid;
            else
                i = mid + 1;
        }
        else { // nums[mid] <= nums[j-1]
            if (target > nums[mid] && target <= nums[j - 1])
                i = mid + 1;
            else
                j = mid;
        }
    }
    return -1; // no solution
}

bool SearchRotatedArrayII(std::vector<int> &nums, int target) {
    int i = 0, j = nums.size();
    while (i < j) {
        int mid = i + ((j - i) >> 1);
        if (nums[mid] == target) return true;
        if (i + 1 == j) return (nums[i] == target ? true : false); // only one ele

        // binary search
        if (nums[mid] > nums[i]) {
            if (target >= nums[i] && target < nums[mid])
                j = mid;
            else
                i = mid + 1;
        }
        else if (nums[mid] < nums[j - 1]) {
            if (target > nums[mid] && target <= nums[j - 1])
                i = mid + 1;
            else
                j = mid;
        }
        else if (nums[mid] == nums[i])
            i++;
        else if (nums[mid] == nums[j - 1])
            j--;
        else
            return false; // nums[mid] < nums[i] and nums[mid] > nums[j-1]
    }
    return false; // no solution
}

int FindMinInRotatedArray(std::vector<int> &nums) {
    int i = 0, j = nums.size();
    while (i < j) {
        int mid = i + ((j - i) >> 1);
        if (nums[i] <= nums[j - 1])
            return nums[i]; // only one element or ascending order
        else if (nums[i] > nums[j - 1]) {
            if (nums[mid] >= nums[i])
                i = mid + 1;
            else { // nums[mid] <= nums[j-1]
                i++;
                j = mid + 1;
            }
        }
    }
    return INT_MIN; // no solution
}

int FindMinInRotatedArrayII(std::vector<int> &nums) {
    int i = 0, j = nums.size();
    while (i < j) {
        int mid = i + ((j - i) >> 1);
        if (i == j - 1 || nums[i] < nums[j - 1])
            return nums[i]; // only one element or ascending order
        else if (nums[i] == nums[j - 1])
            i++;
        else if (nums[i] > nums[j - 1]) {
            if (nums[mid] >= nums[i])
                i = mid + 1;
            else { // nums[mid] <= nums[j-1]
                i++;
                j = mid + 1;
            }
        }
    }
    return INT_MIN; // no solution
}

double FindMedianSortedArrays(std::vector<int> &nums1, std::vector<int> &nums2) {
    uint32_t beg1 = 0;
    uint32_t beg2 = 0;
    uint32_t sz1 = nums1.size();
    uint32_t sz2 = nums2.size();
    uint32_t k = (sz1 + sz2) / 2 + (sz1 + sz2) % 2;
    uint32_t has_next = ((sz1 + sz2) % 2 == 1 ? 0 : 1);               // 总个数为偶数时，需要找下一个元素
    while (sz1 != beg1 && sz2 != beg2 && k != 1) {                    // not overflow
        uint32_t offset1 = std::min((k >> 1) - 1, sz1 - beg1 - 1);    // if k=2, offset1 is 0
        uint32_t offset2 = std::min(k - offset1 - 2, sz2 - beg2 - 1); // if k is 2, offset2 is 0;
        if (nums1[beg1 + offset1] > nums2[beg2 + offset2]) {
            beg2 = beg2 + offset2 + 1;
            k = k - offset2 - 1;
        }
        else {
            beg1 = beg1 + offset1 + 1;
            k = k - offset1 - 1;
        }
    } // calculate the res, 为了简单，我们这里定义nums1[sz1] = nums2[sz2] = +INF
    auto GetData = [](std::vector<int> &nums, uint32_t index) {
        if (index == nums.size()) return INT64_MAX;
        return int64_t(nums[index]);
    };
    if (k == 1) {
        if (has_next == 1) {
            double median = std::min(GetData(nums1, beg1), GetData(nums2, beg2));
            GetData(nums1, beg1) > GetData(nums2, beg2) ? beg2++ : beg1++;
            median += std::min(GetData(nums1, beg1), GetData(nums2, beg2));
            return median / 2.0;
        }
        else
            return std::min(GetData(nums1, beg1), GetData(nums2, beg2));
    }
    else if (sz1 == beg1) {
        if (has_next == 1) {
            return (nums2[beg2 + k - 1] + nums2[beg2 + k]) / 2.0;
        }
        else
            return nums2[beg2 + k - 1];
    }
    else if (sz2 == beg2) {
        if (has_next == 1) {
            return (nums1[beg1 + k - 1] + nums1[beg1 + k]) / 2.0;
        }
        else
            return nums1[beg1 + k - 1];
    }
    else
        assert(false && "Bug.");
}

int MySqrt(int x) {
    if (x < 0) assert(false && "Invalid input x.");
    uint32_t i = 0, j = 0x10000;
    // uint8_t cnt = 0;
    while (i != j) {
        uint64_t mid = ((j - i + 1) >> 1) + i;
        // std::cout << i << "\t" << j << "\t" << mid << std::endl;
        if (mid * mid > x)
            j = mid - 1;
        else if (mid * mid < x)
            i = mid;
        else // mid * mid = x
            return mid;
    }
    return i; // only 1 element
}

int WoodCut(std::vector<int> &L, int k) {
    if (L.empty()) return 0;
    uint32_t i = 0;
    uint32_t j = *std::max_element(L.begin(), L.end()); // j为数组L中的最大值

    // the combination of L, k, length is valid or not
    auto ValidLength = [](std::vector<int> &L, int k, uint32_t length) {
        uint32_t segment = 0;
        for (auto wood : L) {
            segment += wood / length;
            if (segment >= k)
                return true;
        }
        return false;
    };

    // binary search for the max length
    while (i < j) {
        uint32_t mid = i + ((j - i + 1) >> 1);
        if (ValidLength(L, k, mid)) // 这个函数表示长度选为mid时，能将L最少划分为k段
            i = mid;
        else
            j = mid - 1;
    }
    return i;
}

int32_t main() {
    //std::vector<int32_t> nums = {1};
    //std::cout << FindFirstPosition(nums, 1) << std::endl; // return 0;
    //std::vector<int32_t> nums1 = {1};
    //std::cout << FindFirstPosition(nums1, 2) << std::endl; // return -1;
    //std::vector<int32_t> nums2 = {1, 2, 3};
    //std::cout << FindFirstPosition(nums2, 3) << std::endl; // return 2;
    //std::vector<int32_t> nums3 = {1, 2, 3};
    //std::cout << FindFirstPosition(nums3, 1) << std::endl; // return 0;
    //std::vector<int32_t> nums4 = {1, 2, 3, 4};
    //std::cout << FindFirstPosition(nums4, 2) << std::endl; // return 1;
    //std::vector<int32_t> nums5 = {1, 2, 5, 6};
    //std::cout << FindFirstPosition(nums5, 3) << std::endl; // return -1;

    //std::vector<bool> nums6 = {0, 0, 0, 0, 1};
    //std::cout << FindFirstBadVersion(nums6) << std::endl; // return -1;

    //std::cout << MySqrt(4) << std::endl;

    return 0;
}