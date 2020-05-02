#ifndef BIN_TREE_DICTIONARY
#define BIN_TREE_DICTIONARY

#include "IDictionary.hpp"
#include "UnorderedBinaryTree.hpp"

class BinTreeDictionary : public IDictionary {
    UnorderedBinaryTree<std::string> _dictionary;

public:
    void add(std::string const &word) {
        _dictionary.addNewElement(word);
    }

    bool check(std::string const &word) {
        return _dictionary.isInTree(word);
    }

    std::string getNameOfStructure() {
        return "BinTreeDictionary";
    }

    virtual ~BinTreeDictionary() {}
};

#endif