#include <iostream>
#include "HashTable.hpp"
#include <fstream>
#include "../TextParser/TextParser.hpp"
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

int main() {

    TextParser parser;
    HashTable hash(100);

    if (!parser.parseText("dictionary.txt"))
        std::cout << "cannot open file" << std::endl;

    for (std::string &str : parser.vectorOfWords()) {
        hash.push(str);
    }

    hash.sortTable();
    // hash.print();



    size_t counter = 0;
    for (auto & p : fs::directory_iterator("texts")) {
        HashTable hashOriginals(10000);

        if (!parser.parseText(p.path().string()))
            std::cout << "cannot open file" << std::endl;

        for (std::string &word : parser.vectorOfWords()) {
            const std::string *elem = hash.findElement(word);
            if (!elem) {
                hashOriginals.push(word, false);
                counter++;
            }
        }
        std::cout << "Not founded originals in [" << p.path().string() << "] - " << hashOriginals.size() << " words, general amount - " << parser.vectorOfWords().size() << std::endl;
    }

    std::cout << "Not founded - " << counter << " words" << std::endl;

    std::cout << hash.size() << std::endl;

    return 0;
}