#include "stdint.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

uint32_t LongestCommonSubstring(std::string s1, std::string s2) {
    uint32_t m = s1.size();
    uint32_t n = s2.size();
    std::vector<std::vector<uint32_t>> lcss_max(
        m + 1, std::vector<uint32_t>(n + 1, 0)); // row 0, column 0 ->o 0
    std::vector<std::vector<uint32_t>> lcss_suffix(
        m + 1, std::vector<uint32_t>(n + 1, 0)); // row 0, column 0 ->o 0
    for (uint32_t i = 0; i < m; i++) {
        for (uint32_t j = 0; j < n; j++) {
            // Get the longest common suffix
            if (s1[i] == s2[j]) {
                lcss_suffix[i + 1][j + 1] = lcss_suffix[i][j] + 1;
            }
            else {
                lcss_suffix[i + 1][j + 1] = 0;
            }
            // Get max from the 3 choices
            lcss_max[i + 1][j + 1] = std::max(lcss_max[i][j + 1], lcss_max[i + 1][j]);
            lcss_max[i + 1][j + 1] =
                std::max(lcss_max[i + 1][j + 1], lcss_suffix[i + 1][j + 1]);
        }
    }
    return lcss_max[m][n];
}

int main(void) {
    std::string s1 = "CBCE";
    std::string s2 = "ABCD";

    std::cout << LongestCommonSubstring(s1, s2) << std::endl;
    return 0;
}
