#include <string>
#include <iostream>


class HandleInput
{
    public:
        static std::string get_input();
        static void check_input(std::string, bool&);
        static void manual();
};