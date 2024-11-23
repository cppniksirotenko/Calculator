#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include <vector>
#include <string>
#include <stack>

class Calculator
{

public:
    double execute(const std::string &s);

private:
    std::vector<std::string> parseExp(const std::string &exp);
    double calculate(const std::vector<std::string> &list, bool inBrackets);
    std::string workBrackets(const std::string &exp);
};

#endif // CALCULATOR_HPP
