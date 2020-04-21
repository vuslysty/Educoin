#include "Lexer.hpp"

void Lexer::numFS() {
  std::string num;

  num.assign(inputStr, startToken, carret - startToken);
  tokens->emplace_back(NUM, num);

  carret--;
}

void Lexer::varFS() {
  std::string num;

  num.assign(inputStr, startToken + 1, 1);
  tokens->emplace_back(VAR, num);

  carret--;
}

void Lexer::operationFS() {
  char op = inputStr[carret];

  switch (op) {
    case '+':
      tokens->emplace_back(PLUS);
      break;
    case '-':
      tokens->emplace_back(MIN);
      break;
    case '/':
      tokens->emplace_back(DIV);
      break;
    case '*':
      tokens->emplace_back(MULT);
      break;
    case '%':
      tokens->emplace_back(MOD);
      break;
  }
}

void Lexer::scopeFS() {
  char scope = inputStr[carret];

  switch (scope) {
    case '(':
      tokens->emplace_back(OpenScope);
      break;
    case ')':
      tokens->emplace_back(CloseScope);
      break;
  }
}

void Lexer::endFS() { stop = true; }