#ifndef PARSER_HPP
#define PARSER_HPP

#include "Lexer.hpp"

class Parser;

typedef void    (Parser::*transitionP_callback)();

struct transitionP
{
	int 					newState;
	transitionP_callback	worker;
};

class Parser {

    int		state = 0;
    bool    stop = false;

	int		openScopeCounter = 0;
	int		closeScopeCounter = 0;			

	std::list<Token>			*tokens = nullptr;
	std::list<Token>::iterator  carret;

	void    addZeroFS();
    void    exitFS();
    void    errorFS();
	void	moveCarretBack();
	void	moveCarretForward();
	void	scopeCounter();

	void	initBeforeWork(std::list<Token> *t);

    static const transitionP	fsmTable[5][LastIdentifier + 1];

public: 

	void doParsingAnalization(std::list<Token> *t);
};

#endif