#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include <string>
#include <iostream>
#include <list>

enum eToken{ NUM, VAR, PLUS, MIN, DIV, MULT, MOD, OpenScope, CloseScope, LastIdentifier };

const std::string strToken[] = {"NUM", "VAR", "PLUS", "MIN", "DIV", "MULT", "MOD", "OpenScope", "CloseScope", "LastIdentifier"};

#endif //ABSTRACTVM_AVM_HPP