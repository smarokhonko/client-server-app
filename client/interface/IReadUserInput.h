#pragma once

#include <string>

//Every class who wants to implement its own reading stretagy has to implement IReadUserInput
//in this way Client would apply different reading strategy, like reading from different sources (console, file: json & xml, etc.)

class IReadUserInput
{
public:
    virtual ~IReadUserInput(){}

    virtual std::string read() = 0;
};