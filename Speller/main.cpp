#include "Checker.hpp"
#include "IDictionary.hpp"

int main() {

    IDictionary *dictionaries[] = {
        new TrieDictionary(),
        new VectorDictionary(),
        new StdHashTableDictionary(),
        new MyHashTableDictionary(),
        // new BinTreeDictionary() // Works too long time, recomended to start with less than 200K words.
    };

    size_t size = sizeof(dictionaries) / sizeof(*dictionaries);

    Checker checker;

    for (size_t i = 0; i < size; i++) {
        checker.check(dictionaries[i]);
        delete dictionaries[i];
    }

    checker.printResults();
}