#include <exception>
#include <functional>
#include <iostream>
#include <string>

///////////////////////////////////////////////////////////////////////////////
class ZeroDivException : std::exception  {
public:
    const char *what() const noexcept {
        return "Cannot divide on zer0";
    }
};

///////////////////////////////////////////////////////////////////////////////
template<typename T=int>
class Calculator {
private:
    class Div {

    public:
        Div(int *rs) : res{rs} {}
        T operator()(T a, T b) {
            if(!b) {
                throw ZeroDivException();
            }
            *res = a / b;
            return *res;
        }


    private:
        int *res;
    };

public:
    enum class Operations : char {Add = '+', Subtract = '-', Multiply = '*', Div = '/'};

public:

    operator std::string() {
        return "Expression : " + std::to_string(m_x) + " " + static_cast<char>(m_op) + " " + std::to_string(m_y) + " = "  + std::to_string(m_res);
    }

    T operator()(T x, T y, Operations op) const  {

        m_x = x;
        m_y = y;
        m_op = op;

        std::function<int(int,int)> operation;

        auto add {[this](T a, T b) {
                m_res = a + b;
                return m_res;
            }};
        auto subtract {[this](T a, T b) {
                m_res = a - b;
                return m_res;
            }};
        auto mult {[this](T a, T b) {
                m_res = a * b;
                return m_res;
            }};

        switch (op) {
        case Calculator::Operations::Subtract:
            operation = subtract;
            return operation(x, y);
        case Calculator::Operations::Multiply:
            operation = mult;
            return operation(x, y);
        case Calculator::Operations::Div:
            operation = Div(&m_res);
            return operation(x, y);
        case Operations::Add:
            operation = add;
            return operation(x, y);
        }
        return 0;
    }
private:
    mutable T m_res;
    mutable T m_x;
    mutable T m_y;
    mutable Operations m_op;
};

///////////////////////////////////////////////////////////////////////////////
int main() {


    Calculator calc;
    int x, y;
    char op;

    std::cout << "Enter x op y" << std::endl;
    std::cin >> x;
    std::cin >> op;
    std::cin >> y;

    try {
        int ret = calc(x, y, static_cast<Calculator<int>::Operations>(op));
        std::cout << ret << std::endl;
        std::cout << std::string(calc) << std::endl;
    } catch(const ZeroDivException &ex) {
        std::cout << ex.what() << std::endl;
    }

    return 0;
}
