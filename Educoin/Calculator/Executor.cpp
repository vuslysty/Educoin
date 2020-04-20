#include "Executor.hpp"

void Executor::doOperation(std::list<Token>::iterator &op) {
    std::list<Token>::iterator firstElem;
    std::list<Token>::iterator secondElem;

    firstElem = op, --firstElem;
    secondElem = op, ++secondElem;

    if (op->getToken() == PLUS)
        firstElem->getNValue() += secondElem->getNValue();
    else if (op->getToken() == MIN)
        firstElem->getNValue() -= secondElem->getNValue();
    else if (op->getToken() == DIV)
        firstElem->getNValue() /= secondElem->getNValue();
    else if (op->getToken() == MULT)
        firstElem->getNValue() *= secondElem->getNValue();
    else if (op->getToken() == MOD)
        firstElem->getNValue() %= secondElem->getNValue();

    list.erase(op, ++secondElem);
    op = firstElem;
}

void Executor::computeByPriority(std::list<Token>::iterator begin,
                                     std::list<Token>::iterator end)
{
    std::list<Token>::iterator iter = begin;

    // Compute all first priority operations
    while (iter != end) {
        eToken t = iter->getToken();
        if (t == DIV || t == MULT || t == MOD)
            doOperation(iter);
        ++iter;
    }

    // Compute all second priority operations
    iter = begin;
    while (iter != end) {
        eToken t = iter->getToken();
        if (t == PLUS || t == MIN)
            doOperation(iter);
        ++iter;
    }

    iter = begin, ++iter;
    std::swap(*begin, *iter);
    list.erase(iter, end);
}

int_fast64_t Executor::executeExpression(std::string const &expr) {
    
    list.clear();
    lexer.doLexAnalization(&list, expr);
    parser.doParsingAnalization(&list);

    computeByPriority(list.begin(), list.end());
    return list.front().getNValue();
}