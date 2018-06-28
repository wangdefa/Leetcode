#include "stdint.h"
#include <algorithm>
#include <iostream>
#include <string>

// s[i...] matches p[j...]
bool IsMatch(const std::string &t, const std::string &p, uint32_t i,
             uint32_t j) {
    while (i < t.size() && j < p.size()) {
        if (t[i] == p[j] || p[j] == '?') {
            i++, j++; // present char is matching
        }
        else if (p[j] == '*') // match 0 or any length string
        {
            uint32_t len = 0;
            for (; len <= t.size() - i; len++) {
                if (IsMatch(t, p, i + len, j + 1)) {
                    return true;
                }
            }
            return false; // all the possible match fails
        }
        else {
            return false; // present char is not matching
        }
    }

    while (j < p.size() && p[j] == '*')
        j++; // remove the useless *
    if (i == t.size() && j == p.size()) {
        return true;
    }
    else {
        return false;
    }
}

bool IsMatchDfs(const std::string &t, const std::string &p) {
    std::cout << t << " matches " << p << "  :";
    return IsMatch(t, p, 0, 0);
}

bool IsMatch(std::string s, std::string p) {
    uint32_t sz_s = s.size();
    uint32_t sz_p = p.size();

    // Remove all the continuous * in pattern string
    uint32_t j = 0;
    for (uint32_t i = 0; i < sz_p; i++) {
        if (j == 0 || p[i] != '*' || p[j - 1] != '*') {
            p[j++] = p[i]; // this i is valid
        }
    }
    p.resize(j);
    sz_p = j;
    std::cout << p << std::endl;

    // Init the first row and column of the dp
    std::vector<bool> tmp(sz_p + 1, false);
    std::vector<std::vector<bool>> dp(sz_s + 1, tmp);
    dp[0][0] = true;                       // init the first
    for (uint32_t i = 1; i <= sz_p; i++) { // first row
        dp[0][i] = (p[i - 1] == '*' ? dp[0][i - 1] : false);
        // std::cout << dp[0][i] << std::endl;
    }

    // Infer
    for (uint32_t i = 1; i <= sz_s; i++) {
        for (uint32_t j = 1; j <= sz_p; j++) {
            if (s[i - 1] == p[j - 1] || p[j - 1] == '?') {
                dp[i][j] = dp[i - 1][j - 1]; // present char is matching
            }
            else if (p[j - 1] == '*') { // match 0 or any length string
                dp[i][j] = (dp[i - 1][j] || dp[i][j - 1]);
            }
            else {
                dp[i][j] = false; // present char is not matching
            }
        }
    }
    // for (uint32_t i = 0; i <= sz_s; i++) {
    //   for (uint32_t j = 0; j <= sz_p; j++) {
    //     std::cout << dp[i][j] << "\t";
    //   }
    //   std::cout << std::endl;
    // }
    return dp[sz_s][sz_p];
}

int32_t main(void) {
    std::cout << IsMatch("abcaa", "?*?a") << std::endl;
    std::cout << IsMatch("abcaa", "a?*?a") << std::endl;
    std::cout << IsMatch("a*bcaa", "c?*?a") << std::endl;
    std::cout << IsMatch("aa", "*") << std::endl;
    return 0;
}