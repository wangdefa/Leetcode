#include "assert.h"
#include "limits.h"
#include "stdint.h"
#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

/*Definition for a binary tree node.*/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
  public:
    vector<int> postorderTraversal(TreeNode *root) {
        std::vector<int> result;
        TreeNode *mover = root;
        std::stack<TreeNode *> stack_root;

        while (mover != NULL || !stack_root.empty()) {
            if (mover != NULL) {
                stack_root.push(mover);
                mover = mover->left;
            }
            else {
                mover = stack_root.top();
                if (mover->right == NULL) {
                    result.push_back(mover->val);
                    stack_root.pop();
                }
            }
        }

        while (mover != NULL) {
            // move along the left until we get the first element (left most node)
            while (mover != NULL) {
                stack_root.push(mover);
                mover = mover->left;
            }

            // visit the root and tranverse the right child
            while (mover == NULL && !stack_root.empty()) {
                mover = stack_root.top();
                if (mover->right == NULL) {
                    result.push_back(mover->val);
                    stack_root.pop();
                    while (!stack_root.empty() && stack_root.top()->right == mover) {
                        mover = stack_root.top();
                        result.push_back(mover->val);
                        stack_root.pop();
                    }
                    mover = NULL;
                }
                else {
                    mover = mover->right;
                }
            }
        }

        return result;
    }
};