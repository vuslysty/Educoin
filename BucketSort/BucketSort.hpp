#ifndef BUCKET_SORT  // NOLINT
#define BUCKET_SORT

#include <cmath>
#include <iostream>
#include <vector>

class BucketSort {
  size_t _min;
  size_t _max;

  void setMinMax(double *array, size_t size) {
    double tmp_min = __DBL_MAX__;
    double tmp_max = 0.0;

    for (size_t i = 0; i < size; i++) {
      tmp_min = std::min(tmp_min, array[i]);  // NOLINT
      tmp_max = std::max(tmp_max, array[i]);  // NOLINT
    }
    _min = static_cast<size_t>(floor(tmp_min));
    _max = static_cast<size_t>(floor(tmp_max));
  }

  double *partition(double *start, double *end) {
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

  void mQsort(double *start, double *end) {
    double *center = partition(start, end);

    if (start != center) {
      mQsort(start, center - 1); // NOLINT
    }
    if (end != center) {
      mQsort(center + 1, end); // NOLINT
    }
  }

 public:
  size_t operator()(double *array, size_t size) {  // NOLINT
    if (array == nullptr || size == 0u) {
      return 0;
    }

    setMinMax(array, size);

    size_t count_buckets = _max - _min + 1;
    std::vector<std::vector<double>> buckets;
		
		buckets.resize(count_buckets);

    for (size_t i = 0; i < size; i++) {
      // NOLINTNEXTLINE
      buckets[static_cast<size_t>(floor(array[i])) - _min].push_back(array[i]);
    }

    size_t max_collision = 0;
    size_t index = 0;
    for (size_t i = 0; i < count_buckets; i++) {
      if (!buckets[i].empty()) {
        double *tmp_arr = buckets[i].data();

        mQsort(tmp_arr, tmp_arr + (buckets[i].size() - 1));  // NOLINT
        max_collision = std::max(max_collision, buckets[i].size());
      }
			// NOLINTNEXTLINE
      for (size_t j = 0; j < buckets[i].size(); j++) {
        array[index++] = buckets[i][j];  // NOLINT
      }
    }

    return max_collision;
  }
};

#endif