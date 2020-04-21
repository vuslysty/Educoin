#include "Lexer.hpp"

void Lexer::errorFS() {
  std::cout << "ERROOOOR" << std::endl;
  std::string error_pointer(inputStr.size(), ' ');
  error_pointer[startToken] = '^';

  for (unsigned int i = startToken + 1; i <= carret; i++)
    error_pointer[i] = '~';

  std::cout << inputStr << std::endl;
  std::cout << error_pointer << std::endl;

  exit(1);
}

int Lexer::getCondition() const {
  int i;

  for (i = 0; i < CONDITION_COUNT; i++)
    if ((this->*conditions[i])(inputStr[carret])) break;
  return (i);
}

void Lexer::initBeforeWork(std::list<Token> *list, std::string const &str) {
  state = 0;
  stop = false;
  carret = 0;
  startToken = 0;

  tokens = list;
  inputStr = str;
}

void Lexer::doLexAnalization(std::list<Token> *list, std::string const &str) {
  transitionL_callback funk = nullptr;
  int condition = 0;

  initBeforeWork(list, str);

  while (!stop) {
    if (state == 0) startToken = carret;

    condition = getCondition();
    funk = fsmTable[state][condition].worker;

    if (funk) (this->*funk)();

    state = fsmTable[state][condition].newState;

    carret++;
  }
}

const Conditions Lexer::conditions[CONDITION_COUNT] = {
    &Lexer::whiteCondition,     &Lexer::numCondition,   &Lexer::varCondition,
    &Lexer::operationCondition, &Lexer::ScopeCondition, &Lexer::zeroCondition};

const transitionL Lexer::fsmTable[4][7] = {
    //-------------------- STATE 0 ----------------------------------------
    [0][0] = {0, nullptr},
    [0][1] = {1, nullptr},
    [0][2] = {2, nullptr},
    [0][3] = {0, &Lexer::operationFS},
    [0][4] = {0, &Lexer::scopeFS},
    [0][5] = {0, &Lexer::endFS},
    [0][6] = {0, &Lexer::errorFS},
    //-------------------- STATE 1 ----------------------------------------
    [1][0] = {0, &Lexer::numFS},
    [1][1] = {1, nullptr},
    [1][2 ... 6] = {0, &Lexer::numFS},
    //-------------------- STATE 2 ----------------------------------------
    [2][0] = {0, &Lexer::endFS},
    [2][1] = {3, nullptr},
    [2][2 ... 6] = {0, &Lexer::endFS},
    //-------------------- STATE 3 ----------------------------------------
    [3][0] = {0, &Lexer::varFS},
    [3][1] = {0, &Lexer::errorFS},
    [3][2] = {0, &Lexer::errorFS},
    [3][3 ... 5] = {0, &Lexer::varFS},
    [3][6] = {0, &Lexer::errorFS}
    //--------------------   END   ----------------------------------------
};