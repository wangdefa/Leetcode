### Linked list

[TOC]

#### Remove Duplicates from Sorted List

------

##### Problem description

Given a sorted linked list, delete all duplicates such that each element appear only *once*.
**Example 1:**

```
Input: 1->1->2
Output: 1->2
```

**Example 2:**

```
Input: 1->1->2->3->3
Output: 1->2->3
```

##### Algorithm description and certification

采用两个指针 ptr_first, ptr_second, 其中 ptr_first 指向刚加入到结果 list 当中的元素；然后通过移动 ptr_second 使其指向下一个应当要加入到结果 list 当中的元素。

##### Code

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        // special case
        if (head == NULL) return head;
        
        // At least one node is valid
        ListNode* ptr_second = head;
        ListNode* ptr_first = ptr_second;
        while (ptr_first != NULL){ 
            // Find a different one or the tail
            while (ptr_second != NULL && ptr_first->val == ptr_second->val) 
                ptr_second = ptr_second->next;
            ptr_first->next = ptr_second; // add the second pointer into linked list
            ptr_first = ptr_second; // move the first pointer to 
        }
        
        //
        return head;
    }
};
```

##### Reference

[Leetcode 83](https://leetcode.com/problems/remove-duplicates-from-sorted-list/description/)



#### Remove Duplicates from Sorted List II

------

##### Problem description

Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only *distinct* numbers from the original list.
**Example 1:**

```
Input: 1->2->3->3->4->4->5
Output: 1->2->5
```

**Example 2:**

```
Input: 1->1->1->2->3
Output: 2->3
```

##### Algorithm description and certification

与前一题类似，仍然采用两个指针。ptr_valid 始终指向有效的元素；ptr_check 始终指向待检查的元素。对于任意一个待检查的元素，若其不等于其前驱以及后继，那么这个元素即为有效元素，从而转化为 有效元素，并且加入到 结果当中。但是，为了方便处理，可以在最开头的地方加入一个哨兵元素。

##### Code

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        // Special case
        if(head == NULL) return head;
        
        // Get the valid ele
        ListNode* guard = new ListNode(head->val - 1); // not the same val
        ListNode* ptr_check = head;
        ListNode* ptr_valid = guard;
        int last_val = head->val - 1; // the val of precursor
        while (ptr_check != NULL){            
            while (ptr_check != NULL && (ptr_check->val == last_val ||
                   (ptr_check->next != NULL && ptr_check->next->val == ptr_check->val))){
                last_val = ptr_check->val;
                ptr_check = ptr_check->next;
            }
            
            // ptr_check is NULL or valid element
            ptr_valid->next = ptr_check;
            ptr_valid = ptr_check;
            if (ptr_check != NULL){
                last_val = ptr_check->val;
                ptr_check = ptr_check->next;
            }                   
        }
        
        head = guard->next;
        delete guard; // release the memory
        return head;
    }
};
```

##### Reference

[Remove Duplicates from Sorted List II](https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/description/)



#### Partition List

------

##### Problem description

Given a linked list and a value *x*, partition it such that all nodes less than *x* come before nodes greater than or equal to *x*.You should preserve the original relative order of the nodes in each of the two partitions.
**Example:**

```
Input: head = 1->4->3->2->5->2, x = 3
Output: 1->2->2->4->3->5
```

##### Algorithm description and certification

设 head 为输入链表的头结点，输入的值为 x；由于要保证相对顺序的稳定性，不妨将原先的输入链表拆分为两个链表，分别为： {list_less: head_less, tail_less}, {list_geq: head_geq, tail_geq}，其中 head 表示头结点，tail 表示尾节点，less 表示小于 x 的元素所组成的链表，geq 表示大于等于 x 的元素所组成的链表；那么有如下的伪代码：

```cpp
// special case
if (head == NULL) return head;

// Divide the original list into two parts
while (head != NULL)
    if (head->val >= x) list_geq.add(head);
	else list_less.add(head);
	head = head->next;

// Merge the two list
tail_less->next = head_geq;
return head_less;
```

为了确保一些边界条件更加容易处理，可以在初始化时，将 list_less, list_geq 均放置一个哨兵节点，如以下code所示。

