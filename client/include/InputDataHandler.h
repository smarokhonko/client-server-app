#pragma once

#include <string>
#include "Types.h"

class InputDataHandler
{
public:
    InputDataHandler(int argc, char **argv);

    bool parseAndValidateInput();

    ConnectionType getConnectionType() const;

    std::string getServerIP() const;

    int getServerPort() const;

private:
    bool isValidIP(const std::string &ip);
    
    void printHelpMenu();

private:
    int m_argc;
    char **m_argv;
    ConnectionType m_connectionType;
    std::string m_serverIP;
    int m_serverPort = -1;
};