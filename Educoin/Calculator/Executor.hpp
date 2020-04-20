#include "Parser.hpp"
#include "Lexer.hpp"

class Executor {

    Lexer               lexer;
    Parser              parser;
    std::list<Token>    list;

    void computeByPriority(std::list<Token>::iterator begin,
                               std::list<Token>::iterator end);
    void doOperation(std::list<Token>::iterator &op);

public:
    int_fast64_t executeExpression(std::string const &expr);
};