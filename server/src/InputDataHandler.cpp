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
            break;
        }

        switch (opt)
        {
        case 't':
            if (std::string(optarg) != "inet")
            {
                std::cerr << "Invalid connection type specified: " << optarg << std::endl;

                printHelpMenu();

                return false;
            }
            break;
        case 'i':
            m_serverIP = optarg;
            break;
        case 'p':
            m_serverPort = std::stoi(optarg);
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

    if (!isValidIP(m_serverIP) || m_serverPort <= 0 || m_serverPort > 65535)
    {
        std::cerr << "Invalid input data. Please check your arguments and try again." << std::endl;
        printHelpMenu();
        return false;
    }

    return true;
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
    std::cout << "Usage: server " << " [options]\n";
    std::cout << "Options:\n";
    std::cout << "  -i <server_ip>        Specify the server IP address (default: 127.0.0.1)\n";
    std::cout << "  -p <server_port>      Specify the server port (default: 8080)\n";
    std::cout << "  --help                Display this help menu\n";
    std::cout << "Examples:\n";
    std::cout << "  ./server         use by default 127.0.0.1:8080\n";
    std::cout << "  ./server -t inet -i 127.0.0.1 -p 8080\n";
    std::cout << "  unix cinnection is supported by default\n";
}