#include "Lexer.hpp"

void Lexer::errorFS() {
    std::cout << "ERROOOOR" << std::endl;
    exit(1);
}

int Lexer::getCondition() const
{
	int i;

	for (i = 0; i < CONDITION_COUNT; i++)
		if ((this->*conditions[i])(inputStr[carret]))
			break ;
	return (i);
}

void Lexer::doLexAnalization()
{
	transitionL_callback	funk = nullptr;
	int 					condition = 0;

	state = 0;
	while (!stop)
	{
        if (state == 0)
            startToken = carret;

		condition = getCondition();
		funk = fsmTable[state][condition].worker;

		if (funk)
			(this->*funk)();

		state = fsmTable[state][condition].newState;

		carret++;
	}
}

const Conditions	Lexer::conditions[CONDITION_COUNT] = {
		&Lexer::whiteCondition,
		&Lexer::numCondition,
		&Lexer::varCondition,
		&Lexer::operationCondition,
		&Lexer::ScopeCondition,
        &Lexer::zeroCondition
};


const transitionL	Lexer::fsmTable[4][7] = {
//-------------------- STATE 0 ----------------------------------------
		[0][0] = {0, nullptr},
		[0][1] = {1, nullptr},
		[0][2] = {2, nullptr},
		[0][3] = {0, &Lexer::operationFS},
		[0][4] = {0, &Lexer::scopeFS},
		[0][5] = {0, &Lexer::endFS},
		[0][6] = {0, &Lexer::errorFS},
//-------------------- STATE 1 ----------------------------------------
		[1][0] = {0, &Lexer::numFS},
		[1][1] = {1, nullptr},
		[1][2 ... 6] = {0, &Lexer::numFS},
//-------------------- STATE 2 ----------------------------------------
		[2][0] = {0, &Lexer::endFS},
		[2][1] = {3, nullptr},
		[2][2 ... 6] = {0, &Lexer::endFS},
//-------------------- STATE 3 ----------------------------------------
		[3][0] = {0, &Lexer::varFS},
		[3][1] = {0, &Lexer::errorFS},
		[3][2] = {0, &Lexer::errorFS},
		[3][3] = {0, &Lexer::varFS},
		[3][4] = {0, &Lexer::errorFS},
		[3][5] = {0, &Lexer::varFS},
		[3][6] = {0, &Lexer::errorFS}
//--------------------   END   ----------------------------------------
};