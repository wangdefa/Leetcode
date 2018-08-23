#include "stdint.h"
#include <algorithm>
#include <limits.h>
#include <string>
using namespace std;

int32_t minCut(string s) {
    // Special case
    if (s.empty()) return 0;

    // Initialize
    int32_t n = s.size();
    vector<int32_t> status(n, INT_MAX); // status[i] = minCut(str[0, i]);
    vector<vector<bool>> is_palindrome(n, vector<bool>(n, false));

    // Get the is_palindrome array
    for (int32_t axis = 0; axis < n; axis++) {
        for (int32_t axis_bias = 0; axis_bias <= 1; axis_bias++) { // use this to deal with the axis=0.5 or so
            for (int32_t len = 0;; len++) {
                int32_t axis1 = axis - len;
                int32_t axis2 = axis + axis_bias + len;
                if (axis2 < n && axis1 >= 0 && s[axis2] == s[axis1])
                    is_palindrome[axis1][axis2] = true;
                else
                    break;
            }
        }
    }

    // Get the final result
    for (int32_t i = 0; i < n; i++) {
        if (is_palindrome[0][i]) {
            status[i] = 0;
            continue;
        }
        for (int32_t j = 0; j < i; j++) { // str[0:j] str[j+1:i)
            if (is_palindrome[j + 1][i])
                status[i] = min(status[i], status[j] + 1);
        }
    }

    // Return the result
    return status[n - 1];
}