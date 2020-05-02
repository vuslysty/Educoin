#ifndef MY_HASH_TABLE_DICTIONARY
#define MY_HASH_TABLE_DICTIONARY

#include "IDictionary.hpp"
#include "HashTable.hpp"

class MyHashTableDictionary : public IDictionary {
    HashTable   _dictionary;

public:

    MyHashTableDictionary() : _dictionary(HashTable())
    {}

    void add(std::string const &word) {
        _dictionary.push(word);
    }

    bool check(std::string const &word) {
        return _dictionary.findElement(word) ? true : false;
    }

    std::string getNameOfStructure() {
        return "MyHashTableDictionary";
    }

    void print() const {
        _dictionary.print();
    }

    void sort() {
        _dictionary.sortTable();
    }

    virtual ~MyHashTableDictionary() {}
};

#endif