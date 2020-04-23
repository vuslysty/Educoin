#ifndef TOKEN_HPP //NOLINT
#define TOKEN_HPP

#include <iostream>
#include <string>

enum eToken {
  NUM,
  VAR,
  PLUS,
  MIN,
  DIV,
  MULT,
  MOD,
  OpenScope,
  CloseScope,
  LastIdentifier
};

class Token {
  eToken _token;
  std::string _s_value;
  int_least64_t _n_value;

 public:
  //NOLINTNEXTLINE
  explicit Token(eToken t, std::string value = "") : _token(t), _s_value(std::move(value)) {
    if (_token == NUM || _token == VAR) {
      _n_value = std::stoll(_s_value); //NOLINT
    }
    else {
      _n_value = 0;
    }
  }
  // Token(Token const &src) = default;
  // Token(Token &&src) = default;
  // Token &operator=(Token const &rhs) = default;
  // Token &operator=(Token &&rhs) = default;
  // ~Token() = default;

  eToken getToken() const { return _token; }
  std::string getSValue() const { return _s_value; }
  int_least64_t getNValue() const { return _n_value; }
  int_least64_t &getNValue() { return _n_value; }
};

#endif