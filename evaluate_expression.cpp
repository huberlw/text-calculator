#include "evaluate_expression.h"

const std::string SIN = "sin";
const std::string COS = "cos";
const std::string TAN = "tan";
const std::string COT = "cot";
const std::string LOG = "log";
const std::string LN = "ln";

const int LEFT_ASSOC = 2;

const std::map<std::string, int> OP_PREC = {{"+", 1}, {"-", 1}, {"*", 2}, {"/", 2},
                                            {"^", 3}, {SIN, 4}, {COS, 4}, {TAN, 4},
                                            {COT, 4}, {LOG, 4}, {LN, 4}};


/**
 * @brief Evaluates infix notation mathematical expressions
 * 
 * @param expression infix notation expression
 * @return double answer to expression
 */
double EvaluateExpression::evaluate(std::string expression)
{
    return rpn(shunting_yard(get_tokens(expression)));
}


/**
 * @brief Parses infix notation equation into tokens
 * 
 * @param expression infix notation expression
 * @return std::vector<std::string> expression parsed into tokens
 */
std::vector<std::string> EvaluateExpression::get_tokens(std::string expression)
{
    // tokens should be broken into operators, numbers, or functions
    std::vector<std::string> tokens;

    // whether binary operators are allowed or not
    bool allow_binary = false;

    // number of brackets/parentheses left open
    int open_brackets = 0;
    int open_parenthesis = 0;

    // whether the brackets/parentheses need to be filled or not
    bool need_fill = false;

    // get tokens
    for (int i = 0; i < expression.length(); i++)
    {
        // check for blank space
        if (expression[i] != ' ')
        {
            // check for number
            if (isdigit(expression[i]) || expression[i] == '.')
            {
                // brackets/parentheses no longer empty
                if (need_fill)
                    need_fill = false;

                // allow binary operators
                allow_binary = true;

                int len = 1;

                // get length of number
                while (isdigit(expression[i+len]) || expression[i+len] == '.')
                    len++;
                
                // get number as string
                std::string toke = expression.substr(i, len);

                // ensure string is valid number
                try
                {
                    double test = std::stod(toke);
                }
                catch (std::invalid_argument& ia)
                {
                    tokens.clear();
                    return tokens;
                }

                tokens.push_back(toke);

                i += len - 1;
            }
            // check for unary operator
            else if (expression[i] == '-' && !allow_binary)
            {
                tokens.push_back("-1");
                tokens.push_back("*");
            }
            // check for binary operator
            else if (expression[i] == '*' || expression[i] == '/')
            {
                if (allow_binary)
                {
                    tokens.push_back(expression.substr(i, 1));
                    allow_binary = false;
                }
                else
                {
                    tokens.clear();
                    return tokens;
                }
            }
            else if (expression[i] == '+' || expression[i] == '-')
            {
                if (allow_binary)
                {
                    tokens.push_back(expression.substr(i, 1));
                    allow_binary = false;
                }
                else
                {
                    tokens.clear();
                    return tokens;
                }
            }
            // check for parenthesis/bracket
            else if (expression[i] == '(')
            {
                tokens.push_back("(");
                open_parenthesis++;
                need_fill = true;
            }
            else if (expression[i] == ')')
            {
                // invalid expression
                if (need_fill)
                {
                    tokens.clear();
                    return tokens;
                }

                // allow binary operators
                allow_binary = true;

                tokens.push_back(")");
                open_parenthesis--;
            }
            else if (expression[i] == '{')
            {
                tokens.push_back("{");
                open_brackets++;
                need_fill = true;
            }
            else if (expression[i] == '}')
            {
                // invalid expression
                if (need_fill)
                {
                    tokens.clear();
                    return tokens;
                }

                // allow binary operators
                allow_binary = true;

                tokens.push_back("}");
                open_brackets--;
            }
            // check for function
            else if (expression[i] == '^')
            {
                tokens.push_back("^");
                need_fill = true;
            }
            else if (expression.substr(i, 3) == SIN)
            {
                tokens.push_back(SIN);
                need_fill = true;
                i += 2;
            }
            else if (expression.substr(i, 3) == COS)
            {
                tokens.push_back(COS);
                need_fill = true;
                i += 2;
            }
            else if (expression.substr(i, 3) == TAN)
            {
                tokens.push_back(TAN);
                need_fill = true;
                i += 2;
            }
            else if (expression.substr(i, 3) == COT)
            {
                tokens.push_back(COT);
                need_fill = true;
                i += 2;
            }
            else if (expression.substr(i, 3) == LOG)
            {
                tokens.push_back(LOG);
                need_fill = true;
                i += 2;
            }
            else if (expression.substr(i, 2) == LN)
            {
                tokens.push_back(LN);
                need_fill = true;
                i += 1;
            }
            // invalid expression
            else 
            {
                tokens.clear();
                return tokens;
            }
        }
    }

    if (open_parenthesis != 0 || open_brackets != 0)
        tokens.clear();

    return tokens;
}