##### Code

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        // special case
        if (head == NULL) return head;

        // Divide the original list into two parts
        ListNode *head_less = new ListNode(0);
        ListNode *tail_less = head_less;
        ListNode *head_geq = new ListNode(0);
        ListNode *tail_geq = head_geq;        
        while (head != NULL){
            if (head->val >= x){
                tail_geq->next = head;
                tail_geq = tail_geq->next;
            }
            else{
                tail_less->next = head;
                tail_less = tail_less->next;
            }
            
            ListNode *tmp = head->next;
            head->next = NULL;
            head = tmp;
        }

        // Merge the two list
        tail_less->next = head_geq->next;
        ListNode *res = head_less->next;
        delete head_less;
        delete head_geq;
        return res;
    }
};
```

##### Reference

[Partition list](https://leetcode.com/problems/partition-list/description/)



#### Add Two Numbers

------

##### Problem description

You are given two **non-empty** linked lists representing two non-negative integers. The digits are stored in **reverse order** and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

**Example**

```
Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
Explanation: 342 + 465 = 807.
```

##### Algorithm description and certification

相对比较简单的一个题，值得注意的是：

1. 将初始的 carry(进位) 设为 0，从而不需要考虑初始化时没有carry 的问题；
2. 在 while 循环当中一直往后加，直到 carry = 0, l1, l2 为空，从而简化边界条件；
3. 在初始化 res 时，加入一个哨兵节点，但是务必记得 后面需要释放内存；

##### Code

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* res = new ListNode(0); ;
        ListNode* adder = res; 
        int carry = 0;
        while (carry != 0 || l1 != NULL || l2 != NULL){      
            // add the number and save it into result
            int val1 = (l1 != NULL ? l1->val : 0);
            int val2 = (l2 != NULL ? l2->val : 0);
            adder->next = new ListNode((carry + val1 + val2) % 10);  
            adder = adder->next;
                        
            // Update the status: carry, l1, l2
            carry = (carry + val1 + val2) / 10;
            l1 = (l1 != NULL ? l1->next : NULL);
            l2 = (l2 != NULL ? l2->next : NULL);
        }
        
        adder = res->next;
        delete res;
        return adder;        
    }
};
```

##### Reference

[Add Two Numbers](https://leetcode.com/problems/add-two-numbers/description/)



#### Remove Nth Node From End of List

------

##### Problem description

Given a linked list, remove the nth node from the end of list and return its head.

The minimum number of nodes in list is *n*.

Have you met this question in a real interview?  Yes

**Example**

Given linked list: `1->2->3->4->5->null`, and *n* = `2`.

After removing the second node from the end, the linked list becomes `1->2->3->5->null`.

**Challenge**

Can you do it without getting the length of the linked list?

##### Algorithm description and certification

直接使用快慢指针来解。其中，快指针 比 慢指针快 (n+1)步，因此我们加入一个哨兵节点。

##### Code

```cpp
/**
 * Definition of singly-linked-list:
 * class ListNode {
 * public:
 *     int val;
 *     ListNode *next;
 *     ListNode(int val) {
 *        this->val = val;
 *        this->next = NULL;
 *     }
 * }
 */

class Solution {
public:
    /**
     * @param head: The first node of linked list.
     * @param n: An integer
     * @return: The head of linked list.
     */
    ListNode * removeNthFromEnd(ListNode * head, int n) {
        // write your code here
        if (head == NULL) return head;
        
        // move the slow and find the pos
        ListNode* dummy = new ListNode(0);        
        ListNode* fast = dummy;
        ListNode* slow = dummy;
        dummy->next = head;
        for (; n >= 0; n--) fast = fast->next; // move n+1 step
        while (fast != NULL){
            fast = fast->next;
            slow = slow->next;
        }
        
        // slow is pointed to the precursor of the deleted ele
        slow->next = slow->next->next;
        slow = dummy->next;
        delete dummy;
        return slow;
    }
};
```

##### Reference

[Remove Nth Node From End of List](https://www.lintcode.com/problem/remove-nth-node-from-end-of-list/description)



#### Linked List Cycle

------

##### Problem description

Given a linked list, determine if it has a cycle in it.

Follow up:
Can you solve it without using extra space?

##### Algorithm description and certification

典型的快慢指针问题，只需要快指针每次移动两步，慢指针每次移动一步，若二者在某个时间相等，则有环；若一个指针到达末尾，则无环。

##### Code

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode *head) {
        // special case
        if (head == NULL) return false;
        
        // move the two pointer unless they met or arrive the end
        ListNode *fast = head->next;
        ListNode *slow = head;
        while (fast != NULL && slow != NULL){
            // two pointer meet at here
            if (fast == slow) return true;
            if (fast->next == NULL) return false; // reach the end
            
            // move the two pointer
            slow = slow->next;
            fast = fast->next->next;            
        }
        
        return false;
    }
};
```

##### Reference



#### Linked List Cycle II

------

##### Problem description

Given a linked list, return the node where the cycle begins. If there is no cycle, return `null`.

**Note:** Do not modify the linked list.

**Follow up**:
Can you solve it without using extra space?

##### Algorithm description and certification

1. 由于不确定链表当中是否含有环，因此最开始的采用快慢指针进行检测，若二者相遇，则表示有环 (采用与题 Linked List Cycle 一样的思路)； 
2. 如果链表当中有环，那么如何找到这个环的起点 ？

假设这个链表如下图所示，其组成环的节点个数为 $Y$，除了环以外的链表节点个数为 $X$。那么在第一步进行有环检测时，第一个指针每次移动两步，第二个指针每次移动一步，待二者相交后，设第二个指针一共移动了 $t$ 步；那么有：

$$
2t = X + k_1Y + \delta
$$

$$
t = X + k_2Y + \delta
$$

联立上述两式，可得：
$$
X + \delta = (k_1 - 2k_2) Y
$$
而且，当两个指针相交后，二者对于 环的初始节点 的距离为 $\delta$，所以，此时我们将第二个指针移至链表头结点，然后两个指针每次均移动一步，当二者再次相交时，即为要寻找的 环的初始节点。

![Linked_List_Cycle_II](/home/wangdefa/Desktop/Linked_List_Cycle_II.png)

其伪代码如下：

```cpp
// Initialize the two pointer
if (head == NULL) return NULL;
slow = fast = head;

