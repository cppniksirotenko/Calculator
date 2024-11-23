#include "calculator.hpp"
#include <iostream>

//-----------------------------------------------------------------------------
double Calculator::execute(const std::string &str)
{
    std::cout << str << std::endl;
    std::string first = workBrackets(str);
    const auto &list = parseExp(first);
    return calculate(list, false);
}

//-----------------------------------------------------------------------------
std::vector<std::string> Calculator::parseExp(const std::string &exp)
{
    std::vector<std::string> list;
    std::string push;
    for(char c : exp) {
        if(std::isspace(c)) {
            continue;
        }

        if(c == '+' || c == '-' || c == '/' || c == '*') {
            if(!push.empty()) {
                list.push_back(push);
                push.clear();
                list.push_back(std::string(1, c));
            } else if(push.empty() && c == '-') {
                push += c;
            }
        } else {
            push += c;
        }
    }

    list.push_back(push);

    return list;

}

//-----------------------------------------------------------------------------
double Calculator::calculate(const std::vector<std::string> &list, bool inBrackets)
{
    std::stack<double> numbers;
    std::stack<std::string> operations;

    for(const auto &a : list) {
        if(a == "+" || a == "-" || a == "/" || a == "*") {
            operations.push(a);
        } else {
            if(!operations.empty()  && (operations.top() == "*" || operations.top() == "/")) {
                double first = numbers.top(); numbers.pop();
                double second = std::stod(a);
                if(operations.top() == "*") {
                    numbers.push(first * second);
                } else if(operations.top() == "/") {
                    numbers.push(first / second);
                }
                operations.pop();
            } else {
                numbers.push(std::stod(a));
            }
        }
    }

    while(!operations.empty()) {
        std::string op = operations.top();
        double second = numbers.top(); numbers.pop();
        double first = numbers.top(); numbers.pop();
        if(op == "+") {
            double value = first + second;
            numbers.push(value);
        } else if(op == "-")  {
            double value = first - second;
            numbers.push(value);
        }
        operations.pop();
    }

    return numbers.top();
}

//-----------------------------------------------------------------------------
std::string Calculator::workBrackets(const std::string &exp)
{
    std::string resString = exp;
    const std::string separators{ ")" };

    size_t end { exp.find_first_of(separators) };

    while (end != std::string::npos) {
        size_t start = end;
        while(resString[start] != '(') {
            --start;
        }
        std::string tmp = resString.substr(start + 1, end - start - 1);
        const auto &list = parseExp(tmp);
        double res = calculate(list, true);
        resString.replace(start, end - start + 1, std::to_string(res));
        end = resString.find_first_of(separators, start);
    }

    return resString;
}


