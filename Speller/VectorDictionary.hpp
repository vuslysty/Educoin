#ifndef VECTOR_DICTIONATY
#define VECTOR_DICTIONATY

#include "IDictionary.hpp"
#include <vector>
#include <algorithm>

class VectorDictionary : public IDictionary {
    std::vector<std::string> _dictionary;
    bool _is_sorted{false};


template<typename T>
static T const *get_center(T const *start, T const *end) {
    if (start == end)
        return start;

    size_t count_of_elem = 1 + ((end - start) / sizeof(T));
    return start + (count_of_elem / 2);
}

template<typename T, typename FG, typename FEQ>
static T const *find(T const &target, T const *start, T const *end,
    FG is_greater =  [](T const &a, T const &b) -> bool {return a > b;},
    FEQ is_equal = [](T const &a, T const &b) -> bool {return a == b;})
{
    T const *ret_value = nullptr;   
    T const *center = get_center(start, end);

    if (is_equal(target, *center))
        ret_value = center;
    else if (start != center && !is_greater(target, *center))
        ret_value = find(target, start, center - 1, is_greater, is_equal);
    else if (end != center && is_greater(target, *center))
        ret_value = find(target, center + 1, end, is_greater, is_equal);
    return ret_value;
}

public:

    void add(std::string const &word) {
        _dictionary.push_back(word);
        _is_sorted = false;
    }

    bool check(std::string const &word) {
        if (!_is_sorted) {
            std::sort(_dictionary.begin(), _dictionary.end());
            _is_sorted = true;
        }
        const std::string *res = find(word, _dictionary.data(), _dictionary.data() + (_dictionary.size() - 1),
        [](std::string const &a, std::string const &b) { return a > b; },
        [](std::string const &a, std::string const &b) { return a == b; });
        
        return res ? true : false;
        // auto res = std::find(_dictionary.begin(), _dictionary.end(), word);
        // return (res == _dictionary.end()) ? false : true;
    }

    std::string getNameOfStructure() {
        return "VectorDictionary";
    }

    virtual ~VectorDictionary() {}
};

#endif