// Find the first point of intersection
do{
    if (fast == NULL || fast->next == NULL) return NULL; // don't have cycle
	fast = fast->next->next;
	slow = slow->next;
}while (fast != slow);

// Find the second point of intersection
slow = head;
while (slow != fast)
    slow = slow->next;
	fast = fast->next;

// return the result
return fast;	
```

##### Code

```cpp
// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
  public:
    ListNode *detectCycle(ListNode *head) {
        // Initialize the two pointer
        ListNode *slow = head;
        ListNode *fast = head;

        // Find the first point of intersection
        do {
            if (fast == NULL || fast->next == NULL) return NULL; // don't have cycle
            fast = fast->next->next;
            slow = slow->next;
        } while (fast != slow);

        // Find the second point of intersection
        slow = head;
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }

        // return the result
        return fast;
    }
};
```

在代码的第 17~21 行，选择采用 do-while 循环，因为在最开头的时候，fast 与 slow 相等，这个相交点需要进行排除。

##### Reference

[Linked List Cycle II](https://leetcode.com/problems/linked-list-cycle-ii/description/)

[博客：水中的鱼](http://fisherlei.blogspot.com/2013/11/leetcode-linked-list-cycle-ii-solution.html)



#### Reverse Linked List

Reverse a singly linked list.

**Example:**

```
Input: 1->2->3->4->5->NULL
Output: 5->4->3->2->1->NULL
```

**Follow up:**

A linked list can be reversed either iteratively or recursively. Could you implement both?

##### Algorithm description and certification

题目比较简单，定义 $precursor$ 始终指向已经翻转部分的头结点；$head$ 始终指向当前需要进行翻转的节点；$successor$ 作为一个中间节点，主要作用是：保持 head 的下一个节点，防止链表断裂后无法连接。

##### Code

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* precursor = NULL;
        ListNode* successor = NULL;
        while (head != NULL){
            successor = head->next;
            head->next = precursor;
            precursor = head;
            head = successor;
        }
        return precursor;
    }
};
```

##### Reference

