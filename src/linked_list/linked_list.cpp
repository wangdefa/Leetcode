#include "assert.h"
#include "stdint.h"
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode *detectCycle(ListNode *head) {
    // Initialize the two pointer
    if (head == NULL) return NULL;
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
    while (head1 != NULL || head2 != NULL) {
        if (head1 != NULL) {
            mover->next = head1;
            mover = mover->next;
            head1 = head1->next;
        }
        if (head2 != NULL) {
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

int main() {
    return 0;
}