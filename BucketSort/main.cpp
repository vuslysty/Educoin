#include <sstream>

#include "BucketSort.hpp"

std::vector<double> split(const std::string& s, char delimiter) {
  std::vector<double> tokens;
  std::string token;
  std::istringstream token_stream(s);  // NOLINT

  while (std::getline(token_stream, token, delimiter)) {
    if (!token.empty()) {
      double num = std::stod(token); // NOLINT
      if (num == 0.0) {
        return tokens;
      }
      tokens.push_back(num);
    }
  }
  token.clear();

  return tokens;
}

int main() {
  BucketSort sorter{};
  std::string line;
  std::vector<double> numbers;

  getline(std::cin, line, '\n');
  numbers = split(line, ' ');

  if (!numbers.empty()) {
    size_t max_collisions = sorter(numbers.data(), numbers.size());

    for (size_t i = 0; i < numbers.size(); i++) {
      if (i != 0u) {
        std::cout << " ";
      }
      std::cout << numbers[i];  
    }
    std::cout << std::endl;
    std::cout << max_collisions << std::endl;
  } else {
    std::cout << "Empty" << std::endl;
  }
  return 0;
}