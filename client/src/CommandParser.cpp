#include <sstream>
#include <iostream>

#include "CommandParser.h"

static void printHelp()
{
    std::cout << std::endl;
    std::cout << "Valid template: " << std::endl;
    std::cout << "  put key value" << std::endl;
    std::cout << "  OR"<< std::endl;
    std::cout << "  get key" << std::endl;
}

bool CommandParser::isValid(const std::string& input)
{
    std::istringstream iss(input);

    std::string command, key, value;

    iss >> command;

    if (command == "put") 
    {
        // Read the key and value
        if (iss >> key >> value) 
        {
            return true;
        }
    }
    else if (command == "get") 
    {
         // Read the key and value
        if ((iss >> key) && iss.eof()) 
        {
            return true;
        }
    }
    else if(command == "exit" || command == "quit")
    {
        return true;
    }
    else if(!command.empty())
    {
        std::cout << input << " - is invalid command!!!" << std::endl;

        printHelp();
    }

    
    return false;
}