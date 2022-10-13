#include "evaluate_expression.h"

const std::string SIN = "sin";
const std::string COS = "cos";
const std::string TAN = "tan";
const std::string COT = "cot";
const std::string LOG = "log";
const std::string LN = "ln";

const int LEFT_ASSOC = 2;
const int TAKES_TWO = 3;

const std::map<std::string, int> OP_PREC = {{"+", 1}, {"-", 1}, {"*", 2}, {"/", 2},
                                            {"^", 3}, {SIN, 4}, {COS, 4}, {TAN, 4},
                                            {COT, 4}, {LOG, 4}, {LN, 4}};


/**
 * @brief Ensures string is a valid number
 * 
 * @param str strring to be tested
 * @return true string is a valid number
 * @return false string is not a valid number
 */
bool EvaluateExpression::is_num(std::string str)
{
    try
    {
        double test = std::stod(str);
        return true;
    }
    catch (std::invalid_argument)
    {
        return false;
    }
}


/**
 * @brief Evaluates infix notation mathematical expressions
 * 
 * @param expression infix notation expression
 */
void EvaluateExpression::evaluate(std::string expression)
{
    // try evaluating expression
    try
    {
        std::cout << "Result: " << rpn(shunting_yard(get_tokens(expression))) << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
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

    // unary operator checks
    bool allow_binary = false;
    bool unary_needs_num = false;
    int bracket_after = 0;

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
                if (is_num(toke))
                {
                    tokens.push_back(toke);
                    i += len - 1;

                    // close parenthesis around (-1 * x)
                    if (unary_needs_num)
                    {
                        tokens.push_back(")");
                        unary_needs_num = false;

                        while (bracket_after > 0)
                        {
                            tokens.push_back(")");
                            bracket_after--;
                        }
                    }
                }
                else
                {
                    throw std::invalid_argument("invalid number: " + toke);
                }
            }
            // check for unary operator
            else if (expression[i] == '-' && !allow_binary)
            {
                // change unary to (-1 * x)
                tokens.push_back("(");
                tokens.push_back("-1");
                tokens.push_back("*");

                if (unary_needs_num)
                {
                    bracket_after++;
                }
                else
                {
                  unary_needs_num = true;  
                }
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
                    std::string err_message = "invalid expression: invalid use of \"";
                    err_message.push_back(expression[i]);
                    err_message += ("\"");
                    throw std::invalid_argument(err_message);
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
                    std::string err_message = "invalid expression: invalid use of \"";
                    err_message.push_back(expression[i]);
                    err_message += ("\"");
                    throw std::invalid_argument(err_message);
                }
            }
            // check for parenthesis/bracket
            else if (expression[i] == '(')
            {
                // check last token for bracket
                if (tokens.size() > 0 && (tokens.back() == ")" || tokens.back() == "}"))
                {
                    tokens.push_back("*");
                    allow_binary = false;
                }

                tokens.push_back("(");
                open_parenthesis++;
                need_fill = true;
                
                if (unary_needs_num)
                {
                    unary_needs_num = false;
                    bracket_after++;
                }  
            }
            else if (expression[i] == ')')
            {
                // invalid expression
                if (need_fill)
                {
                    throw std::invalid_argument("invalid expression: empty brackets");
                }

                // allow binary operators
                allow_binary = true;

                tokens.push_back(")");
                open_parenthesis--;

                while (bracket_after > 0)
                {
                    tokens.push_back(")");
                    bracket_after--;
                }
            }
            else if (expression[i] == '{')
            {
                // check last token for bracket
                if (tokens.size() > 0 && (tokens.back() == ")" || tokens.back() == "}"))
                {
                    tokens.push_back("*");
                    allow_binary = false;
                }

                tokens.push_back("{");
                open_brackets++;
                need_fill = true;

                if (unary_needs_num)
                {
                    unary_needs_num = false;
                    bracket_after++;
                }  
            }
            else if (expression[i] == '}')
            {
                // invalid expression
                if (need_fill)
                {
                    throw std::invalid_argument("invalid expression: empty brackets");
                }

                // allow binary operators
                allow_binary = true;

                tokens.push_back("}");
                open_brackets--;

                while (bracket_after > 0)
                {
                    tokens.push_back(")");
                    bracket_after--;
                }
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
                std::string err_message = "invalid expression: unknown operator \"";
                err_message.push_back(expression[i]);
                err_message += ("\"");
                throw std::invalid_argument(err_message);
            }
        }
    }

    // check for errors
    if (open_parenthesis != 0 || open_brackets != 0)
        throw std::invalid_argument("invalid expression: unclosed brackets");
    else if (unary_needs_num)
        throw std::invalid_argument("invalid expression: invalid use of unary operator");

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
        if (is_num(token))
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
        // invalid expression
        else 
        {
            throw std::invalid_argument("invalid expression: unknown operator " + token);
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
std::string EvaluateExpression::rpn(std::queue<std::string> output)
{
    std::stack<double> opStack;

    while (output.size() > 0)
    {
        std::string token = output.front();
        output.pop();

        // check for operator, else number
        if (OP_PREC.find(token) != OP_PREC.end())
        {
            std::map<std::string, int>::const_iterator pos = OP_PREC.find(token);
            double result;

            if (pos->second <= TAKES_TWO)
            {
                if (opStack.size() >= 2)
                {
                    double second = opStack.top();
                    opStack.pop();
                    double first = opStack.top();
                    opStack.pop();

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
                        if (second != 0)
                        {
                            result = first / second;
                        }
                        else
                        {
                            throw std::invalid_argument("invalid expression: division by zero");
                        }
                    }
                    else if (token == "^")
                    {
                        result = pow(first, second);
                    }
                }
                else
                {
                    throw std::invalid_argument("invalid expression: insufficient number of values for operator");
                }
            }
            else
            {
                if (opStack.size() >= 1)
                {
                    double first = opStack.top();
                    opStack.pop();

                    if (token == SIN)
                    {
                        result = sin(first);
                    }
                    else if (token == COS)
                    {
                        result = cos(first);
                    }
                    else if (token == TAN)
                    {
                        result = tan(first);
                    }
                    else if (token == COT)
                    {
                        result = cos(first) / sin(first);
                    }
                    else if (token == LOG)
                    {
                        if (first >= 0)
                        {
                            result = log10(first);
                        }
                        else
                        {
                            throw std::invalid_argument("invalid expression: negative logarithm");
                        }
                    }
                    else if (token == LN)
                    {
                        if (first >= 0)
                        {
                            result = log(first);
                        }
                        else
                        {
                            throw std::invalid_argument("invalid expression: negative logarithm");
                        }
                    }
                }
                else
                {
                    throw std::invalid_argument("invalid expression: insufficient number of values for operator");
                }
            }

            opStack.push(result);
        }
        else
        {
           try
            {
                opStack.push(std::stod(token));
            }
            catch (std::invalid_argument)
            {
                throw std::invalid_argument("invalid expression: " + token);
            } 
        }
    }

    if (opStack.size() != 1)
        throw std::invalid_argument("invalid expression");
    
    return std::to_string(opStack.top());
}