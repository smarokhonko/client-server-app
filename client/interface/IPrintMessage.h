#pragma once

#include <string>

class IPrintMessage
{
public:
    virtual ~IPrintMessage() {}
    
    virtual void print(const std::string&) = 0;
};