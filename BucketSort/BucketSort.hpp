#ifndef BUCKET_SORT  // NOLINT
#define BUCKET_SORT

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

static double *partition(double *start, double *end) {
  bool go_forward = true;

  while (start < end) {
    if (*start > *end) {
      std::swap(*start, *end);
      go_forward ? end-- : start++;  // NOLINT
      go_forward = !go_forward;
    } else {
      go_forward ? start++ : end--;  // NOLINT
    }
  }
  return end;
}

static void mQsort(double *start, double *end) {
  double *center = partition(start, end);

  if (start != center) {
    mQsort(start, center - 1); // NOLINT
  }
  if (end != center) {
    mQsort(center + 1, end); // NOLINT
  }
}

class BucketSorter {
  
  size_t              _max_collisions{0};
  std::vector<double> _vector;

 public:

  void startSort() {

    if (_vector.empty()) {
      _max_collisions = 0;
      return ;
    }

    size_t min = static_cast<size_t>(floor(*std::min_element(_vector.begin(), _vector.end())));
    size_t max = static_cast<size_t>(floor(*std::max_element(_vector.begin(), _vector.end())));
    size_t count_buckets = max - min + 1;
    std::vector<std::vector<double>> buckets;
    
    buckets.resize(count_buckets);

    for (double num : _vector) {
      buckets[static_cast<size_t>(floor(num)) - min].push_back(num);
    }

    size_t index = 0;
    _max_collisions = 0;
    for (size_t i = 0; i < count_buckets; i++) {
      if (!buckets[i].empty()) {
        double *tmp_arr = buckets[i].data();

        mQsort(tmp_arr, tmp_arr + (buckets[i].size() - 1));  // NOLINT
        _max_collisions = std::max(_max_collisions, buckets[i].size());
      }
			// NOLINTNEXTLINE
      for (size_t j = 0; j < buckets[i].size(); j++) {
        _vector[index++] = buckets[i][j];  // NOLINT
      }
    }
  }

  void push(double elem) {
    _vector.push_back(elem);
  }

  size_t getMaxCollisions() const {
    return _max_collisions;
  }

  std::vector<double> getVector() const {
    return _vector;
  }

  void printVector() const {
    for (size_t i = 0; i < _vector.size(); i++) {
      if (i != 0u) { std::cout << " "; }
      std::cout << _vector[i];
    }
    std::cout << std::endl;
  }

  void printFormat() const {
    printVector();
    std::cout << _max_collisions << std::endl;
  }
};

#endif