#ifndef TRIE_DICTIONARY
#define TRIE_DICTIONARY

#include "IDictionary.hpp"
#include "Trie.hpp"

class TrieDictionary : public IDictionary {
    Trie _dictionary;

public:
    virtual void add(std::string const &word) {
        _dictionary.add(word);
    }

    virtual bool check(std::string const &word) {
        return _dictionary.check(word);
    }

    std::string getNameOfStructure() {
        return "MyTrieDictionary";
    }

    virtual ~TrieDictionary() {}
};

#endif