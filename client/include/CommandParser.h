#pragma once

#include "ICommandParser.h"

class CommandParser : public ICommandParser
{
public:
    bool isValid(const std::string&) override;
};