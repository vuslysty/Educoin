#include "Lexer.hpp"

void Lexer::errorFS() {
  std::cout << "ERROOOOR" << std::endl;
  std::string error_pointer(_input_str.size(), ' ');
  error_pointer[_start_token] = '^';

  for (unsigned int i = _start_token + 1; i <= _carret; i++)
    error_pointer[i] = '~';

  std::cout << _input_str << std::endl;
  std::cout << error_pointer << std::endl;

  exit(1);
}

int Lexer::getCondition() const {
  int i;

  for (i = 0; i < CONDITION_COUNT; i++)
    if ((this->*kConditions[i])(_input_str[_carret])) break;
  return (i);
}

void Lexer::initBeforeWork(std::list<Token> *list, std::string const &str) {
  _state = 0;
  _stop = false;
  _carret = 0;
  _start_token = 0;

  _tokens = list;
  _input_str = str;
}

void Lexer::doLexAnalization(std::list<Token> *list, std::string const &str) {
  TransitionLCallback funk = nullptr;
  int condition = 0;

  initBeforeWork(list, str);

  while (!_stop) {
    if (_state == 0) _start_token = _carret;

    condition = getCondition();
    funk = kFsmTable[_state][condition].worker;

    if (funk) (this->*funk)();

    _state = kFsmTable[_state][condition].newState;

    _carret++;
  }
}

const Conditions Lexer::kConditions[CONDITION_COUNT] = {
    &Lexer::whiteCondition,     &Lexer::numCondition,   &Lexer::varCondition,
    &Lexer::operationCondition, &Lexer::scopeCondition, &Lexer::zeroCondition};

const TransitionL Lexer::kFsmTable[4][7] = {
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