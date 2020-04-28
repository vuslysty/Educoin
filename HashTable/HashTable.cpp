#include "HashTable.hpp"

HashTable::HashTable() : _size(DEF_SIZE)
{
    _table.resize(_size);
} 

HashTable::HashTable(size_t size) : _size(size)
{
    _table.resize(_size);
}

HashTable::~HashTable() {}

size_t HashTable::getHashSum(const std::string &src) {
    size_t hashsum = 0;
    for (char c : src) {
        hashsum = (hashsum * 31) ^ static_cast<size_t>(c);
    }
    return hashsum;
}

void HashTable::push(std::string const &str, bool enable_reapetes) {
    size_t hash_sum = getHashSum(str);
    size_t index = hash_sum % _size;

    if (!enable_reapetes) {
        for (content_t &cont : _table[index]) {
            if (cont.first == hash_sum)
                return ;
        }
    }

    _count++;
    _table[index].push_back({hash_sum, str});
}

void HashTable::print() const {
    for (size_t i = 0; i < _size; i++) {
        std::cout << "Row[" << i << "]: ";
        for (content_t const &word : _table[i]) {
            std::cout << word.second << " ";
        }
        std::cout << std::endl;
    }
}

template<typename T, typename F>
static T *partition(T *start, T *end, F greater) {
  bool go_forward = true;

  while (start < end) {
    if (greater(*start, *end)) {
      std::swap(*start, *end);
      go_forward ? end-- : start++;  // NOLINT
      go_forward = !go_forward;
    } else {
      go_forward ? start++ : end--;  // NOLINT
    }
  }
  return end;
}

template<typename T, typename F>
static void mQsort(T *start, T *end,
    F comparator = [](T const &a, T const &b){return a > b;}) {

  T *center = partition(start, end, comparator);

  if (start != center) {
    mQsort(start, center - 1, comparator); // NOLINT
  }
  if (end != center) {
    mQsort(center + 1, end, comparator); // NOLINT
  }
}

template<typename T, typename F>
static bool isSorted(std::vector<T> vector, F less_or_eq) {
    if (vector.empty())
        return true;
    auto first = vector.begin();
    auto second = first; ++second;

    for (; second != vector.end(); ++first, ++second) {
        if (!less_or_eq(*first, *second))
            return false;
    }
    return true;
}

void HashTable::sortTable() {

    for (size_t i = 0; i < _size; i++) {
        if (!_table[i].empty()) {
            content_t *array = _table[i].data();
            size_t size = _table[i].size();
            // isSorted(_table[i], [](content_t const &a, content_t const &b) { return (a.first <= b.first);});

            if (size > 1) {
                mQsort(array, array + (size - 1), [](content_t const &a, content_t const &b) { return (a.first > b.first);} );
            }
        }
    }
}

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

std::string const *HashTable::findElement(std::string const &str) const {
    size_t hash_sum = getHashSum(str);
    content_t cont;

    cont.first = hash_sum;
    cont.second = str;

    if (_table[hash_sum % _size].empty())
        return nullptr;

    const content_t *array = _table[hash_sum % _size].data();
    size_t array_size = _table[hash_sum % _size].size();

    const content_t *res = find(cont, array, array + (array_size - 1),
        [](content_t const &a, content_t const &b) { return a.first > b.first; },
        [](content_t const &a, content_t const &b) { return a.first == b.first; });

    return res ? &res->second : nullptr;
}

size_t HashTable::size() const {
    return _count;
}