#pragma once

#include <tuple>

#include "ICommandParser.h"

class CommandParser : public ICommandParser
{
public:
    std::tuple<std::string, std::string, std::string> parse(const std::string&) override;
};