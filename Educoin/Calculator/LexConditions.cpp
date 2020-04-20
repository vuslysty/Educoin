#include "Lexer.hpp"

bool Lexer::whiteCondition(const char c) const
{
	return (c == '\t' || c == ' ');
}

bool Lexer::numCondition(const char c) const
{
	return (isdigit(c));
}

bool Lexer::varCondition(const char c) const
{
	return (c == '$');
}

bool    Lexer::operationCondition(const char c) const
{
    return (c == '+' || c == '-' || c == '/' ||
            c == '*' || c == '%');
}

bool Lexer::ScopeCondition(const char c) const
{
	return (c == '(' || c == ')');
}

bool Lexer::zeroCondition(const char c) const
{
    return (c == '\0');
}