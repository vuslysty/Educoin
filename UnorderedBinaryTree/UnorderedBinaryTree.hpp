#ifndef _BINARY_TREE_H  // NOLINT
#define _BINARY_TREE_H

#include <iostream>
#include <sstream>

template <typename T>
class UnorderedBinaryTree {  // NOLINT

  static size_t getHashSum(const std::string &src) {
      size_t h = 0;
      for (char c : src) {
          h = (h << 7) ^ (h >> 26) ^ static_cast<size_t>(c);
      }
      return h;
  }

  class Node {
   public:
    size_t _hash;
    Node *_left_node;
    Node *_right_node;

    explicit Node(size_t hash)
        : _hash(hash),
          _left_node(nullptr),
          _right_node(nullptr) {
    }
  };

  Node *_root;

  void addNewElement(size_t hash, Node *node) {
    if (hash < node->_hash) {
      if (node->_left_node) {
        addNewElement(hash, node->_left_node);
      } else {
        // NOLINTNEXTLINE
        node->_left_node = new Node(hash);
      }

    } else if (hash > node->_hash) {
      if (node->_right_node) {
        addNewElement(hash, node->_right_node);
      } else {
        // NOLINTNEXTLINE
        node->_right_node = new Node(hash);
      }
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

  bool isInTree(size_t hash, Node *node) const {
    if (node->_hash == hash) {
      return true;
    } else if (node->_left_node && hash < node->_hash) {  // NOLINT
      return isInTree(hash, node->_left_node);
    } else if (node->_right_node && hash > node->_hash) {
      return isInTree(hash, node->_right_node);
    } else {
      return false;
    }
  }

 public:
  UnorderedBinaryTree() : _root(nullptr) {}
  ~UnorderedBinaryTree() { delNode(&_root); }

  void addNewElement(const T &elem) {
    if (_root == nullptr) {
      _root = new Node(getHashSum(elem));  // NOLINT
    } else {
      addNewElement(getHashSum(elem), _root);
    }
  }

  bool isInTree(T const &elem) const {
    return _root ? isInTree(getHashSum(elem), _root) : false;
  }

};

#endif