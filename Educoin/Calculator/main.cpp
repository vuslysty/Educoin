#include "Executor.hpp"

void run() {
  Executor executor;
  std::string expression;
  int_fast64_t res;

  while (true) {
    std::getline(std::cin, expression, '\n');
    if (std::cin.eof()) {
      std::cout << "Bye" << std::endl;
      break;
    }
    if (!expression.empty()) {
      res = executor.executeExpression(expression);
      std::cout << res << std::endl;
    }
  }
}

int main() {
  run();
  return 0;
}
