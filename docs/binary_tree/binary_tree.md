

[TOC]

### Binary Tree

#### Binary Tree Preorder Traversal

Given a binary tree, return the *preorder* traversal of its nodes' values.

**Example:**

```
Input: [1,null,2,3]
   1
    \
     2
    /
   3

Output: [1,2,3]
```

**Follow up:** Recursive solution is trivial (不重要的), could you do it iteratively?

##### Algorithm description and certification

这个题的基本大意是：对一颗二叉树进行先序遍历 (采用迭代的方法，而非递归)。大致思路如下：

1. 将根节点加入到 栈 (Stack) 当中；
2. 从栈中取出一个节点，然后沿着 左孩子 访问到底，并且将沿途的有孩子加入到 栈 当中；
3. 若栈不为空，回到第二步；

##### Code

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        std::vector<int> result;
        std::stack<TreeNode*> root_stack;
        root_stack.push(root);        
        
        // visit all the node
        while (!root_stack.empty()){
            TreeNode* root_to_visit = root_stack.top();
            root_stack.pop();
            
            // visit all the node along the left child
            while (root_to_visit != NULL){
                result.push_back(root_to_visit->val); // visit the root
                root_stack.push(root_to_visit->right);
                root_to_visit = root_to_visit->left;
            }
        }
        
        return result;
    }
};
```

##### Reference

[Binary Tree Preorder Traversal](https://leetcode.com/problems/binary-tree-preorder-traversal/description/)

[数据结构(C++ 语言版), 5.4.2 迭代版先序遍历](https://item.jd.com/12113082.html)



#### Binary Tree Inorder Traversal

Given a binary tree, return the *inorder* traversal of its nodes' values.

**Example:**

```
Input: [1,null,2,3]
   1
    \
     2
    /
   3

Output: [1,3,2]
```

**Follow up:** Recursive solution is trivial, could you do it iteratively?

##### Algorithm description and certification

迭代版的中序遍历，与迭代版的先序遍历比较类似；以下为其大致流程：

1. 从 root 一直往左走，并且将沿途的节点加入到 栈 当中；一直到走不下去；
2. 若栈不为空，从栈中取出一个元素，并且访问它；
3. 若此元素的 右孩子 不为空，则将 右孩子当做 root，返回第一步；
4. 否则 回到第二步；

```cpp
while (root != NULL)
    // move along the left until we get the first element (left most node)
     while (root != NULL)
          stack.push(root);
          root = root->left;
         
     // visit the root and tranverse the right child
     while(root == NULL && !stack.empty())
         root = stack.top(); stack.pop();
         visit(root); // visit root       
         root = root->right; // move and check right child 
```

##### Code

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        std::vector<int> result;
        TreeNode* mover = root;
        std::stack<TreeNode*> stack_root;
        
        while(mover != NULL){
            // move along the left until we get the first element (left most node)
            while (mover != NULL){
                stack_root.push(mover);
                mover = mover->left;
            }
            
            // visit the root and tranverse the right child
            while(mover == NULL && !stack_root.empty()){
                mover = stack_root.top();
                result.push_back(mover->val);
                stack_root.pop();
                mover = mover->right;
            }
        }
        
        return result;
    }
```

##### Reference

[Binary Tree Inorder Traversal](https://leetcode.com/problems/binary-tree-inorder-traversal/description/)



#### Binary Tree Postorder Traversal

##### Algorithm description and certification

可以参考下 数据结构(邓俊辉著) 这本书上面的解答；

1. 将 root 加入 栈 S 里面；设当前已访问元素 mover 为一个 dummy 节点；
2. 若 栈 S不为空，进入第 3 步；否则退出；
3. 若 mover != S.top->left && mover != S.top->right；
   // 栈顶元素不为当前元素的父节点，那么此节点需要单独作为一棵树进行 后序遍历；
4. 若 S.top 左右孩子 不均为空，按照 右孩子、左孩子 的顺序将其加入到栈当中；直到 S.top 的左右孩子均为 空；
5. 否则取出栈顶元素，并访问；然后回到第 2 步；

还有一些其他的解法，其直接按照 后序遍历 的对立面进行遍历（就是遍历的顺序与后序遍历刚好相反），然后对结果进行反转，感觉有点投机取巧的意味。

##### Code

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        if (root == NULL) return res;
        TreeNode node(0);
        TreeNode* visited_node = &node;
        stack<TreeNode*> s;
        s.push(root);
        
        while (!s.empty()){
            // if last visited node is not the child of the present node,
            // it must be the right sibling and should be visited to deep
            if (visited_node != s.top()->left && visited_node != s.top()->right){
                while (s.top()->left != NULL || s.top()->right  != NULL){
                    TreeNode* tmp = s.top(); // save the top, since it will be changed
                    if (tmp->right != NULL) s.push(tmp->right);
                    if (tmp->left != NULL) s.push(tmp->left);
                }
            }
            
            // visit the node in the top of stack
            visited_node = s.top(); s.pop();
            res.push_back(visited_node->val);
        }
        return res;
    }
};
```

##### Reference

[数据结构(C++ 语言版), 5.4.4 迭代版后序遍历](https://item.jd.com/12113082.html)



#### Binary Tree Level Order Traversal

Given a binary tree, return the *level order* traversal of its nodes' values. (ie, from left to right, level by level).

For example:
Given binary tree `[3,9,20,null,null,15,7]`,

```
    3
   / \
  9  20
    /  \
   15   7
