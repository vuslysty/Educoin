#include "Lexer.hpp"

int main() {
    Lexer lexer("----2+4-56(0  $3 )   $0");

    lexer.doLexAnalization();
    
    std::cout << lexer.getStr() << std::endl;

    std::list<Token> &list = lexer.getTokenList();

    list.emplace_front(OpenScope);
    list.emplace_back(CloseScope);

    for (auto e : list) {
        std::cout << strToken[e.getToken()] << " ";
    }
    std::cout << std::endl;

    return 0;
}
