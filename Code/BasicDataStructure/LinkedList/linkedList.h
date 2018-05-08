#include<vector>
#include<stack>
#include <iostream>
#include <iomanip>
#include <string>
#include "assert.h"
#include "stdint.h"

struct Node
{    
    int32_t val;
    Node * next;
    Node(int32_t x) : val(x), next(nullptr){}
    Node(){}
};

class LinkedList 
{
    public:
        Node * head; // The head act as a gurad
        Node * tail;
        uint32_t size;

    public:
        LinkedList()
        {
            head = new Node(-1); // use it as a guard
            tail = head;
            size = 0;
        }

        void PushBack(int32_t val)
        {
            tail->next = new Node(val);
            tail = tail->next;
            size++;
        }

        int32_t PopBack()
        {
            // list is empty
            if (size == 0)
            {
                return -1;
            }

            // Move the ptr until the next is tail
            Node* tmp = head;
            while(tmp->next != tail)
            {
                tmp = tmp->next;
            }
            delete tail;
            tail = nullptr;

            // Update the tail and size
            tail = tmp;
            tail->next = nullptr;
            size--;
        }
        
        void Reverse()
        {
            // special case
            if (size == 0)
            {
                return;
            }

            // do the reverse of the list
            Node* first = head;
            Node* second = head->next;
            tail = second;
            while (second != nullptr)
            {
                Node* third = second->next;
                second->next = (first == head ? nullptr : first);
                first = second;
                second = third;
            }
            head->next = first;
        }

        bool HasCycle()
        {
            // use two pointer: move one step 
            //                  move two step
            Node* first = head->next;
            Node* second = head->next;
            while (true)
            {
                // first can move two step, second can move one step
                if (first != nullptr && first->next != nullptr && second != nullptr)
                {
                    first = first->next->next;
                    second = second->next;
                    if (first == second)
                    {
                        return true;
                    }
                }
                else 
                {
                    return false; // first have come to the end
                }
            }
        }

        void Serilize(std::string str)
        {
            Node* ptr = head->next;
            std::cout << str << ":\t";
            while (ptr != nullptr)
            {
                std::cout << ptr->val << "\t";
                ptr = ptr->next;
            }
            std::cout << std::endl;
        }
};