[Reverse Linked List](https://leetcode.com/problems/reverse-linked-list/description/)



#### Reverse Linked List II

Reverse a linked list from position *m* to *n*. Do it in one-pass.

**Note:** 1 ≤ *m* ≤ *n* ≤ length of list.

**Example:**

```
Input: 1->2->3->4->5->NULL, m = 2, n = 4
Output: 1->4->3->2->5->NULL
```

##### Algorithm description and certification

与 Reverse Linked List 这个题目类似，但是现在加上了翻转区间这一个限制；很自然让人联想到的方法为：

1. 记录前一段不需要翻转节点当中的 头结点 ($dummy$) 与尾节点 $(tail\_front$)；
2. 翻转需要翻转的这一段区域，记录这段这翻转区域的头结点 $(mid\_head$) 与尾节点 $(mid\_tail)$；同时记录 后一段不需要翻转的头结点 $(head\_back$)；
3. 拼接这三段链表，使之成为一个完整的链表；

需要注意，由于 m, n 的限制，在原链表当中可能找不到 $tail\_front$， 此时可以引入一个 dummy 的头结点；

伪代码大致如下：

```cpp
tail_front->next = dummy->next = head; // set a dummy node

// move the tail_front to a appropriate position
for i = [1, m)
    tail_front = tail_front->next;

// Reverse
tail_mid = tail_front->next;
head_mid = tail_mid;
head_back = Reverse(head_mid, n -m + 1); // reverse from the tail_mid, n-m+1 element

// list cat
tail_front->next = head_mid;
tail_mid->next = head_back;
return dummy->next;
```

##### Code

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        ListNode node(0);
        ListNode* dummy = &node; // dummy head
        ListNode* tail_front = dummy; // the tail of the front part
        dummy->next = head;
        
        // move the front_tail to it's own position
        for (size_t offset = 1; offset < m; offset++){
            tail_front = tail_front->next;
        }
        
        // reverse the mid part
        ListNode* tail_mid = tail_front->next;
        ListNode* reverse_node = tail_mid;
        ListNode* precursor = NULL;
        ListNode* successor = NULL;
        for (size_t offset = 0; offset < n - m + 1; offset++){
            successor = reverse_node->next;
            reverse_node->next = precursor;
            precursor = reverse_node;
            reverse_node = successor;
        }
        
        // ping jie
        tail_front->next = precursor;
        tail_mid->next = reverse_node;
        return dummy->next;
    }
};
```

##### Reference

[Reverse Linked List II](https://leetcode.com/problems/reverse-linked-list-ii/description/)



#### Merge Two Sorted List

Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists.

**Example:**

```
Input: 1->2->4, 1->3->4
Output: 1->1->2->3->4->4
```

##### Algorithm description and certification

这个题目比较简单，不再进行讲解；值得注意的是在处理跟链表有关的边界条件时，加上一个 dummy 的头结点，总是可以使得边界的处理更加简单。

##### Code

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode tmp(0);
        ListNode* dummy = &tmp; // used to point to the next valid node
        ListNode* res_head = dummy; // used to save the head of the res
        
        // Merge the two list until one of them is empty
        while (l1 != NULL && l2 != NULL){
            if (l1->val > l2-> val){
                dummy->next = l2;
                l2 = l2->next;
            }
            else{
                dummy->next = l1;
                l1 = l1->next;
            }   
            dummy = dummy->next;
        }
        
        // Merge the rest of the list
        if (l1 == NULL) dummy->next = l2;
        else dummy->next = l1;
        
        return res_head->next;
    }
};
```

##### Reference

