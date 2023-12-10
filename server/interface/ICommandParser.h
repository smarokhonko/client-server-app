#pragma once

#include <string>

class ICommandParser
{
public:
    virtual ~ICommandParser() {}
    
    virtual std::tuple<std::string, std::string, std::string> parse(const std::string&) = 0;
};