/**
 * @brief Transforms infix notation epxressions to posfix notation using the Shunting Yard algorithm
 * 
 * @param tokens infix notation expression parsed into tokens
 * @return std::queue<std::string> postfix notation expression
 */
std::queue<std::string> EvaluateExpression::shunting_yard(std::vector<std::string> tokens)
{
    // operator stack and output queue
    std::stack<std::string> opStack;
    std::queue<std::string> outQueue;

    while (tokens.size() > 0)
    {
        std::string token = tokens.front();
        tokens.erase(tokens.begin());

        // token is number
        if (isdigit(token[0]) || token[0]  == '.')
        {
            outQueue.push(token);
        }
        // token is operator
        else if (OP_PREC.find(token) != OP_PREC.end())
        {
            while (opStack.size() > 0)
            {
                std::map<std::string, int>::const_iterator stack_pos = OP_PREC.find(opStack.top());
                std::map<std::string, int>::const_iterator pos = OP_PREC.find(token);

                // pop from op_stack if not left parenthesis and top of op_stack has greater precedence
                // or if same precedence and token is left associative
                if (stack_pos->first != "(")
                {
                    if ((pos->second < stack_pos->second) ||
                        (stack_pos->second == pos->second && pos->second <= LEFT_ASSOC))
                    {
                        outQueue.push(stack_pos->first);
                        opStack.pop();
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }

            opStack.push(token);
        }
        else if (token == "(" || token == "{")
        {
            opStack.push(token);
        }
        else if (token == ")" || token == "}")
        {
            // get closing bracket/parenthesis
            std::string closing;

            if (token == ")")
                closing = "(";
            else
                closing = "{";

            while (opStack.top() != closing)
            {
                outQueue.push(opStack.top());
                opStack.pop();
            }

            opStack.pop();
        }
    }

    // pop remaining items from the operator stack into output queue
    while (opStack.size() > 0)
    {
        outQueue.push(opStack.top());
        opStack.pop();
    }

    return outQueue;
}


/**
 * @brief Uses Reverse Polish Notation (RPN) to evaluate mathematical expressions
 * 
 * @param output output queue from Shunting Yard algorithm
 * @return double answer to expression
 */
double EvaluateExpression::rpn(std::queue<std::string> output)
{
    std::stack<int> opStack;

    while (output.size() > 0)
    {
        std::string token = output.front();
        output.pop();

        // check for operator, else number
        if (OP_PREC.find(token) != OP_PREC.end())
        {
            std::map<std::string, int>::const_iterator pos = OP_PREC.find(token);

            if (pos->second <= LEFT_ASSOC)
            {
                double first = opStack.top();
                opStack.pop();
                double second = opStack.top();
                opStack.pop();

                double result;

                if (token == "+")
                {
                    result = first + second;
                }
                else if (token == "-")
                {
                    result = first - second;
                }
                else if (token == "*")
                {
                    result = first * second;
                }
                else if (token == "/")
                {
                    result = first / second;
                }
            }
            else
            {
                double first = opStack.top();
                opStack.pop();

                double result;

                if (token == "^")
                {

                }
                else if (token == SIN)
                {

                }
                else if (token == COS)
                {
                    
                }
                else if (token == TAN)
                {
                    
                }
                else if (token == COT)
                {
                    
                }
                else if (token == LOG)
                {
                    
                }
                else if (token == LN)
                {
                    
                }
            }
        }
        else
        {
           try
            {
                opStack.push(std::stod(token));
            }
            catch (std::invalid_argument& ia)
            {
                return 0;
            } 
        }
    }

    return 0;
}


int main()
{
    std::string arr[] = {"3+4*2/(1-5)^(2^(3))",
                        "sin(cos(2)/3*5)"};

    for (int i = 0; i < 2; i++)
    {
        std::vector<std::string> bro = EvaluateExpression::get_tokens(arr[i]);
        std::queue<std::string> t = EvaluateExpression::shunting_yard(bro);

        while (t.size() > 0)
        {
            std::cout << t.front() << ", ";
            t.pop();
        }

        std::cout << std::endl;
    }
    

    return 0;
}