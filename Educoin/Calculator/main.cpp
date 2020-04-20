#include "Lexer.hpp"
#include "Parser.hpp"
#include "Executor.hpp"

int main() {
    Executor executor;

    std::string expr = "2+2*2-4/2*2";

    executor.executeExpression(expr);
    std::cout << executor.executeExpression(expr) << std::endl;

    // for (auto e : list) {
    //     std::cout << strToken[e.getToken()] << " ";
    // }
    // std::cout << std::endl;

    return 0;
}
