#include "Parser.hpp"

void Parser::addZeroFS() {
    tokens->insert(carret, {NUM, "0"});
    moveCarretBack();
}

void Parser::exitFS() {
    if (openScopeCounter != closeScopeCounter) {
        std::cout << "Problem with scopes!!" << std::endl;
        exit(1);
    }
    tokens->pop_back();
    stop = true;
}

void Parser::errorFS() {
    std::cout << "Syntax Error!" << std::endl;
    exit(1);
}

void Parser::moveCarretBack()    { --carret; }
void Parser::moveCarretForward() { ++carret; }

void Parser::scopeCounter() { 
    if ((*carret).getToken() == OpenScope)
        openScopeCounter++;
    else if((*carret).getToken() == CloseScope)
        closeScopeCounter++;
}
