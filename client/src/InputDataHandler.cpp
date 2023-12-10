#include <getopt.h>
#include <iostream>
#include <regex>

#include "InputDataHandler.h"

InputDataHandler::InputDataHandler(int argc, char **argv)
    : m_argc(argc)
    , m_argv(argv)
{
}

bool InputDataHandler::parseAndValidateInput()
{
    // Check if any arguments are provided
    if (m_argc == 1)
    {
        std::cerr << "No arguments provided. Please provide valid arguments." << std::endl;

        printHelpMenu();

        return false;
    }

    int opt;

    while (true)
    {
        int option_index = 0;

        static struct option long_options[] = {
            {"help", no_argument, 0, 'h'},
            {0, 0, 0, 0}};

        opt = getopt_long(m_argc, m_argv, "t:i:p:", long_options, &option_index);

        if (opt == -1)
        {
            std::cerr << "No arguments provided. Please provide valid arguments." << std::endl;
            printHelpMenu();
            break;
        }

        switch (opt)
        {
        case 't':
            if (std::string(optarg) == "inet")
            {
                m_connectionType = ConnectionType::INET;
            }
            else if (std::string(optarg) == "unix")
            {
                m_connectionType = ConnectionType::UNIX;
            }
            else
            {
                std::cerr << "Invalid connection type specified: " << optarg << std::endl;

                printHelpMenu();

                return false;
            }
            break;
        case 'i':
            if (m_connectionType == ConnectionType::INET)
            {
                m_serverIP = optarg;
            }
            break;
        case 'p':
            if (m_connectionType == ConnectionType::INET)
            {
                m_serverPort = std::stoi(optarg);
            }
            break;
        case 'h':
            printHelpMenu();
            return false;
        case '?':
        default:
            printHelpMenu();
            return false;
        }
    }

    if (m_connectionType == ConnectionType::INET)
    {
        if (!isValidIP(m_serverIP) || m_serverPort <= 0 || m_serverPort > 65535)
        {
            std::cerr << "Invalid input data. Please check your arguments and try again." << std::endl;
            printHelpMenu();
            return false;
        }
    }
    else if (m_connectionType == ConnectionType::UNIX)
    {
        if (!m_serverIP.empty() || m_serverPort != -1)
        {
            return false;
        }
    }

    return true;
}

ConnectionType InputDataHandler::getConnectionType() const
{
    return m_connectionType;
}

std::string InputDataHandler::getServerIP() const
{
    return m_serverIP;
}

int InputDataHandler::getServerPort() const
{
    return m_serverPort;
}

bool InputDataHandler::isValidIP(const std::string &ip)
{
    const std::regex pattern(
        "^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
        "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
        "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
        "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");

    return std::regex_match(ip, pattern);
}

void InputDataHandler::printHelpMenu()
{
    std::cout << "Usage: client " << " [options]\n";
    std::cout << "Options:\n";
    std::cout << "  -t <inet|unix>        Specify the connection type (default: unix)\n";
    std::cout << "  -i <server_ip>        Specify the server IP address (default: 127.0.0.1)\n";
    std::cout << "  -p <server_port>      Specify the server port (default: 8080)\n";
    std::cout << "  --help                Display this help menu\n";
    std::cout << "Examples:\n";
    std::cout << "  ./client              use by default 127.0.0.1:8080\n";
    std::cout << "  ./client -t inet -i 127.0.0.1 -p 8080\n";
    std::cout << "  ./client -t unix\n";
}