```

return its level order traversal as:

```
[
  [3],
  [9,20],
  [15,7]
]
```

##### Algorithm description and certification

对于一棵树的层次遍历，直接采用一个队列，然后进行BFS遍历即可； 但是本题要在结果当中体现出树的层次结构，可以考虑采用两个队列，两个队列分别保留当前层与下一层的节点，然后不断向前滚动即可；

1. 将根节点放入队列 1；
2. 若队列1不为空，退出程序；否则进行第3步；
3. 从队列1当中取出队列首元素，然后将其左右孩子加入到队列2，直到队列1为空；再此过程当中，将队列1当中的元素保存下来，作为树的一层；
4. 从队列2当中取出队列首元素，然后将其左右孩子加入到队列1，直到队列2为空；再此过程当中，将队列2当中的元素保存下来，作为树的一层；然后回到第2步；

##### Code

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if (root == NULL) return res;
        std::queue<TreeNode*> q0;
        std::queue<TreeNode*> q1;
        q0.push(root);        
        vector<int> tmp;
        
        // use two queue interlevel to get the level order
        while (!q0.empty()){
            while (!q0.empty()){ // run out of the first queue
                TreeNode* node = q0.front(); q0.pop();
                if (node->left != NULL) q1.push(node->left);
                if (node->right != NULL) q1.push(node->right);
                tmp.push_back(node->val);
            }
            res.push_back(tmp);
            tmp.clear();
            
            while(!q1.empty()) { // run out of the second queue
                TreeNode* node = q1.front(); q1.pop();
                if (node->left != NULL) q0.push(node->left);
                if (node->right != NULL) q0.push(node->right);
                tmp.push_back(node->val);
            }
            if(!tmp.empty()) res.push_back(tmp); // look, may tmp is empty
            tmp.clear();
        }
        
        return res;
    }
};
```

##### Reference

[Binary tree level order traaversal](https://leetcode.com/problems/binary-tree-level-order-traversal/description/)



#### Diameter of Binary Tree

Given a binary tree, you need to compute the length of the diameter of the tree. The diameter of a binary tree is the length of the **longest** path between any two nodes in a tree. This path may or may not pass through the root.

**Example:**
Given a binary tree 

```
          1
         / \
        2   3
       / \     
      4   5    
```

Return **3**, which is the length of the path [4,2,1,3] or [5,2,1,3].

**Note:** The length of path between two nodes is represented by the number of edges between them.

##### Algorithm description and certification

只需要找出以所有的节点为 根节点 的那条通路的最大长度，然后选择最长的即可；
如以上例子，只需要找出以 1， 2， 3， 4， 5为根节点的最长通路即可；
节点１，其最长通路左右子树的高度之和，即为： 2 +１＝３；
节点２，其最长通路左右子树的高度之和，即为： １ +１＝２；
......

##### Code

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:    
    int diameterOfBinaryTree(TreeNode* root) {
        // special case
        if (root == NULL) return 0;
        
        // initialize
        max_length = 0;
        getHeight(root);
        return max_length;        
    }
    int getHeight(TreeNode * node){
        // special case
        if (node == NULL) return 0;
        
        // update the max_length and return the height
        int height_left = getHeight(node->left);
        int height_right = getHeight(node->right);
        max_length = max(max_length, height_left + height_right);
        return max(height_left, height_right) + 1;
    }
    
private:
    int max_length;
};
```

##### Reference

[Diameter of Binary Tree](https://leetcode.com/problems/diameter-of-binary-tree/description/)



#### Invert Binary Tree

Invert a binary tree.

**Example:**

Input:

```
     4
   /   \
  2     7
 / \   / \
