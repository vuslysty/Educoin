#ifndef PARSER_HPP //NOLINT
#define PARSER_HPP

#include "Lexer.hpp"

class Parser;

// typedef void (Parser::*transitionP_callback)();
using TransitionPCallback = void (Parser::*)();

struct TransitionP {
  int newState;
  TransitionPCallback worker;
};

class Parser {
  int _state{0};
  bool _stop{false};

  int _open_scope_counter{0};
  int _close_scope_counter{0};

  std::list<Token> *_tokens_list{nullptr};
  std::list<Token>::iterator _carret;

  void addZeroFS();
  void exitFS();
  void errorFS();
  void moveCarretBack();
  void moveCarretForward();
  void scopeCounter();

  void initBeforeWork(std::list<Token> *t);

  static const TransitionP kFsmTable[5][LastIdentifier + 1];

 public:
  void doParsingAnalization(std::list<Token> *t);
};

#endif