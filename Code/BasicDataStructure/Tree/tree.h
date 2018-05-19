#include <time.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <queue>
#include "assert.h"
#include "stdint.h"

struct Node {
  int32_t val;
  Node* left;
  Node* right;
  Node* parent;
  Node(int32_t x) : val(x), parent(nullptr), left(nullptr), right(nullptr) {}
  Node() {}

  void InsertAsLeft(int32_t val) {
    this->left = new Node(val);
    this->left->parent = this;
  }

  void InsertAsRight(int32_t val) {
    this->right = new Node(val);
    this->right->parent = this;
  }
};

class Tree {
 public:
  Node* head;  // The head act as a gurad
  uint32_t max_size;
  enum TraverseMode {
    FIRST,   // root, left, right
    MIDDLE,  // left, root, right
    LAST     // left, right, root
  };

 public:
  Tree(uint32_t sz) {
    srand(time(NULL));
    max_size = sz;
    uint32_t max_val = 10 * sz;
    std::queue<Node*> q_node;
    head = new Node(rand() % max_val);
    q_node.push(head);  // push in the head first

    for (uint32_t index = 0; index < sz; index++) {
      Node* node = q_node.front();
      q_node.pop();

      // Insert the left child
      int32_t val = rand() % (max_val);
      if (rand() % 10 >= 2) {
        node->InsertAsLeft(val);
        q_node.push(node->left);
        // std::cout << val << " act as left child, parent is:" << node->val <<
        // std::endl;
      }

      // Insert the right child
      val = rand() % (max_val);
      if (rand() % 10 >= 1) {
        node->InsertAsRight(val);
        q_node.push(node->right);
        // std::cout << val << " act as right child, parent is:" << node->val <<
        // std::endl;
      }
    }
  }

  void Traverse(TraverseMode mode) {
    switch (mode) {
      case TraverseMode::FIRST:
        TraverseFirst(head);
        break;
      case TraverseMode::MIDDLE:
        TraverseMiddle(head);
        break;
      case TraverseMode::LAST:
        TraverseLast(head);
        break;
      default:
        assert(false);
    }
  }

  void TraverseFirst(Node* node) {
    if (node == nullptr) {
      return;
    }

    std::cout << node->val << "\t";
    TraverseFirst(node->left);
    TraverseFirst(node->right);
  }

  void TraverseMiddle(Node* node) {
    if (node == nullptr) {
      return;
    }
    TraverseMiddle(node->left);
    std::cout << node->val << "\t";
    TraverseMiddle(node->right);
  }

  void TraverseLast(Node* node) {
    if (node == nullptr) {
      return;
    }
    TraverseLast(node->left);
    TraverseLast(node->right);
    std::cout << node->val << "\t";
  }

  void Serilize(Node* root, std::string file_name) {
    // use the traverse level method to print the .dot file
    std::ofstream out(file_name + ".dot", std::ios::trunc);
    out << "digraph G{" << std::endl;

    // add the root node
    uint32_t node_id = 0;
    std::queue<Node*> q_node;
    std::queue<uint32_t> q_node_id;
    auto SerilizeNode = [&out](Node* node, uint32_t id) {
      out << "node[shape=record,style=filled,color=\"#a0522d\",fontcolor=white]"
             ";"
          << std::endl;
      out << id << "[label=\"<f0> | <f1>" << node->val << "| <f2> \"];"
          << std::endl;
    };
    if (head != nullptr) {
      // print the head and add it into the queue
      SerilizeNode(head, node_id);
      q_node.push(head);
      q_node_id.push(node_id++);
    }
    while (!q_node.empty()) {
      Node* node = q_node.front();
      uint32_t id = q_node_id.front();
      q_node.pop();
      q_node_id.pop();

      if (node->left != nullptr) {
        SerilizeNode(node->left, node_id);
        out << id << ":f0:sw->" << node_id << ":f1;" << std::endl;
        q_node.push(node->left);
        q_node_id.push(node_id++);
      }
      if (node->right != nullptr) {
        SerilizeNode(node->right, node_id);
        out << id << ":f2:se->" << node_id << ":f1;" << std::endl;
        q_node.push(node->right);
        q_node_id.push(node_id++);
      }
    }

    out << "}" << std::endl;
    out.close();
  }
};
