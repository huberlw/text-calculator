#include <map>
#include <cmath>
#include <limits>
#include <stack>
#include <queue>
#include <vector>
#include <string>
#include <iostream>


class EvaluateExpression
{
    public:
        static void evaluate(std::string);

    private:
        static bool is_num(std::string);
        static std::vector<std::string> get_tokens(std::string);
        static std::queue<std::string> shunting_yard(std::vector<std::string>);
        static std::string rpn(std::queue<std::string>);
};