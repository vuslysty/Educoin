#ifndef HASH_TABLE
#define HASH_TABLE

#include <vector>
#include <string>
#include <iostream>

#define DEF_SIZE 20

typedef std::pair<size_t, std::string> content_t;

class HashTable {
    size_t  _size{20};
    std::vector<std::vector<content_t> > _table;
    size_t  _count{0};


    static size_t getHashSum(const std::string &src);
public:

    HashTable();
    HashTable(size_t size);
    ~HashTable();

    void push(std::string const &str, bool enable_reapetes = true);
    void print() const;

    void sortTable();

    std::string const *findElement(std::string const &str) const;
    
    size_t size() const;

};

#endif