1   3 6   9
```

Output:

```
     4
   /   \
  7     2
 / \   / \
9   6 3   1
```

##### Algorithm description and certification

可以很明显看出，题目的要求是对所有的节点，将其左子树与右子树进行交换位置。解题思路与广度优先搜索一致，在每次从队列当中　pop 出来一个节点后，若此节点不空，则将其左右子树进行调换。

##### Code

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (root == NULL) return root;
        
        std::queue<TreeNode*> q_node;
        q_node.push(root);
        while(!q_node.empty()){
            TreeNode* node = q_node.front();
            q_node.pop();
            if (node == NULL) continue;
            
            TreeNode* tmp = node->left;
            node->left = node->right;
            node->right = tmp;
            q_node.push(node->left);
            q_node.push(node->right);
        }
        return root;
    }
};
```

##### Reference

[Invert Binary Tree](https://leetcode.com/problems/invert-binary-tree/description/)



#### Construct Binary Tree from Preorder and Inorder Traversal

Given preorder and inorder traversal of a tree, construct the binary tree.

**Note:**
You may assume that duplicates do not exist in the tree.

For example, given

```
preorder = [3,9,20,15,7]
inorder = [9,3,15,20,7]
```

Return the following binary tree:

```
    3
   / \
  9  20
    /  \
   15   7
```

##### Algorithm description and certification

整个题直接采用递归的思路进行求解。

1. 从先序遍历序列当中拿出第一个元素 val，以其为当前子树的树根；
2. 在中序遍历序列当中查找出 val 的下标 i，并且以此将中序遍历序列分为两个序列： left_in, right_in；
3. 根据 left 序列的长度将先序遍历序列划分为 3 块，root, left_pre, right_pre;
4. 分别对 {left_in, left_pre}, {right_in, right_pre} 进行递归调用，从而形成 左子树与右子树。
5. 当 左右子树均为空时，返回。

##### Code

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return buildTree(preorder, inorder, 0, preorder.size(), 0, inorder.size());
    }
    
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder, int pi, int pj, 
                        int ii, int jj){
        if (pi == pj || ii == jj) return NULL;
        
        // find index of the root in the inorder traversal sequence
        TreeNode* root = new TreeNode(preorder[pi]); // create the root of the sub tree
        int i = std::find(inorder.begin(), inorder.end(), 
                          preorder[pi]) - inorder.begin(); 
        int left_size = i - ii;
        
        // build the left and right sub tree
        root->left = buildTree(preorder, inorder, pi+1, pi+1+left_size, ii, i);
        root->right = buildTree(preorder, inorder, pi+1+left_size, pj, i+1, jj);
        return root;
    }
};
```

##### Reference

[Construct Binary Tree from Preorder and Inorder Traversal](https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/description/)



#### Construct Binary Tree from Inorder and Postorder Traversal

Given inorder and postorder traversal of a tree, construct the binary tree.

**Note:**
You may assume that duplicates do not exist in the tree.

For example, given

```
inorder = [9,3,15,20,7]
postorder = [9,15,7,20,3]
```

Return the following binary tree:

```
    3
   / \
  9  20
    /  \
   15   7
```

##### Algorithm description and certification

与根据 中序遍历+先序遍历 进行复原 binary tree 的方式类似，只不过这里将通过 后序遍历 获取每棵子树的根节点，剩下的逻辑与前一题保持一致。

##### Code

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        return buildTree(inorder, postorder, 0, inorder.size(), 0, postorder.size());
    }
    
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder, int ii, int ij, 
                        int pi, int pj){
        if (pi == pj || ii == ij) return NULL;
        
        TreeNode* root = new TreeNode(postorder[pj - 1]); // root
        int index = std::find(inorder.begin(), inorder.end(), 
                              postorder[pj - 1]) - inorder.begin();
        root->left = buildTree(inorder, postorder, ii, index, pi, pi+index-ii);
        root->right = buildTree(inorder, postorder, index+1, ij, pi+index-ii, pj-1);
        return root;
    }
};
```

