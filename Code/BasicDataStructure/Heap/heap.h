#include <queue>
#include <vector>
#include <iostream>
#include <iomanip> 
#include <fstream> 
#include "assert.h"
#include "stdint.h"
#include <time.h>
#include <functional>

template <class T>
class Heap 
{
    public:
        // use this to save the data of this heap 
        std::vector<T> heap;
        // use this to determine we will create min or max heap
        std::function<bool(T, T)> cmp; 

    public:
        // max or min heap will created
        Heap(std::function<bool(T, T)> cmp_func);
        // Floyd constructor
        Heap(typename std::vector<T>::iterator first, typename std::vector<T>::iterator last, 
            std::function<bool(T, T)> cmp_func);

        int32_t GetParent(int32_t index);
        int32_t GetLeftChild(int32_t index);
        int32_t GetRightChild(int32_t index);
        int32_t GetFirstInnerNode();
        void Insert(T data);
        bool Delete();
        T Get(); // Get the element of the top
        bool Empty(); // if the present heap is empty or not
        void Serilize();
        void Serilize(std::string file_name);
};

template <class T>
Heap<T>::Heap(std::function<bool(T, T)> cmp_func)
{
    // use this com_func to determine the max_heap or the min_heap
    cmp = cmp_func;
}
// Floyd constructor
template <class T>
Heap<T>::Heap(typename std::vector<T>::iterator first, typename std::vector<T>::iterator last, std::function<bool(T, T)> cmp_func)
{
    cmp = cmp_func; 
    heap.resize(last - first);
    std::copy(first, last, heap.begin());
    int32_t index = this->GetFirstInnerNode();
    Serilize();
    if (index == -1)
    {
        return; // There is no inner point
    }
    // Process the normal case
    for (; index != -1; index--)
    {
        int32_t index_copy = index;
        while(true)
        {
            // find an appropriate element to filter down
            int32_t valid_child = index_copy;
            if (this->GetLeftChild(index_copy) != -1 && cmp(heap[this->GetLeftChild(index_copy)], heap[valid_child]))
            {
                valid_child = this->GetLeftChild(index_copy);
            }
            if (this->GetRightChild(index_copy) != -1 && cmp(heap[this->GetRightChild(index_copy)], heap[valid_child]))
            {
                valid_child = this->GetRightChild(index_copy);
            }
            // swap the element if the condition met, or we will break
            if(valid_child != index_copy)
            {
                T tmp = heap[index_copy];
                heap[index_copy] = heap[valid_child];
                heap[valid_child] = tmp;
                index_copy = valid_child; // continue to down filter
                Serilize(); 
                std::cout << "Valid child: " << valid_child << std::endl;
            }
            else
            {
                break; // the down stream is over
            }                
        }
    }
}
template <class T>
int32_t Heap<T>::GetParent(int32_t index)
{
    assert(index >= 0);
    if (index == 0)
    {
        return -1; // this means this is the root, it does not have a parent
    }
    return (index - 1) >> 1;
}
template <class T>
int32_t Heap<T>::GetLeftChild(int32_t index)
{
    // If lager than the size, return -1
    assert(index >= 0);
    index = (index << 1) + 1;
    index = (index < heap.size() ? index : -1);
    return index;
}
template <class T>
int32_t Heap<T>::GetRightChild(int32_t index)
{
    // If lager than the size, return -1
    assert(index >= 0);
    index = (index << 1) + 2;
    index = (index < heap.size() ? index : -1);
    return index;
}
template <class T>
int32_t Heap<T>::GetFirstInnerNode()
{
    int32_t index = heap.size();
    if (index == 0)
    {
        return -1; // empty heap
    }
    return GetParent(heap.size() - 1);
}
template <class T>
void Heap<T>::Insert(T data)
{
    heap.push_back(data);
    int32_t index = heap.size() - 1;
    while(this->GetParent(index) != -1 && cmp(heap[index], heap[this->GetParent(index)]))
    {
        T tmp = heap[index];
        heap[index] = heap[this->GetParent(index)];
        heap[this->GetParent(index)] = tmp;
        index = this->GetParent(index);
    }
}
template <class T>
bool Heap<T>::Delete()
{
    // if the heap is empty, this function will return false
    if (heap.size() == 0)
    {
        return false; // the heap is empty, so the delete fails
    }
    if (heap.size() == 1)
    {
        heap.resize(0);
        return true;
    }
    // normal case
    heap[0] = heap[heap.size() - 1]; // move the last element to the head
    heap.resize(heap.size() - 1); // remove the last element
    int32_t index = 0;
    while(true)
    {
        // find an appropriate element to filter down
        int32_t valid_child = index;
        if (this->GetLeftChild(index) != -1 && cmp(heap[this->GetLeftChild(index)], heap[valid_child]))
        {
            valid_child = this->GetLeftChild(index);
        }
        if (this->GetRightChild(index) != -1 && cmp(heap[this->GetRightChild(index)], heap[valid_child]))
        {
            valid_child = this->GetRightChild(index);
        }
        // swap the element if the condition met, or we will break
        if(valid_child != index)
        {
            T tmp = heap[index];
            heap[index] = heap[valid_child];
            heap[valid_child] = tmp;
            index = valid_child;
        }
        else
        {
            break; // the down stream is over
        }                
    }
    return true;
}
template <class T>
T Heap<T>::Get()
{
    assert(!Empty());
    return heap.front();
}
template <class T>
bool Heap<T>::Empty()
{
    return heap.empty();
}
template <class T>
void Heap<T>::Serilize()
{
    for (auto data : heap)
    {
        std::cout << data.val << "\t";
    }
    std::cout << std::endl;      
}
template <class T>
void Heap<T>::Serilize(std::string file_name)
{
    // use the traverse level method to print the .dot file
    std::ofstream out(file_name + ".dot", std::ios::trunc);
    out << "digraph G{" << std::endl;

    // add the root node 
    uint32_t node_id = 0; // we will use this node id to create the graph
    std::queue<uint32_t> q_node;
    auto SerilizeNode = [&out](T node, uint32_t id)
    {
        out << "node[shape=record,style=filled,color=\"#a0522d\",fontcolor=white];" << std::endl;
        out << id << "[label=\"<f0> | <f1>" << node.val << "| <f2> \"];" << std::endl;
    };
    if (!Empty())
    {
        // print the head and add it into the queue
        SerilizeNode(heap.front(), node_id);
        q_node.push(node_id++);
    }
    while (!q_node.empty())
    {
        uint32_t id = q_node.front();
        q_node.pop();

        if (this->GetLeftChild(id) != -1)
        {
            SerilizeNode(heap[this->GetLeftChild(id)], node_id);
            out << id << ":f0:sw->" << node_id<< ":f1;" << std::endl;
            q_node.push(node_id++);
        }
        if (this->GetRightChild(id) != -1)
        {
            SerilizeNode(heap[this->GetRightChild(id)], node_id);
            out << id << ":f2:se->" << node_id<< ":f1;" << std::endl;
            q_node.push(node_id++);
        }
    }

    out << "}" << std::endl;
    out.close();
}