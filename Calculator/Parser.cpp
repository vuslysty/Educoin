#include "Parser.hpp"

void Parser::initBeforeWork(std::list<Token> *t) {
  _state = 0;
  _stop = false;
  _open_scope_counter = 0;
  _close_scope_counter = 0;

  _tokens_list = t;
  t->emplace_front(OpenScope);
  t->emplace_back(CloseScope);
  t->emplace_back(LastIdentifier);
  _carret = t->begin();
}

void Parser::doParsingAnalization(std::list<Token> *t) {
  TransitionPCallback funk = nullptr;
  eToken condition;

  initBeforeWork(t);
  _tokens_list = t;
  _carret = t->begin();
  while (!_stop) {
    condition = (*_carret).getToken();
    funk = kFsmTable[_state][condition].worker;
    _state = kFsmTable[_state][condition].newState;

    if (funk) (this->*funk)();

    moveCarretForward();
  }
}

const TransitionP Parser::kFsmTable[5][LastIdentifier + 1] = {
    //-------------------- STATE 0 ----------------------------------------
    [0][0 ... 1] = {3, nullptr},
    [0][2 ... 6] = {4, nullptr},
    [0][7] = {1, &Parser::scopeCounter},
    [0][8] = {2, &Parser::scopeCounter},
    [0][9] = {0, &Parser::exitFS},
    //-------------------- STATE 1 ----------------------------------------
    [1][0 ... 1] = {0, &Parser::moveCarretBack},
    [1][2 ... 3] = {0, &Parser::addZeroFS},
    [1][4 ... 6] = {0, &Parser::errorFS},
    [1][7] = {0, &Parser::moveCarretBack},
    [1][8 ... 9] = {0, &Parser::errorFS},
    //-------------------- STATE 2 ----------------------------------------
    [2][0 ... 1] = {0, &Parser::errorFS},
    [2][2 ... 6] = {0, &Parser::moveCarretBack},
    [2][7] = {0, &Parser::errorFS},
    [2][8 ... 9] = {0, &Parser::moveCarretBack},
    //-------------------- STATE 3 ----------------------------------------
    [3][0 ... 1] = {0, &Parser::errorFS},
    [3][2 ... 6] = {0, &Parser::moveCarretBack},
    [3][7] = {0, &Parser::errorFS},
    [3][8 ... 9] = {0, &Parser::moveCarretBack},
    //-------------------- STATE 4 ----------------------------------------
    [4][0 ... 1] = {0, &Parser::moveCarretBack},
    [4][2 ... 6] = {0, &Parser::errorFS},
    [4][7] = {0, &Parser::moveCarretBack},
    [4][8 ... 9] = {0, &Parser::errorFS},
    //--------------------   END   ----------------------------------------
};