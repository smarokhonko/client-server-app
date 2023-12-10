#pragma once

#include <string>
#include "Types.h"

class InputDataHandler
{
public:
    InputDataHandler(int argc, char **argv);

    bool parseAndValidateInput();

    std::string getServerIP() const;

    int getServerPort() const;

private:
    bool isValidIP(const std::string &ip);
    
    void printHelpMenu();

private:
    int m_argc;
    char **m_argv;
    std::string m_serverIP;
    int m_serverPort = -1;
};