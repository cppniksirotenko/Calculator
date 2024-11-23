#include <iostream>

#include "calculator.hpp"

int main()
{
    std::string exp1 = "55 + 44*3 - 11";
    std::string exp2 = "(2-1) + 2 * (2 / (2 - 1))";
    std::string exp3 = "(2-1) + (2 * (2 - 1))";
    std::string exp4 = "5/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))";


    Calculator c;


    std::cout << c.execute(exp1) << std::endl;
    std::cout << c.execute(exp2) << std::endl;
    std::cout << c.execute(exp3) << std::endl;
    std::cout << c.execute(exp4) << std::endl;
    return 0;
}
