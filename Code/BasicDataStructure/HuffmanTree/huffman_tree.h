#include <vector>
#include <iostream>
#include <iomanip> 
#include <fstream> 
#include "assert.h"
#include "stdint.h"
#include <string>
#include <unordered_map>
#include "../Heap/heap.h"

class Node
{
    public:
        uint32_t node_id; // we will use it to search this node
        uint32_t freq; // the frequency of this word
        std::string val;
        Node* left;
        Node* right;
    
    public:
        Node(std::string word, uint32_t f, uint32_t id) : node_id(id), freq(f), val(word), left(nullptr), right(nullptr){}
        Node(){}
        Node(const Node& other)
        {
            node_id = other.node_id;
            freq = other.freq;
            val = other.val;
            left = other.left;
            right = other.right;
        }
        bool operator<(const Node& other) const
        {
            return freq < other.freq;
        }
};

class HuffmanTree 
{
    public:
        Node* m_root; // the huffman encoding tree
        std::unordered_map<std::string, uint32_t> m_input_freq; // word and frequency
        std::unordered_map<std::string, std::string> m_output_encoding; // word and it encoding

    public:
        HuffmanTree(std::unordered_map<std::string, uint32_t> input_freq);
        void Serilize(std::string file_name); // print huffman tree

    private:
        void DfsEncoding(Node* node, std::string encoding); // use bfs to do encoding for the huffman tree
        std::string GetEncoding(std::string);
};

HuffmanTree::HuffmanTree(std::unordered_map<std::string, uint32_t> input_freq)
{
    // special case
    if (input_freq.empty())
    {
        return;
    }

    // Create the priority queue, node_id search table, using the input word, frequency pairs
    std::vector<Node*> node_id_table;
    Heap<Node> p_queue([](Node first, Node second){return first < second;});
    uint32_t node_id= 0;
    for (auto pair : input_freq)
    { 
        Node* ptr = new Node(pair.first, pair.second, node_id++);
        node_id_table.push_back(ptr);
        p_queue.Insert(*ptr);
    }
    
    // continue to merge those nodes until there is one node
    while(p_queue.Size() >= 2) 
    {
        Node node1 = p_queue.Get();
        p_queue.Delete();
        Node node2 = p_queue.Get();
        p_queue.Delete();

        Node* ptr = new Node("", node1.freq + node2.freq, node1.node_id);
        ptr->left = node_id_table[node1.node_id];
        ptr->right = node_id_table[node2.node_id];
        p_queue.Insert(*ptr); // Insert the new node into heap
        node_id_table[ptr->node_id] = ptr; // update the node id table
    }
    m_root = node_id_table[p_queue.Get().node_id]; // update the root of the tree

    // Bfs encoding for the huffman tree
    DfsEncoding(m_root, "");
}
void HuffmanTree::DfsEncoding(Node* node, std::string encoding)
{
    // not the leaf node
    if (node->left != nullptr)
    {
        DfsEncoding(node->left, encoding + "0"); 
    }
    if (node->right != nullptr)
    {
        DfsEncoding(node->right, encoding + "1"); 
    }

    // the leaf node
    if (node->left == nullptr && node->right == nullptr)
    {
        m_output_encoding.insert(std::make_pair(node->val, encoding));
        return;
    }
}
std::string HuffmanTree::GetEncoding(std::string str)
{
    auto iter = m_output_encoding.find(str);
    if (iter != m_output_encoding.end())
    {
        return iter->second;
    }
    return ""; // not a leaf node
}
void HuffmanTree::Serilize(std::string file_name)
{
    // use the traverse level method to print the .dot file
    std::ofstream out(file_name + ".dot", std::ios::trunc);
    out << "digraph G{" << std::endl;

    // add the root node
    uint32_t node_id = 0;
    std::queue<Node*> q_node;
    std::queue<uint32_t> q_node_id;
    auto SerilizeNode = [&out](Node* node, uint32_t id, std::string encoding)
    {
        out << "node[shape=record,style=filled,color=\"#a0522d\",fontcolor=white];" << std::endl;
        if (encoding == "")
        {
            out << id << "[label=\"<f0> | <f1>" << node->val << "| <f2> \"];" << std::endl;
        }
        else
        {
            out << id << "[label=\"<f0> | <f1>" << 
            (node->val + " -- " + std::to_string(node->freq) + " -- " + encoding) << "| <f2> \"];" << std::endl;
        }
    };
    if (m_root != nullptr)
    {
        // print the head and add it into the queue
        SerilizeNode(m_root, node_id, GetEncoding(m_root->val));
        q_node.push(m_root);
        q_node_id.push(node_id++);
    }
    while (!q_node.empty())
    {
        Node* node = q_node.front();
        uint32_t id = q_node_id.front();
        q_node.pop();
        q_node_id.pop();

        if (node->left != nullptr)
        {
            SerilizeNode(node->left, node_id, GetEncoding(node->left->val));
            out << id << ":f0:sw->" << node_id<< ":f1;" << std::endl;
            q_node.push(node->left);
            q_node_id.push(node_id++);
        }
        if (node->right != nullptr)
        {
            SerilizeNode(node->right, node_id, GetEncoding(node->right->val));
            out << id << ":f2:se->" << node_id<< ":f1;" << std::endl;
            q_node.push(node->right);
            q_node_id.push(node_id++);
        }
    }

    out << "}" << std::endl;
    out.close();
}