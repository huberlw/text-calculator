#include "handle_input.h"
#include "evaluate_expression.h"


/**
 * @brief Gets line of user input
 * 
 * @return std::string returns input
 */
std::string HandleInput::get_input()
{
    std::string expression;

    std::cout << "\nEnter a mathematical expression:" << std::endl;
    std::getline(std::cin, expression);

    return expression;
}


/**
 * @brief Checks input and either prints the user manual or expression evaluation
 * 
 * @param expression user input
 */
void HandleInput::check_input(std::string expression, bool &run_calc)
{
    if (expression == "help")
    {
        manual();
    }
    else if (expression == "exit")
    {
        run_calc = false;
    }
    else
    {
        EvaluateExpression::evaluate(expression);
    }
}


/**
 * @brief Gives description of operactors and how to use the calculator
 */
void HandleInput::manual()
{
    // title and author
    std::cout << "CS480 Text Calculator:" << std::endl;
    std::cout << "By: Lincoln Huber" << std::endl;

    // operators
    std::cout << "\n\tAvailable Operators:" << std::endl;
    std::cout << "\t\t+ = add" << std::endl;
    std::cout << "\t\t- = subtract" << std::endl;
    std::cout << "\t\t* = multiply" << std::endl;
    std::cout << "\t\t/ = divide" << std::endl;
    std::cout << "\t\t^ = power" << std::endl;
    std::cout << "\t\tsin = sine" << std::endl;
    std::cout << "\t\tcos = cosine" << std::endl;
    std::cout << "\t\ttan = tangent" << std::endl;
    std::cout << "\t\tcot = cotangent" << std::endl;
    std::cout << "\t\tlog = logarithm base 10" << std::endl;
    std::cout << "\t\tln = natural logarithm" << std::endl;

    // brakcets
    std::cout << "\n\tAvailable Brackets:" << std::endl;
    std::cout << "\t\t() = parentheses" << std::endl;
    std::cout << "\t\t{} = braces" << std::endl;

    // warning
    std::cout << "\n\tWarnings:" << std::endl;
    std::cout << "\t\tOperators must be formatted exactly as shown above." << std::endl;
    std::cout << "\t\tIncorrect syntax will lead to an error message." << std::endl;

    // expample expressions
    std::cout << "\n\tExample Expressions:" << std::endl;
    std::cout << "\t\t3 + 4 * 2 / (1 - 5)^(2^3)" << std::endl;
    std::cout << "\t\tsin(1)^2 + 2" << std::endl;
    std::cout << "\t\t(-sin 1 + 1) (1 / -cos 1)" << std::endl;

    // help info
    std::cout << "\n\tAdditional Options:" << std::endl;
    std::cout << "\t\tTo see this manual again type \"help\"." << std::endl;
    std::cout << "\t\tTo exit this calculator type \"exit\"." << std::endl;
}