#include "Lexer.hpp"

void Lexer::numFS() {
  std::string num;

  num.assign(_input_str, _start_token, _carret - _start_token);
  _tokens->emplace_back(NUM, num);

  _carret--;
}

void Lexer::varFS() {
  std::string num;

  num.assign(_input_str, _start_token + 1, 1);
  _tokens->emplace_back(VAR, num);

  _carret--;
}

void Lexer::operationFS() {
  char op = _input_str[_carret];

  switch (op) {
    case '+':
      _tokens->emplace_back(PLUS);
      break;
    case '-':
      _tokens->emplace_back(MIN);
      break;
    case '/':
      _tokens->emplace_back(DIV);
      break;
    case '*':
      _tokens->emplace_back(MULT);
      break;
    case '%':
      _tokens->emplace_back(MOD);
      break;
  }
}

void Lexer::scopeFS() {
  char scope = _input_str[_carret];

  switch (scope) {
    case '(':
      _tokens->emplace_back(OpenScope);
      break;
    case ')':
      _tokens->emplace_back(CloseScope);
      break;
  }
}

void Lexer::endFS() { _stop = true; }