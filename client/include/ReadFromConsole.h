#pragma once

#include "IReadUserInput.h"

class ReadFromConsole : public IReadUserInput
{
public:
    ~ReadFromConsole();

    std::string read() override;;

    bool isDataAvailable(int fd, int timeout_sec, int timeout_usec);

    std::string nonBlockingGetline(int timeout_sec = 0, int timeout_usec = 0);
};