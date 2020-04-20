#include "Lexer.hpp"
#include "Parser.hpp"
#include "Executor.hpp"

int main() {
    Executor executor;

    // executor.executeExpression("-((-2 * 4) * ((-10) - 7) )");
    // executor.executeExpression("$0 - 64");

    // executor.executeExpression("100");
    executor.executeExpression("1");
    executor.executeExpression("2");
    executor.executeExpression("3");
    executor.executeExpression("4");
    executor.executeExpression("5");
    executor.executeExpression("6");
    executor.executeExpression("7");
    executor.executeExpression("8");
    executor.executeExpression("9");
    executor.executeExpression("10");
    executor.executeExpression("11");


    int_fast64_t res = executor.executeExpression("$0");

    std::cout << res << std::endl;

    // for (auto e : list) {
    //     std::cout << strToken[e.getToken()] << " ";
    // }
    // std::cout << std::endl;

    return 0;
}
