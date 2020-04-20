#ifndef TOKEN_HPP
#define TOKEN_HPP

#include "Calculator.hpp"

class Token {
    eToken      token;
    std::string sValue;

public:

    Token(eToken t, std::string value = "") : token(t), sValue(value) {};
    Token(Token const & src) = default;
    Token(Token && src) = default;
    Token &operator=(Token const & rhs) = default;
    Token &operator=(Token && rhs) = default ;
    ~Token() = default;

    eToken      getToken() const { return token; }
    std::string getValue() const { return sValue; }
};

#endif