#pragma once

#include <string>

class ICommandParser
{
public:
    virtual ~ICommandParser() {}
    
    virtual bool isValid(const std::string&) = 0;
};