#ifndef STD_HASH_TABLE_DICTIONARY
#define STD_HASH_TABLE_DICTIONARY

#include "IDictionary.hpp"
#include <unordered_set>

class StdHashTableDictionary : public IDictionary {
    std::unordered_set<std::string> _dictionary;

public:

    virtual void add(std::string const &word) {
        _dictionary.insert(word);
    }

    virtual bool check(std::string const &word) {
        return !(_dictionary.find(word) == _dictionary.end());
    }

    virtual std::string getNameOfStructure() {
        return "StdHashTableDictionary";
    }

    virtual ~StdHashTableDictionary() {}
};

#endif