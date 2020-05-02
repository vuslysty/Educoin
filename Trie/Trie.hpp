#ifndef TRIE_HPP
#define TRIE_HPP

#include <vector>
#include <string>

class Trie {

    class Node {
    public:
        bool end_of_word{false};
        std::vector<Node*> vector;

        Node() {
            // 27 = 26 letter of alphabet and character '
            vector.resize(27, nullptr);
        }

        ~Node() {
            for (Node *it : vector) {
                delete it;
            }
        }
    };

    Node *_node;

    int getIndex(char c) {
        if (c == '\'')
            return 26;
        else 
            return c - 'a';
    }

public:
    Trie() : _node(new Node()) {}

    void add(std::string const &str) {
        Node *ptr = _node;

        for (char c : str) {
            int index = getIndex(c);

            if (ptr) {
                Node *found = nullptr;
                
                found = ptr->vector[index];

                if (found) {
                    ptr = found;
                    continue;
                }
            }
            else {
                ptr = new Node();
            }

            ptr->vector[index] = new Node();
            ptr = ptr->vector[index];
        }
        ptr->end_of_word = true;
    }

    bool check(std::string const &str) {
        Node *ptr = _node;

        for (char c : str) {
            if (ptr) {
                int index = getIndex(c);

                Node *found = nullptr;
                
                found = ptr->vector[index];

                if (found) {
                    ptr = found;
                    continue;
                }
            }
            return false;
        }
        return (ptr->end_of_word);
    }

    ~Trie() {
        delete _node;
    }

};

#endif 