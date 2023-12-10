#include <iostream>
#include <unistd.h>

#include "ReadFromConsole.h"

ReadFromConsole::~ReadFromConsole()
{
}

std::string ReadFromConsole::read()
{
    std::string line = nonBlockingGetline(1, 0);
    
    return line;
}

bool ReadFromConsole::isDataAvailable(int fd, int timeout_sec, int timeout_usec)
{
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(fd, &fds);

    struct timeval timeout;
    timeout.tv_sec = timeout_sec;
    timeout.tv_usec = timeout_usec;

    return select(fd + 1, &fds, nullptr, nullptr, &timeout) > 0;
}

std::string ReadFromConsole::nonBlockingGetline(int timeout_sec, int timeout_usec)
{
    std::string line;

    if (isDataAvailable(STDIN_FILENO, timeout_sec, timeout_usec))
    {
        std::getline(std::cin, line);
    }

    return line;
}