#include <iostream>
#include <vector>

#include "PrintToConsole.h"

void PrintToConsole::print(const std::string& str)
{
    if(!str.empty())
        std::cout << "response:" << str << std::endl;
}