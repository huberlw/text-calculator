#include <evaluate_expression.h>


double EvaluateExpression::evaluate(std::string expression)
{
    return rpn(shunting_yard(get_tokens(expression)));
}


std::vector<std::string> EvaluateExpression::get_tokens(std::string expression)
{
    // tokens should be broken into operators, numbers, or functions
    std::vector<std::string> tokens;

    // remove all spaces from expression
    remove(expression.begin(), expression.end(), ' ');

    /*
    NUMBERS AND OPERATORS CAN BE TYPED. FUNCTIONS CANNOT. 

    POTENTIAL ERRORS:
    (), (()), 5++5, (+), 5+, ^^, sin(), 5^
    */

    // whether binary operators are allowed or not
    bool allow_binary = false;
    
    // whether the next number will be negative
    bool neg_next = false;

    // whether the next token must be a number
    bool number_next = false;

    // number of brackets/parentheses left open
    int open_brackets = 0;
    int open_parenthesis = 0;

    // get tokens
    for (int i = 0; i < expression.length(); i++)
    {
        // check for number
        if (isdigit(expression[i]) || expression[i] == '.')
        {
            // allow binary operators
            allow_binary = true;

            int len = 1;

            // get length of number
            while (isdigit(expression[i+1]) || expression[i+1] == '.')
                len++;
            
            // get number as string
            std::string toke = expression.substr(i, len);

            // make number negative (unary operator)
            if (neg_next)
            {
                toke.insert(0, "-");
                neg_next = false;
            }

            tokens.push_back(toke);

            i += len - 1;
        }
        // check for operator
        else if (expression[i] == '*')
        {
            if (allow_binary)
            {

            }
            else
            {
                tokens.clear();
                return tokens;
            }
        }
        else if (expression[i] == '/')
        {
            if (allow_binary)
            {

            }
            else
            {
                tokens.clear();
                return tokens;
            }
        }
        else if (expression[i] == '+')
        {
            if (allow_binary)
            {

            }
            else
            {
                continue;
            }
        }
        else if (expression[i] == '-')
        {
            if (allow_binary)
            {

            }
            else
            {
                neg_next = !neg_next;
            }
        }
        // check for parenthesis/bracket
        else if (expression[i] == '(')
        {
            tokens.push_back(expression.substr(i, 1));
            open_parenthesis++;
        }
        else if (expression[i] == ')')
        {
            tokens.push_back(expression.substr(i, 1));
            open_parenthesis--;
        }
        else if (expression[i] == '{')
        {
            tokens.push_back(expression.substr(i, 1));
            open_brackets++;
        }
        else if (expression[i] == '}')
        {
            tokens.push_back(expression.substr(i, 1));
            open_brackets--;
        }
        // check for function
        else if (expression.substr(i, 4).compare("sin("))
        {
            open_parenthesis++;
            tokens.push_back("sin(");
        }
        else if (expression.substr(i, 4).compare("cos("))
        {
            open_parenthesis++;
            tokens.push_back("cos(");
        }
        else if (expression.substr(i, 4).compare("tan("))
        {
            open_parenthesis++;
            tokens.push_back("tan(");
        }
        else if (expression.substr(i, 4).compare("cot("))
        {
            open_parenthesis++;
            tokens.push_back("cot(");
        }
        else if (expression.substr(i, 4).compare("log("))
        {
            open_parenthesis++;
            tokens.push_back("log(");
        }
        else if (expression.substr(i, 3).compare("ln("))
        {
            open_parenthesis++;
            tokens.push_back("ln(");
        }
        else
        {

        }
    }

    if (open_parenthesis > 0 || open_brackets > 0)
        tokens.clear();

    return tokens;
}


std::queue<std::string> EvaluateExpression::shunting_yard(std::vector<std::string> tokens)
{
    // operator stack and output queue
    std::stack<std::string> opStack;
    std::queue<std::string> outQueue;

    for(int i = 0; i < tokens.size(); i++)
    {
        std::string token = tokens.at(i);

        if (true)
        {
            outQueue.push(token);
        }
        else if (true)
        {
            
        }
    }

    return outQueue;
}

// ALGORITHM IS FROM WIKIPEDIA
// while there are tokens to be read:
//     read a token
//     if the token is:
//     - a number:
//         put it into the output queue
//     - a function:
//         push it onto the operator stack 
//     - an operator o1:
//         while (
//             there is an operator o2 other than the left parenthesis at the top
//             of the operator stack, and (o2 has greater precedence than o1
//             or they have the same precedence and o1 is left-associative)
//         ):
//             pop o2 from the operator stack into the output queue
//         push o1 onto the operator stack
//     - a left parenthesis (i.e. "("):
//         push it onto the operator stack
//     - a right parenthesis (i.e. ")"):
//         while the operator at the top of the operator stack is not a left parenthesis:
//             {assert the operator stack is not empty}
//             /* If the stack runs out without finding a left parenthesis, then there are mismatched parentheses. */
//             pop the operator from the operator stack into the output queue
//         {assert there is a left parenthesis at the top of the operator stack}
//         pop the left parenthesis from the operator stack and discard it
//         if there is a function token at the top of the operator stack, then:
//             pop the function from the operator stack into the output queue
// /* After the while loop, pop the remaining items from the operator stack into the output queue. */
// while there are tokens on the operator stack:
//     /* If the operator token on the top of the stack is a parenthesis, then there are mismatched parentheses. */
//     {assert the operator on top of the stack is not a (left) parenthesis}
//     pop the operator from the operator stack onto the output queue


double EvaluateExpression::rpn(std::queue<std::string> output)
{

    return 0;
}