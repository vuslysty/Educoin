#ifndef _BINARY_TREE_H  // NOLINT
#define _BINARY_TREE_H

#include <iostream>
#include <sstream>

template <typename T>
class BinaryTree {  // NOLINT

  class Node {
   public:
    static unsigned int max_deep;

    T _data;
    unsigned int _counter;
    unsigned int _deep;
    Node *_left_node;
    Node *_right_node;

    Node(const T &n, unsigned int deep)
        : _data(n),
          _counter(1),
          _deep(deep),
          _left_node(nullptr),
          _right_node(nullptr) {
      if (deep > max_deep) {
        max_deep = deep;
      }
    }
  };

  Node *_root;

  void addNewElement(const T &elem, Node *node) {
    if (elem < node->_data) {
      if (node->_left_node) {
        addNewElement(elem, node->_left_node);
      } else {
        // NOLINTNEXTLINE
        node->_left_node = new Node(elem, node->_deep + 1);
      }

    } else if (elem > node->_data) {
      if (node->_right_node) {
        addNewElement(elem, node->_right_node);
      } else {
        // NOLINTNEXTLINE
        node->_right_node = new Node(elem, node->_deep + 1);
      }
    } else {
      node->_counter++;
    }
  }

  void delNode(Node **node) {
    if (node && *node) {
      if ((*node)->_left_node) {
        delNode(&(*node)->_left_node);
      }
      if ((*node)->_right_node) {
        delNode(&(*node)->_right_node);
      }
      delete *node;  // NOLINT
      *node = nullptr;
    }
  }

  void printElements(Node *node, std::stringstream *stream) const {
    if (node->_left_node) {
      printElements(node->_left_node, stream);
    }
    for (unsigned int i = 0; i < node->_counter; i++) {
      (*stream) << " " << node->_data;
    }
    if (node->_right_node) {
      printElements(node->_right_node, stream);
    }
  }

  bool isInTree(T const &elem, Node *node) const {
    if (node->_data == elem) {
      return true;
    } else if (node->_left_node && elem < node->_data) {  // NOLINT
      return isInTree(elem, node->_left_node);
    } else if (node->_right_node && elem > node->_data) {
      return isInTree(elem, node->_right_node);
    } else {
      return false;
    }
  }

 public:
  BinaryTree() : _root(nullptr) {}
  ~BinaryTree() { delNode(&_root); }

  void addNewElement(const T &elem) {
    if (_root == nullptr) {
      _root = new Node(elem, 0);  // NOLINT
    } else {
      addNewElement(elem, _root);
    }
  }

  std::string printElements() const {
    std::stringstream stream;  // NOLINT

    if (_root) {
      printElements(_root, &stream);
    } else {
      stream << " Empty";
    }

    std::string str = stream.str();
    return str.assign(str.begin() + 1, str.end());
  }

  bool isInTree(T const &elem) const {
    return _root ? isInTree(elem, _root) : false;
  }

  unsigned int getMaxDeep() const { return Node::max_deep; }
};

template <typename T>
unsigned int BinaryTree<T>::Node::max_deep = 0;

#endif