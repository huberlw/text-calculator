#include <map>
#include <stack>
#include <queue>
#include <vector>
#include <string>
#include <stdbool.h>
#include <iostream>


class EvaluateExpression
{
    public:
        static double evaluate(std::string);
        static std::vector<std::string> get_tokens(std::string);
        static std::queue<std::string> shunting_yard(std::vector<std::string>);

    private:
       
        static double rpn(std::queue<std::string>);
};