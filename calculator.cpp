#include "handle_input.h"


/**
 * @brief Runs text based calculator
 * 
 * @return int zero
 */
int main()
{
    // print manual
    HandleInput::manual();

    // start calculator loop
    bool run_calc = true;

    while (run_calc)
    {
        std::string input = HandleInput::get_input();
        HandleInput::check_input(input, run_calc);
    }

    return 0;
}