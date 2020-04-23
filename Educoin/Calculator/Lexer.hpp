#ifndef LEXER_HPP //NOLINT
#define LEXER_HPP

#include "Token.hpp"
#include <list>

#define CONDITION_COUNT 6
#define STATE_COUNT 4

class Lexer;

// typedef bool (Lexer::*Conditions)(const char c) const;
using Conditions = bool (Lexer::*)(const char) const;
// typedef void (Lexer::*transitionL_callback)();
using TransitionLCallback = void (Lexer::*)();


struct TransitionL {
  int newState;
  TransitionLCallback worker;
};

class Lexer {
  int _state{0};
  bool _stop{false};
  unsigned int _carret{0};
  unsigned int _start_token{0};
  std::list<Token> *_tokens{nullptr};
  std::string _input_str;

  bool whiteCondition(char c) const;
  bool numCondition(char c) const;
  bool varCondition(char c) const;
  bool operationCondition(char c) const;
  bool scopeCondition(char c) const;
  bool zeroCondition(char c) const;

  void numFS();
  void varFS();
  void operationFS();
  void scopeFS();
  void endFS();

  void errorFS();

  int getCondition() const;
  void initBeforeWork(std::list<Token> *list, std::string const &str);

  static const Conditions kConditions[CONDITION_COUNT];
  static const TransitionL kFsmTable[4][7];

 public:

  void doLexAnalization(std::list<Token> *list, std::string const &str);
  std::list<Token> *getTokenList() { return _tokens; }
  std::string getStr() const { return _input_str; }
};

#endif  // LEXER_HPP