[Merge Two Sorted List](https://leetcode.com/problems/merge-two-sorted-lists/description/)



#### Merge K Sorted List 

Merge *k* sorted linked lists and return it as one sorted list. Analyze and describe its complexity.

**Example:**

```
Input:
[
  1->4->5,
  1->3->4,
  2->6
]
Output: 1->1->2->3->4->4->5->6
```

##### Algorithm description and certification

对于这个题，有如下几种比较常见的思路，第一种为：每次从待合并的 链表堆(这里用于表示多个链表) 当中拿出两个链表做merge，然后将结果放回到 链表堆 当中，一直到链表堆当中仅仅含有一个链表；第二种思路为：采用二分法，将原来的链表堆分为两个链表堆，然后对两个链表堆分别做合并，最后对二者的结果做合并即可；第三种思路为：从每个链表当中取出一个元素 (若链表为空，则不取) 建立一个最小堆，将堆首元素放入结果当中，并且将其所属的 list 的下一个节点插入堆当中 (如果存在)，反复进行，一直到堆为空。

设原链表堆当中共含有 $k$ 个链表，每个链表的长度为 $l$;

**逐 list 合并**

第一次对两个链表的做合并的时间复杂度为： $\Theta(2l)$
第二次合并时，其中一个链表的长度为 $2l$，合并的时间复杂度为：$\Theta(3l)$
...
第 k - 1 次合并时，合并的时间复杂度为： $\Theta (kl)$
将上述的 k-1 次合并的时间进行汇总，得到整体的合并时间复杂度为：$\Theta(\sum_{i=2}^{k} i \times l) = \Theta(k^2l)$

**二分法**

采用二分法进行合并时，其边界条件是：链表堆当中仅含有一个或者两个链表，此时可以直接返回或者直接调用合并两个链表的逻辑；假设 $k=2^t$；

在第一次合并当中，共有 $2^{t-1}$组链表需要进行合并，每个链表的长度为 $l$；时间复杂度为： $(2\Theta^{t-1} \times l)$；
在第二次合并当中，共有 $2^{t-2}$组链表需要进行合并，每个链表的长度为 $2l$；时间复杂度为： $(\Theta 2^{t-2} \times 2l)=\Theta (2^{t-1} \times l)$
......
在第 t 次合并当中，共有 $2^0$ 组链表需要进行合并，每个链表的长度为 $2^{t-1} \times l$；时间复杂度为： $(2\Theta^{t-1} \times l)$；
将上述的 t 次合并的时间进行汇总，得到整体的合并时间复杂度为：$\Theta(2^{t-1} \times lt) = \Theta(l \times k\lg k)$；

二分法的伪代码如下：

```cpp
// Merge the list of lists[first, last)
MergeKSortedList(vector<ListNode*>& lists>, first, last)
    // Special case
    if (last == first) return NULL;
	if (last == first + 1) return lists[first];
	if (last == first + 2) return MergeTwoSortedList(lists[first], lists[first + 1]);

	// divide and conquer
	mid = first + ((last - first + 1) >> 1);
	ListNode* l1 = MergeKSortedList(lists, first, mid);
	ListNode* l2 = MergeKSortedList(lists, mid, last);
	return MergeTwoSortedList(l1, l2);
```

**最小堆**

由于 堆 的大小为 k，那么建 堆 的时间复杂度为： $\Theta(k)$；
对于所有的元素，都会有插入到堆，从堆中取出这两个操作，时间复杂度为: $\Theta(\lg k)$；
因此整个的时间复杂度为：$O(l \times k \lg k)$；空间复杂度为：$O(k)$；

```cpp
// Build the heap
for i = 1 : k
	if lists[i] != NULL
		heap.push_back(lists[i]);

// Get the minimum element and insert into the res
dummy = move_ptr;
while (!heap.empty())
    min = heap.GetMin();
	heap.erase();
	if (min->next != NULL)
        heap.insert(min->next);
	move_ptr->next = min;
move_ptr->next = NULL;
return dummy->next;
```

##### Code

**二分法**

```cpp
// Merge Two sorted list into one with the order kept
ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
    ListNode tmp(0);
    ListNode *dummy = &tmp;     // used to point to the next valid node
    ListNode *res_head = dummy; // used to save the head of the res

    // Merge the two list until one of them is empty
    while (l1 != NULL && l2 != NULL) {
        if (l1->val > l2->val) {
            dummy->next = l2;
            l2 = l2->next;
        }
        else {
            dummy->next = l1;
            l1 = l1->next;
        }
        dummy = dummy->next;
    }

    // Merge the rest of the list
    if (l1 == NULL)
        dummy->next = l2;
    else
        dummy->next = l1;

    return res_head->next;
}

// Merge k sorted list into one with the order kept
ListNode *mergeKLists(std::vector<ListNode *> &lists, uint32_t first, uint32_t last) {
    // Special case
    if (last == first) return NULL;
    if (last == first + 1) return lists[first];
    if (last == first + 2) return mergeTwoLists(lists[first], lists[first + 1]);

    // divide and conquer
    uint32_t mid = first + ((last - first + 1) >> 1);
    ListNode *l1 = mergeKLists(lists, first, mid);
    ListNode *l2 = mergeKLists(lists, mid, last);
    return mergeTwoLists(l1, l2);
}

ListNode *mergeKLists(std::vector<ListNode *> &lists){
    return mergeKLists(lists, 0, lists.size());
}
```

**最小堆**

```cpp
ListNode *mergeKLists(std::vector<ListNode *> &lists) {
    // Build the min heap
    std::vector<ListNode *> heap;
    for (size_t i = 0; i < lists.size(); i++) {
        if (lists[i] != NULL) heap.push_back(lists[i]);
    }
    auto cmp = [](ListNode *x, ListNode *y) { return x->val > y->val; };
    std::make_heap(heap.begin(), heap.end(), cmp);

    // Get the minimum element and insert into the res
    ListNode tmp(0);
    ListNode *dummy = &tmp;
    ListNode *move_ptr = &tmp;
    while (!heap.empty()) {
        // Get the minimum number and insert into the res
        ListNode *min = heap.front();
        move_ptr->next = min;
        move_ptr = move_ptr->next;

        // update the heap
        std::pop_heap(heap.begin(), heap.end(), cmp);
        heap.pop_back();
        if (min->next != NULL) {
            heap.push_back(min->next);
            std::push_heap(heap.begin(), heap.end(), cmp);
        }
    }

    // Add the end signal
    move_ptr->next = NULL;
    return dummy->next;
}
```

##### Reference

[Merge K Sorted Lists](https://leetcode.com/problems/merge-k-sorted-lists/description/)



#### Reorder List

Given a singly linked list *L*: $L_0→L_1→…→L_{n-1}→L_n$,
reorder it to: $L_0→L_n→L_1→L_{n-1}→L_2→L_{n-2}→…$

You may **not** modify the values in the list's nodes, only nodes itself may be changed.

**Example 1:**

```
Given 1->2->3->4, reorder it to 1->4->2->3.
```

**Example 2:**

```
Given 1->2->3->4->5, reorder it to 1->5->2->4->3.
```

##### Algorithm description and certification

设原链表的长度为 $n$；若用下标表示最终结果，那么结果是：$0 \to n \to 1 \to (n-1) \to 2 \to (n-2) ...$，这里比较困难的点在于链表的后半部分在 往前移动 的时候，每次移动的时间复杂度为：$O(n)$；因此可以考虑将后半部分链表独立出来，然后进行翻转；最后，将前半部分链表与后半部分链表合并即可得到结果。

1. 获取链表长度 $n$；
2. 将链表分为两个链表，下标范围分别为：$[0, \frac {n+1} {2}), [\frac {n+1} {2}, n)$；
3. 对后半部分链表 $[\frac {n+1} {2}, n)$ 进行反转，并且记录表头；
4. 从头到尾，每次取出前半部分的一个节点，后半部分的一个结果，从而将两个链表 合并；
5. 若前半部分链表仍然还有元素没有加入到结果当中，将其加入到结果当中；
6. 将末元素的 next 指向 NULL;

##### Code

```cpp
void reorderList(ListNode *head) {
    // Get the size of the original list
    uint32_t length = 0;
    for (ListNode *mover = head; mover != NULL; mover = mover->next)
        length++;
    if (length <= 1) return;

    // Split the list into two separate list
    ListNode *head1 = head;
    ListNode *head2 = head;
    uint32_t mid = (length + 1) >> 1;
    for (uint32_t i = 1; i < mid; i++)
        head2 = head2->next; // move to the
    ListNode *tail1 = head2;
    head2 = head2->next;
    tail1->next = NULL;

    // Reverse the second part of the list
    ListNode *pre = NULL;
    ListNode *now = head2;
    ListNode *next = NULL;
    while (now != NULL) {
        next = now->next;
        now->next = pre;
        pre = now;
        now = next;
    }
    head2 = pre;

    // Merge the two list
    head = new ListNode(0);
    ListNode *mover = head;
    while (head1 != NULL || head2 != NULL){
        if (head1 != NULL){
            mover->next = head1;
            mover = mover->next;
            head1 = head1->next;
        }
        if (head2 != NULL){
            mover->next = head2;
            mover = mover->next;
            head2 = head2->next;
        }
    }
    mover->next = NULL;

    // return the result
    mover = head->next;
    delete head;
    head = mover;
}
```

##### Reference

[Reorder List](https://leetcode.com/problems/reorder-list/description/)



#### Copy List with Random Pointer

A linked list is given such that each node contains an additional random pointer which could point to any node in the list or null.

Return a **deep copy** of the list.

##### Algorithm description and certification

一个有点点技巧的题目，可以达到空间复杂度为： $O(1)$；时间复杂度为：$O(n)$；具体解题思路可以参考[这里](https://leetcode.com/problems/copy-list-with-random-pointer/discuss/)

##### Code

```cpp
// 略
```



#### Sort List 

Sort a linked list in *O*(*n* log *n*) time using constant space complexity.

**Example 1:**

```
Input: 4->2->1->3
Output: 1->2->3->4
```

**Example 2:**

```
Input: -1->5->3->4->0
Output: -1->0->3->4->5
```

##### Algorithm description and certification

典型的MergeSort；

##### Code

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        return MergeSort(head);
    }
    ListNode* MergeSort(ListNode* head) {
        // special case
        if (head == NULL || head->next == NULL) return head;
        
        // divide and solve
        ListNode* fast = head;
        ListNode* slow = head;
        while (fast != NULL && fast->next != NULL && fast->next->next != NULL){
            fast = fast->next->next;
            slow = slow->next;
        }
        assert(slow != NULL && slow->next != NULL);
        ListNode* head1 = slow->next; // the other list
        slow->next = NULL; 
        head = MergeSort(head);
        head1 = MergeSort(head1);
        
        // merge the result
        ListNode tmp(0);
        ListNode* dummy_res = &tmp;
        ListNode* mover = dummy_res;
        while (head != NULL || head1 != NULL){
            // one of them is empty
            if (head == NULL){
                mover->next = head1; break;
            }
            else if (head1 == NULL){
                mover->next = head; break;
            }
            
            // all have nodes
            mover->next = (head->val > head1->val ? head1 : head);
            mover = mover->next;
            head->val > head1->val ? head1=head1->next : head=head->next;
        }
        return dummy_res->next;    
    }
};
```

##### Reference

[Sort Lists](https://leetcode.com/problems/sort-list/description/)



#### Insert Sort

Sort a linked list using insertion sort.


![img](https://upload.wikimedia.org/wikipedia/commons/0/0f/Insertion-sort-example-300px.gif)
A graphical example of insertion sort. The partial sorted list (black) initially contains only the first element in the list.
With each iteration one element (red) is removed from the input data and inserted in-place into the sorted list


**Algorithm of Insertion Sort:**

1. Insertion sort iterates, consuming one input element each repetition, and growing a sorted output list.
2. At each iteration, insertion sort removes one element from the input data, finds the location it belongs within the sorted list, and inserts it there.
3. It repeats until no input elements remain.

##### Algorithm description and certification

简单的插入排序，不再说明；

##### Code

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* insertionSortList(ListNode* head) {
        ListNode* dummy_head = new ListNode(0);
        dummy_head->next = NULL;
        
        while (head != NULL){
            ListNode* pre = find(dummy_head, head->val);
            ListNode* successor = pre->next;
            pre->next = head;
            head = head->next;
            pre->next->next = successor;            
        }
        head = dummy_head->next;
        delete dummy_head;
        return head;
    }
    
    ListNode* find(ListNode* dummy_head, int x) {
        assert(dummy_head != NULL);
        while (dummy_head->next != NULL && dummy_head->next->val <= x) 
            dummy_head = dummy_head->next;
        return dummy_head;
    }
};
```

##### Reference

[Insert sort](https://leetcode.com/problems/insertion-sort-list/description/)



#### Palindrome Linked List

Given a singly linked list, determine if it is a palindrome.

**Example 1:**

```
Input: 1->2
Output: false
```

**Example 2:**

```
Input: 1->2->2->1
Output: true
```

**Follow up:**
Could you do it in O(n) time and O(1) space?

##### Algorithm description and certification

与Reorder List 这道题类似，可以将后半部分链表进行翻转，然后进行比较；在完成后，再将链表翻转回来。

##### Code

##### Reference



#### LRU cache

Design and implement a data structure for [Least Recently Used (LRU) cache](https://en.wikipedia.org/wiki/Cache_replacement_policies#LRU). It should support the following operations: `get` and `put`.

`get(key)` - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
`put(key, value)` - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.

**Follow up:**
Could you do both operations in **O(1)** time complexity?

**Example:**

```
LRUCache cache = new LRUCache( 2 /* capacity */ );

cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // returns 1
cache.put(3, 3);    // evicts key 2
cache.get(2);       // returns -1 (not found)
cache.put(4, 4);    // evicts key 1
cache.get(1);       // returns -1 (not found)
cache.get(3);       // returns 3
cache.get(4);       // returns 4
```

##### Algorithm description and certification

鉴于每次 get 或者 put 操作都会将涉及到在 $O(1)$ 时间内将元素的优先级调至最高，因此可以考虑用一个链表来实现优先级的调整；在每次操作一个元素后，将元素移动至 链表的第一个元素。在此，将每个元素移动到 链表第一个元素时，涉及到在 $O(1)$ 时间内的删除以及插入操作，因此考虑采用双向队列。最后，为了通过 $key$ 在 $O(1)$ 时间内获取元素，可以使用 hash table 建立 key 到具体元素之间的映射关系。

对于 Get 操作：

1. 用 $key$ 在 hash table 当中进行检索；
2. 若没有检索到，直接返回 -1；
3. 否则，将元素移动至双向链表的第一个元素（注意：此次操作可能会引起 tail 节点的更改），将元素值返回。

对于 Put 操作：

1. 在 hash table 当中进行检索，若检索到，类似 Get 更改其优先级；
2. 否则，若当前 cache 空间已满，删除 tail 元素，更新 tail 节点，更新链表长度 size；
3. 新建链表节点，将其作为 双向链表的头结点，更新 tail 节点，更新链表长度 size。

##### Code

```cpp
// Realize the LRU(least recently used cache)
struct ListDoubleNode {
    int val;
    int key;
    ListDoubleNode *pre;
    ListDoubleNode *next;
    ListDoubleNode(int k, int v) : val(v), key(k), pre(NULL), next(NULL) {}
    void Remove() {
        // Release the space will be exec in the call function
        assert(this != NULL && pre != NULL);
        if (next != NULL) next->pre = pre;
        pre->next = next;
    }
    void Insert(ListDoubleNode *precursor) {
        // insert this node behind the precursor
        assert(precursor != NULL);
        if (precursor->next != NULL) precursor->next->pre = this;
        this->next = precursor->next;
        precursor->next = this;
        this->pre = precursor;
    }
};
class LRUCache {
  public:
    LRUCache(int capacity) {
        size = 0;
        capa = capacity;
        dummy = new ListDoubleNode(0, 0);
        tail = dummy;
    }

    int get(int key) {
        if (list_table.find(key) == list_table.end()) return -1;

        // get the value and update the priority
        ListDoubleNode *node = list_table.find(key)->second;
        SetHighestPriority(node);
        return node->val;
    }

    void put(int key, int value) {
        // assert the illegal case
        assert(capa > 0);

        // already have this value, only update the value and priority
        if (list_table.find(key) != list_table.end()) {
            ListDoubleNode *node = list_table.find(key)->second;
            node->val = value; // update the value
            SetHighestPriority(node);
            return;
        }

        // Insert the node into LRU cache
        if (size == capa) {
            // remove the least used element here
            ListDoubleNode *node = tail->pre;
            list_table.erase(list_table.find(tail->key)); // remove the LRU element from table
            tail->Remove();
            delete tail;
            tail = node;
            size--;
        }
        ListDoubleNode *node = new ListDoubleNode(key, value);
        if (tail == dummy) tail = node; // update the tail if needed
        node->Insert(dummy);
        list_table[key] = node;
        size++;
    }

  protected:
    void SetHighestPriority(ListDoubleNode *node) {
        // node is the tail, the pre of the node is not dummy
        if (node == tail && node->pre != dummy) tail = node->pre;
        node->Remove();
        node->Insert(dummy);
    }

  private:
    std::unordered_map<int, ListDoubleNode *> list_table;
    ListDoubleNode *dummy; // dummy_head, use to update the priority
    ListDoubleNode *tail;  // tail, used to delete the LRU ele
    int size;
    int capa;
};
```

##### Reference

[LRU cache](https://leetcode.com/problems/lru-cache/description/)

For more concise C++ solution, you can also refer to [here](https://leetcode.com/problems/lru-cache/discuss/45912/Clean-Short-Standard-C++-solution-NOT-writing-C-in-C++-like-all-other-lengthy-ones)

