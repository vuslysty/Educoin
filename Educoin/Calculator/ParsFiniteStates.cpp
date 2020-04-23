#include "Parser.hpp"

void Parser::addZeroFS() {
  _tokens_list->insert(_carret, Token(NUM, "0"));
  moveCarretBack();
}

void Parser::exitFS() {
  if (_open_scope_counter != _close_scope_counter) {
    std::cout << "Problem with scopes!!" << std::endl;
    exit(1);
  }
  _tokens_list->pop_back();
  _stop = true;
}

void Parser::errorFS() {
  std::cout << "Syntax Error!" << std::endl;
  exit(1);
}

void Parser::moveCarretBack() { --_carret; }
void Parser::moveCarretForward() { ++_carret; }

void Parser::scopeCounter() {
  if ((*_carret).getToken() == OpenScope)
    _open_scope_counter++;
  else if ((*_carret).getToken() == CloseScope)
    _close_scope_counter++;
}
