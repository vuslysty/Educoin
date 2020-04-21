#ifndef TOKEN_HPP
#define TOKEN_HPP

#include "Calculator.hpp"

class Token {
  eToken token;
  std::string sValue;
  int_least64_t nValue;

 public:
  Token(eToken t, std::string const &value = "") : token(t), sValue(value) {
    if (token == NUM || token == VAR)
      nValue = std::stoll(sValue);
    else
      nValue = 0;
  }
  Token(Token const &src) = default;
  Token(Token &&src) = default;
  Token &operator=(Token const &rhs) = default;
  Token &operator=(Token &&rhs) = default;
  ~Token() = default;

  eToken getToken() const { return token; }
  std::string getSValue() const { return sValue; }
  int_least64_t getNValue() const { return nValue; }
  int_least64_t &getNValue() { return nValue; }
};

#endif