#include "Lexer.hpp"

bool Lexer::whiteCondition(char c) const {
  return (c == '\t' || c == ' ');
}

bool Lexer::numCondition(char c) const { return (isdigit(c)); }

bool Lexer::varCondition(char c) const { return (c == '$'); }

bool Lexer::operationCondition(char c) const {
  return (c == '+' || c == '-' || c == '/' || c == '*' || c == '%');
}

bool Lexer::scopeCondition(char c) const {
  return (c == '(' || c == ')');
}

bool Lexer::zeroCondition(char c) const { return (c == '\0'); }