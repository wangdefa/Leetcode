//Definition for a binary tree node.
#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
  public:
    vector<TreeNode *> generateTrees(int n) {
        return generateTrees(1, n + 1);
    }

    vector<TreeNode *> generateTrees(int beg, int end) {
        // special case
        vector<TreeNode *> res;
        if (beg == end) {
            res.push_back(NULL);
            return res;
        }

        // for each root, find it's left/right sub_tree
        for (int i = beg; i < end; i++) {
            TreeNode *root;
            TreeNode node(i);
            root = &node;
            vector<TreeNode *> left_set = generateTrees(beg, i);
            vector<TreeNode *> right_set = generateTrees(i + 1, end);
            for (auto left : left_set) {
                for (auto right : right_set) {
                    root->left = left;
                    root->right = right;
                    res.push_back(root);
                }
            }
            // delete root;
        }

        // return the tree set
        return res;
    }
};