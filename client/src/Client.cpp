#include <iostream>

#include <string>

#include "IReadUserInput.h"
#include "IPrintMessage.h"
#include "Client.h"
#include "SocketFactory.h"
#include "Constants.h"
#include "SocketOperations.h"
#include "CommandParser.h"

Client::Client( const char* serverIP, 
                        const int& serverPort, 
                        const ConnectionType& connectionType,
                        const std::string& unixFileName,
                        std::unique_ptr<IReadUserInput> readUserInput,
                        std::unique_ptr<IPrintMessage> printMessage)
    : m_serverIP(serverIP)
    , m_serverPort(serverPort)
    , m_readUserInput(std::move(readUserInput))
    , m_printMessage(std::move(printMessage))
    , m_socketFactory(std::make_unique<SocketFactory>())
    , m_socket(m_socketFactory->create(connectionType, m_serverIP, m_serverPort, unixFileName, std::make_shared<SocketOperations>()))
    , m_commandParser(std::make_unique<CommandParser>())
    , m_isRunning(true)
{
    if (!m_socket)
    {
        throw std::runtime_error("Failed to create socket.");
    }
}

Client::~Client()
{
}

void Client::start()
{
    try
    {
        m_socket->start();

        runCommunication();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void Client::stop()
{
    m_isRunning = false;

    m_socket->stop();
}

void Client::runCommunication()
{
    while (m_isRunning)
    {
        std::string input = readUserInput();

        bool validCommand = m_commandParser->isValid(input);

        if (validCommand)
        {
            if (!send(input))
            {
                return;
            }
                
            const std::string& response = receive();

            printMessage(response);
        }
    }

    std::cout << "communication end..." << std::endl;
}

std::string Client::readUserInput()
{
    return m_readUserInput->read();
}
    
bool Client::send(const std::string& input)
{
    if (input == EXIT_COMMAND || input == QUIT_COMMAND)
    {
        stop();

        return false;
    }

    return m_socket->send(input);
}

std::string Client::receive()
{
    return m_socket->receive();
}

void Client::printMessage(const std::string& response)
{
    m_printMessage->print(response);
}