##### Reference

[Construct Binary Tree from Inorder and Postorder Traversal](https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/description/)



#### Subtree of Another Tree

Given two non-empty binary trees **s** and **t**, check whether tree **t** has exactly the same structure and node values with a subtree of **s**. A subtree of **s** is a tree consists of a node in **s** and all of this node's descendants. The tree **s** could also be considered as a subtree of itself.

**Example 1:**
Given tree s:

```
     3
    / \
   4   5
  / \
 1   2
```

Given tree t:

```
   4 
  / \
 1   2
```

Return true, because t has the same structure and node values with a subtree of s.

**Example 2:**
Given tree s:

```
     3
    / \
   4   5
  / \
 1   2
    /
   0
```

Given tree t:

```
   4
  / \
 1   2
```

Return false.

##### Algorithm description and certification

因为当且仅当树s的子树 sub_tree_s 与 树t 完全一样时，二者才看做是相等的；若存在满足条件的子树，那么子树 sub_tree_s 与树 t 的深度完全一致；因此可以分为以下两步进行求解：

1. 在树 s 当中找寻深度与 树t 一致的节点，作为候选节点并且加入到队列 q 当中；
2. 对 q 当中任一节点，将其作为子树的根 与 树 t 进行对比，若二者一致，则找到，否则找不到；

因为找候选节点的时间复杂度为 $O(n)$, 将队列里面的所有节点与树 t 进行对比的时间复杂度为 $O(n)$，故整体的时间复杂度为 $O(n)$.

##### Code

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isSubtree(TreeNode* s, TreeNode* t) {
        // special case
        if (t == NULL) return true;
        
        // Get the condidate and compare to each condidate
        int depth_t = getDepth(t); // get depth of t
        getCandidate(s, depth_t);  // get all the node whose depth is depth_t
        while (!q.empty()){
            TreeNode* node = q.front(); q.pop();            
            if (isSameTree(node, t)) return true;
        }
        return false;
    }
private:
    bool isSameTree(TreeNode* s, TreeNode* t){
        if (s == NULL && t == NULL) return true;
        if (s == NULL || t == NULL) return false;
        return s->val == t->val && isSameTree(s->left, t->left) 
            && isSameTree(s->right, t->right);
    }
    int getCandidate(TreeNode* node, const int& depth_t){
        if (node == NULL) return 0; // depth != 0
        int depth = max(getCandidate(node->left, depth_t), getCandidate(node->right, depth_t)) + 1;
        if (depth == depth_t) q.push(node);
        return depth;
    }
    
    int getDepth(TreeNode* node){
        if (node == NULL) return 0;
        return max(getDepth(node->left), getDepth(node->right)) + 1;
    }
    
private:    
    std::queue<TreeNode*> q;
};
```

##### Reference

[Subtree of Another Tree](https://leetcode.com/problems/subtree-of-another-tree/description/)



#### Binary Tree Zigzag Level Order Traversal

Given a binary tree, return the *zigzag level order* traversal of its nodes' values. (ie, from left to right, then right to left for the next level and alternate between).

For example:
Given binary tree `[3,9,20,null,null,15,7]`,

```
    3
   / \
  9  20
    /  \
   15   7
```

return its zigzag level order traversal as:

```
[
  [3],
  [20,9],
  [15,7]
]
```

##### Algorithm description and certification

与最开始的层次遍历类似，但是这个地方需要将数据 逢 偶数行进行翻转，因此可以将最开始的队列改成 栈(stack)，在奇数行时，加入节点的顺序为： left, right；在偶数行时的顺序为：right, left 即可。

##### Code

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        // special case
        vector<vector<int>> res;
        if (root == NULL) return res;
        
        // s1 -> s2 -> s1....
        std::stack<TreeNode*> s1;
        std::stack<TreeNode*> s2;
        s1.push(root);
        while (!s1.empty()){
            vector<int> tmp;
            while (!s1.empty()){
                TreeNode* node = s1.top(); s1.pop();
                tmp.push_back(node->val);
                if (node->left != NULL) s2.push(node->left);
                if (node->right != NULL) s2.push(node->right);
            }
            res.push_back(tmp); // it must not empty
            tmp.clear();
            
            while (!s2.empty()){
                TreeNode* node = s2.top(); s2.pop();
                tmp.push_back(node->val);
                if (node->right != NULL) s1.push(node->right);
                if (node->left != NULL) s1.push(node->left);                
            }
            if(tmp.size() != 0) res.push_back(tmp); // can be empty
        }
        
        return res;
    }    
};
```

