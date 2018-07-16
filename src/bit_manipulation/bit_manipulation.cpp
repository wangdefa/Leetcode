#include "stdint.h"
#include <iostream>
#include <unordered_map>
#include <vector>

void Serilize(std::vector<int> vec) {
    for (auto v : vec) {
        std::cout << v << "\t";
    }
    std::cout << std::endl;
}

void Serilize(std::unordered_map<int, int> &data_cnt) {
    for (auto p : data_cnt) {
        std::cout << p.first << "\t" << p.second;
        std::cout << std::endl;
    }
}

int SingleNumber(std::vector<int> &nums) {
    int len = 32; // 在此以32bit的数据为例
    uint32_t sum[32] = {0};
    for (int x_i : nums)
        for (int b = 0; b < len; b++)
            sum[b] += ((x_i >> b) & 0x1);
    // Get result
    int res = 0;
    for (int b = 0; b < len; b++)
        res |= ((sum[b] % 3) << b);
    return res;
}

std::vector<int> SingleNumberIII(std::vector<int> &nums) {
    // Get x1 ^ x2
    int xor_res = 0;
    for (auto x_i : nums)
        xor_res ^= x_i;

    // Get each number
    int num1 = 0, num2 = 0;
    int lowest_valid_bit = xor_res ^ (xor_res & (xor_res - 1)); // Get the lowest valid bit
    for (auto x_i : nums) {
        if ((x_i & lowest_valid_bit) == 0)
            num1 ^= x_i;
        else
            num2 ^= x_i;
    }

    return std::vector<int>{num1, num2};
}

int NumTrees(int n) {
    // special case
    if (n <= 0) return -1;

    // dp
    std::vector<int> counter(n + 1, 0);
    counter[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            counter[i] += counter[j - 1] * counter[i - j];
        }
        std::cout << counter[i] << std::endl;
    }
    return counter[n];
}

int UpdateBits(int n, int m, int i, int j) {
    // write your code here
    uint64_t mask = ((uint64_t(1) << (j - i + 1)) - 1) << i;
    n &= (~mask);
    std::cout << mask << "\t";
    std::cout << n << "\t";
    return n ^ (m << i);
}

std::vector<int> MajorityElement(std::vector<int> &nums, int k) {
    // find all the number which have at least 1/k,
    std::vector<int> res;
    if (nums.empty()) return res;

    // Get the candidate
    std::unordered_map<int, int> data_cnt;
    for (int d : nums) {
        std::cout << "Input " << d << std::endl;

        // Already have this one, we should add the cnt
        if (data_cnt.find(d) != data_cnt.end()) {
            data_cnt[d]++;
            Serilize(data_cnt);
            continue;
        }

        // Not enough k different data, insert this one
        if (data_cnt.size() < k - 1) {
            data_cnt[d] = 1; // init
            Serilize(data_cnt);
            continue;
        }

        // Erase this data is cnt is 1, else cnt--
        for (auto p = data_cnt.begin(); p != data_cnt.end();) {
            if (p->second == 1)
                data_cnt.erase(p++);
            else {
                p->second--;
                p++;
            }
        }
        Serilize(data_cnt);
    }

    // Verify the candidate
    for (auto &p : data_cnt)
        p.second = 0;
    // Serilize(data_cnt);
    for (int d : nums)
        if (data_cnt.find(d) != data_cnt.end())
            data_cnt[d]++;
    // Serilize(data_cnt);
    for (auto p : data_cnt)
        if (p.second > nums.size() / k)
            res.push_back(p.first);
    return res;
}

int main() {
    // std::cout << NumTrees(3) << std::endl;
    // std::cout << UpdateBits(1, -1, 0, 31) << std::endl;

    std::vector<int> vec{1, 2, 1, 2, 1};
    vec = MajorityElement(vec, 2);
    Serilize(vec);
    return 0;
}