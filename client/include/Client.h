#pragma once

#include <string>
#include <memory>

#include "Types.h"

class IReadUserInput;
class IPrintMessage;
class ISocketFactory;
class ISocket;
class ICommandParser;

class Client
{
public:
    Client( const char* serverIP, 
            const int& serverPort,
            const ConnectionType& connectionType,
            const std::string& unixFileName,
            std::unique_ptr<IReadUserInput> readUserInput, 
            std::unique_ptr<IPrintMessage> printMessage);

    ~Client();

    void start();

    void stop();

private:

    void runCommunication();
    
    std::string readUserInput();
    
    bool send(const std::string& input);

    std::string receive();

    void printMessage(const std::string& response);

private:
    const char* m_serverIP;
    int m_serverPort;

    std::unique_ptr<IReadUserInput> m_readUserInput;
    std::unique_ptr<IPrintMessage> m_printMessage;

    std::unique_ptr<ISocketFactory> m_socketFactory;
    std::unique_ptr<ISocket> m_socket;
    std::unique_ptr<ICommandParser> m_commandParser;

    bool m_isRunning;
};
