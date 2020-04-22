#ifndef LEXER_HPP
#define LEXER_HPP

#include "Token.hpp"
#include <list>

#define CONDITION_COUNT 6
#define STATE_COUNT 4

class Lexer;

typedef bool (Lexer::*Conditions)(const char c) const;
typedef void (Lexer::*transitionL_callback)();

struct transitionL {
  int newState;
  transitionL_callback worker;
};

class Lexer {
  int state = 0;
  bool stop = false;
  unsigned int carret = 0;
  unsigned int startToken = 0;
  std::string inputStr;
  std::list<Token> *tokens;

  bool whiteCondition(const char c) const;
  bool numCondition(const char c) const;
  bool varCondition(const char c) const;
  bool operationCondition(const char c) const;
  bool ScopeCondition(const char c) const;
  bool zeroCondition(const char c) const;

  void numFS();
  void varFS();
  void operationFS();
  void scopeFS();
  void endFS();

  void errorFS();

  int getCondition() const;
  void initBeforeWork(std::list<Token> *list, std::string const &str);

  static const Conditions conditions[CONDITION_COUNT];
  static const transitionL fsmTable[4][7];

 public:
  void doLexAnalization(std::list<Token> *list, std::string const &str);
  std::list<Token> *getTokenList() { return tokens; }
  std::string getStr() const { return inputStr; }
};

#endif  // LEXER_HPP