#include <stack>
#include <queue>
#include <vector>
#include <string>
#include <stdbool.h>


class EvaluateExpression
{
    public:
        double evaluate(std::string);

    private:
        std::vector<std::string> get_tokens(std::string);
        std::queue<std::string> shunting_yard(std::vector<std::string>);
        double rpn(std::queue<std::string>);
};