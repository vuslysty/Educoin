#ifndef LEXER_HPP
#define LEXER_HPP

#include "Token.hpp"
#include <list>
#include <iostream>

#define CONDITION_COUNT 6
#define STATE_COUNT 4

class Lexer;

typedef bool	(Lexer::*Conditions)(const char c) const;
typedef void    (Lexer::*transitionL_callback)();

struct transitionL
{
	int 					newState;
	transitionL_callback	worker;
};

class Lexer {

    int                 state;

    bool                stop;
    unsigned int        carret;
    unsigned int        startToken;
    std::string         inputStr;
    std::list<Token>    tokens;

    bool	whiteCondition(const char c) const;
    bool	numCondition(const char c) const;
    bool    varCondition(const char c) const;
    bool    operationCondition(const char c) const;
	bool	ScopeCondition(const char c) const;
    bool    zeroCondition(const char c) const;

    void    numFS();
    void    varFS();
    void    operationFS();
    void    scopeFS();
    void    endFS();

    void    errorFS();

    int     getCondition() const;

    static const Conditions     conditions[CONDITION_COUNT];
    static const transitionL    fsmTable[4][7];

public:

    Lexer(std::string str) : state(0), stop(false), carret(0),
                            startToken(0), inputStr(str)
    {}

    void                doLexAnalization();
    std::list<Token>    &getTokenList() { return tokens; }
    std::string         getStr() const { return inputStr; }
};

#endif //LEXER_HPP