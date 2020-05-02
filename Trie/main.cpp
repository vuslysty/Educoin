#include "Trie.hpp"
#include <iostream>

int main() {

    Trie t;

    t.add("Hi");
    t.add("His");

    std::cout << t.check("Hid") << std::endl;

    return 0;
}