##### Reference

[Binary Tree Zigzag Level Order Traversal](https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/description/)



#### Serialize and Deserialize Binary Tree

Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure.

**Example:** 

```
You may serialize the following tree:

    1
   / \
  2   3
     / \
    4   5

as "[1,2,3,null,null,4,5]"
```

**Clarification:** The above format is the same as [how LeetCode serializes a binary tree](https://leetcode.com/faq/#binary-tree). You do not necessarily need to follow this format, so please be creative and come up with different approaches yourself.

**Note:** Do not use class member/global/static variables to store states. Your serialize and deserialize algorithms should be stateless.

##### Algorithm description and certification

一道 **序列化与反序列化**的题； 以下提供三种思路来解这道题。

* 方法一

  1. 序列化过程：按照题目意思，将这颗二叉树序列化成一颗 [满二叉树](https://baike.baidu.com/item/%E6%BB%A1%E4%BA%8C%E5%8F%89%E6%A0%91/7773283?fr=aladdin)，NULL 节点也需要进行序列化；直到整个队列当中不存在有效的节点；
  2. 反序列化过程：将根节点加入到队列当中；从队列当中取出当前元素 node，然后从字符串当中取出两个元素，作为 node 的左孩子与右孩子；将左右孩子加入到队列当中，直到整个字符串当中不剩于任何元素，反序列号完成。

  经过在 Leetcode上面测试，这种方式会超出内存的限制；因为其队列的大小与树的高度成 指数 关系。 

  ```cpp
  class Codec {
  public:
      // Encodes a tree to a single string.
      string serialize(TreeNode* root) {
          std::queue<TreeNode*> q; q.push(root);
          std::string res = "";
          bool flag = true;
          uint64_t sz = 1;
          
          while (flag){
              flag = false;
              for (uint64_t i = 0; i < sz; i++){
                  TreeNode* node = q.front(); q.pop();
                  if (node != NULL) {                    
                      res = res + std::to_string(node->val) + ",";
                      q.push(node->left);
                      q.push(node->right);
                      if (node->left != NULL || node->right != NULL) flag = true; 
                  }
                  else{
                      res += "#,";
                      q.push(NULL);
                      q.push(NULL);
                  }                
              }            
              sz <<= 1; // the size of the next level
          }
          
          return res;
      }
  
      // Decodes your encoded data to tree.
      TreeNode* deserialize(string data) {
          if (data.size() == 0) return NULL;
          
          // create the root and push it into queue
          uint64_t sz = 1;
          int64_t start = 0;        
          TreeNode* root = getNode(data, start);
          std::queue<TreeNode*> q; q.push(root);
          
          while (start != data.size()){ 
              std::cout << std::endl;
              for (uint64_t i = 0; i < sz; i++){
                  // left/right child               
                  TreeNode* left = getNode(data, start);
                  TreeNode* right = getNode(data, start);
                  
                  // add the left/right child into queue and tree
                  TreeNode* node = q.front(); q.pop();
                  if (left != NULL) node->left = left; 
                  if (right != NULL) node->right = right; 
                  q.push(left);
                  q.push(right);
              }
              sz <<= 1;
          }        
          return root;
      }
      
      TreeNode* getNode(const string& data, int64_t& start){
          int64_t end = data.find(',', start);
          int64_t tmp = start;        
          start = end + 1;
                 
          if (data.substr(tmp, end-tmp) == "#") return NULL;
          return new TreeNode(atoi(data.substr(tmp, end-tmp).c_str()));
      }
  };
  ```

* 方法二

  整体的思路为将每一个节点进行序列化，序列化的同时保存每个节点以及其左孩子，右孩子的 id；

  1. 序列化过程：关键是如何给定每个节点一个唯一的 id；可以将节点放入到 vector 当中，然后在vector的尾部加上节点的左右孩子，此时vector的长度即为节点的id；
  2. 反序列化过程：反序列化比较简单，第一步可以生成所有的节点，保存在vector当中，第二步可以建立所有节点之间的连接关系，即可恢复出树的原始结构。

  ```cpp
  struct Node {
      int val; // val of present node
      int left; // node_id of left child
      int right; // node_id of right child
      Node() : val(0), left(0), right(0) {}
  };
  class Codec {
  public:
      // Encodes a tree to a single string.
      string serialize(TreeNode* root) {
          if (root == NULL) return "";
          std::vector<TreeNode*> vec; 
          vec.push_back(root);
          std::string res = "";
                  
          for (int64_t index = 0; index < vec.size(); index++){
              res += (std::to_string(index) + ","); // node id
              res += (std::to_string(vec[index]->val) + ","); // node value
              
              // left child node id
              res += (vec[index]->left == NULL ? "#," : std::to_string(vec.size()) + ","); 
              if (vec[index]->left != NULL) vec.push_back(vec[index]->left);
              
              // right child node id
              res += (vec[index]->right == NULL ? "#," : std::to_string(vec.size()) + ","); 
              if (vec[index]->right != NULL) vec.push_back(vec[index]->right); 
          }
          
          return res;
      }
  
      // Decodes your encoded data to tree.
      TreeNode* deserialize(string data) {
          if (data.size() == 0) return NULL;
          
          // create the root and push it into queue
          std::vector<TreeNode*> tree;
          std::vector<Node> vec_node;
          int64_t start = 0;   
          
          // get and save all the node
          while (start != data.size()) getNode(vec_node, data, start);
          
          // create all the node we need
          for (auto node : vec_node) tree.push_back(new TreeNode(node.val));
          
          // build the connection between node
          for (int i = 0; i < vec_node.size(); i++) {
              tree[i]->left = (vec_node[i].left == -1 ? NULL : tree[vec_node[i].left]);
              tree[i]->right = (vec_node[i].right == -1 ? NULL : tree[vec_node[i].right]);
          }
          
          return tree[0];
      }
      
      void getNode(std::vector<Node>& vec_node, const string& data, int64_t& start){
          Node node;
          getVal(data, start); // remove the node_id
          node.val = getVal(data, start); // get node val
          node.left = getVal(data, start); // get left child
          node.right = getVal(data, start); // get right child
          vec_node.push_back(node);        
      }
      
      int getVal(const string& data, int64_t& start) {
          int64_t end = data.find(',', start); // node_id
          int64_t tmp = start;        
          start = end + 1;
          
          // use -1 to represent the null
          if (data.substr(tmp, end-tmp) == "#") return -1; 
          return atoi(data.substr(tmp, end-tmp).c_str());
      }                           
  };
  ```

* 方法三

  这个方法与方法一比较类似，但是因为其不会保存过多的无用节点，因此不会造成内存溢出的情况。主要是参考了 [Leetcode 上面的解法](https://leetcode.com/problems/serialize-and-deserialize-binary-tree/discuss/150070/Readable-fast-C%2B%2B-solution-beats-99.6/160286)；将每一个 有效的节点 及其 子节点 均会进行序列化，也就是说，父节点与左右孩子的数目为 1:2 的关系。

  ```cpp
  class Codec {
  private:
      TreeNode* stringToNode(istringstream & iss) {
          string current;
          iss>>current;
          if(current == "#") return NULL;
          else return new TreeNode(stoi(current));
      }
      
  public:
      // Encodes a tree to a single string.
      string serialize(TreeNode* root) {
          auto iter = root;         
          std::queue<TreeNode*> q;
          q.push(root);
          stringstream ss;
          while(!q.empty()) {                
              auto top = q.front();
              if(top != NULL) {
                  ss << top->val << ' '; // parent node
                  q.push(top->left);     // left child node        
                  q.push(top->right);    // right child node        
              } else {
                  ss << "#" <<' ';       // null node
              }
              q.pop();
          } 
          return ss.str();
      }
  
      // Decodes your encoded data to tree.
      TreeNode* deserialize(string data) {  
          std::istringstream iss(data);
          TreeNode* root = stringToNode(iss);
          if(root == NULL) return NULL;
          std::queue<TreeNode*> q;
          q.push(root); // push in parent
          while(!q.empty()){
              auto top = q.front();
              top->left = stringToNode(iss); // add left child of parent
              if(top->left!=NULL) q.push(top->left);
              top->right = stringToNode(iss); // add right child of parent
              if(top->right!=NULL) q.push(top->right);
              q.pop();
          }
          return root;
      }
  };
  ```

##### Reference

[Leetcode 297](https://leetcode.com/problems/serialize-and-deserialize-binary-tree/description/)