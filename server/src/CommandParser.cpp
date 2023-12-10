#include <sstream>
#include <iostream>

#include "CommandParser.h"

std::tuple<std::string, std::string, std::string> CommandParser::parse(const std::string& input)
{
    std::istringstream iss(input);

    std::string command, key, value, resultValue;

    iss >> command;

    if (command == "put") 
    {
        iss >> key;

        while(!iss.eof())
        {
            iss >> value;
            resultValue += " " + value;
        }
    }
    else if (command == "get") 
    {
        iss >> key;
    }
    
    return std::make_tuple(command, key, resultValue);
}