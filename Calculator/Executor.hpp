#ifndef _EXECUTOR_HPP //NOLINT
#define _EXECUTOR_HPP

#include <tuple>

#include "Lexer.hpp"
#include "Parser.hpp"

class Executor {
  Lexer _lexer;
  Parser _parser;
  std::list<Token> _list;

  int_fast64_t _cicle_buf[10] = {0};
  u_int8_t _position_for_save = 0;

  void recursiveExecute(std::list<Token>::iterator begin,
                        std::list<Token>::iterator end);
  void computeByPriority(std::list<Token>::iterator begin,
                         std::list<Token>::iterator end);
  void doOperation(std::list<Token>::iterator *op);

  void saveValueInBuf(int_fast64_t val);
  void changeVarsToNums();

 public:
  int_fast64_t executeExpression(std::string const &expr);
};

#endif