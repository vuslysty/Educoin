#include <vector>

#include "BinaryTree.hpp"

std::vector<unsigned int> split(const std::string& s, char delimiter) {
  std::vector<unsigned int> tokens;
  std::string token;
  std::istringstream tokenStream(s);

  while (std::getline(tokenStream, token, delimiter)) {
    if (!token.empty()) {
      tokens.push_back(std::stoul(token));
    }
  }
  return tokens;
}

int main() {
  BinaryTree<unsigned int> bTree;
  std::vector<unsigned int> numbers;
  std::string line;

  getline(std::cin, line, '\n');
  numbers = split(line, ' ');

  for (unsigned int i : numbers) {
    if (i == 0) {
      std::cout << bTree.printElements() << std::endl;
      return 0;
    }

    bTree.addNewElement(i);
  }

  return 1;
}