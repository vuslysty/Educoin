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
  BucketSorter sorter{};
  std::string line;
  std::vector<double> numbers;

  getline(std::cin, line, '\n');
  numbers = split(line, ' ');

  if (!numbers.empty()) {

    for (double num : numbers) {
      sorter.push(num);
    }
    sorter.startSort();
    sorter.printFormat();
  } else {
    std::cout << "Empty" << std::endl;
  }
  return 0;
}