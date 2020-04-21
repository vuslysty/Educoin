#include <tuple>

#include "Lexer.hpp"
#include "Parser.hpp"

class Executor {
  Lexer lexer;
  Parser parser;
  std::list<Token> list;

  int_fast64_t cicle_buf[10] = {0};
  u_int8_t positionForSave = 0;

  void recursiveExecute(std::list<Token>::iterator begin,
                        std::list<Token>::iterator end);
  void computeByPriority(std::list<Token>::iterator begin,
                         std::list<Token>::iterator end);
  void doOperation(std::list<Token>::iterator &op);

  void saveValueInBuf(int_fast64_t val);
  void changeVarsToNums();

 public:
  int_fast64_t executeExpression(std::string const &expr);
};