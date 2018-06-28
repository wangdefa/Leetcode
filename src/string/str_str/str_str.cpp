#include "find_substr.h"
#include "stdint.h"
#include <iostream>
#include <string>

// use two pointer method: we can use this as the golden
int32_t StrStr(std::string parttern, std::string text) {
    // Find the first index of parttern in text, is not exist, return -1
    for (int32_t index = 0; index < text.size() - parttern.size() + 1; index++) {
        int32_t j = 0;
        for (; j < parttern.size(); j++) {
            if (text[index + j] != parttern[j]) {
                break; // this position is impossible
            }
        }

        // this means we have got the answer
        if (j == parttern.size()) {
            return index;
        }
    }
    return -1;
}

int32_t KmpStrStr(std::string parttern, std::string text) {
    // 1.build the next table
    std::vector<int32_t> next;
    next.resize(parttern.size());
    next[0] = -1; // fail at the first element, we should go back to -1
    int32_t i = 1, j = next[i - 1];
    while (i < parttern.size()) {
        // reach the boundary or it equals
        if (j == -1 || parttern[i - 1] == parttern[j]) {
            i++, j++;
            next[i - 1] = j;
        }
        else {
            j = next[j];
        }
    }
    // print the table
    std::cout << "The input parttern string and it's next array: " << parttern
              << std::endl;
    for (auto i : next) {
        std::cout << i << "\t";
    }
    std::cout << std::endl;

    // 2. search
    i = 0, j = 0;
    while (i < int32_t(parttern.size()) && j < text.size()) {
        if (i == -1 || parttern[i] == text[j]) {
            i++, j++;
        }
        else {
            i = next[i];
        }
    }

    // 3. return -1 if we didn't find the result
    if (i == parttern.size()) {
        return j - i;
    }
    else {
        return -1;
    }
}

int32_t main(void) {
    // std::string pattern = "abcabcdab";
    std::string pattern = "ABCDABD";            // "aaaabbb";
    std::string text = "ABCABCDABABCDABCDABDE"; //"aaabccdaaaabbbdabcabcdababc";
    std::cout << "Two pointer: The first index of the pattern (" + pattern +
                     ") in text (" + text + ") is:\t"
              << StrStr(pattern, text) << std::endl;

    std::cout << "Kmp method: The first index of the pattern (" + pattern +
                     ") in text (" + text + ") is:\t"
              << KmpStrStr(pattern, text) << std::endl;

    Kmp kmp(pattern, text);
    kmp.CreateNext();
    std::cout << "KMP method: The first index of the pattern (" + pattern +
                     ") in text (" + text + ") is:\t";
    std::cout << kmp.Find() << std::endl;
    return 0;
}