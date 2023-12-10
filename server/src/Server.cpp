#include <iostream>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <thread>
#include <mutex>
#include <vector>
#include <string>

#include "InetSocket.h"
#include "UnixSocket.h"

#include "Server.h"
#include "CommandParser.h"

#include "SignalHandler.h"
#include "Constants.h"


Server::Server(const std::string& serverIP, const int serverPort)
    : m_serverIP(serverIP)
    , m_serverPort(serverPort)
    , m_commandParser(std::make_unique<CommandParser>())
{
    m_socketProvider.emplace_back(std::make_shared<UnixSocket>());
    m_socketProvider.emplace_back(std::make_shared<InetSocket>(serverIP, serverPort));   
}

Server::~Server()
{
}

void Server::start()
{
    for (const auto& socket : m_socketProvider)
    {
        if(!socket->create())
            return;

        if(!socket->bindAndListen())
            return;
    }

    std::thread handleClientConnectionsThread(&Server::handleClientConnections, this);
    handleClientConnectionsThread.detach();

    keepMainThread();
}

void Server::stop()
{
    m_stopFlag = true;

    m_clientTracker.closeAllClients();

    for (const auto& socket : m_socketProvider)
    {
        socket->stop();
    }
}

void Server::handleClientConnections()
{
    // Create a thread for each socket provider
    for (const auto& socket : m_socketProvider)
    {
        std::thread([&, socket]()
        {
            while (true)
            {
                const SocketInfo socketInfo = socket->acceptConnection();

                if (socketInfo.socket == -1)
                {
                    return;
                }

                if (socketInfo.socket != -1)
                {
                    m_clientTracker.addClient(socketInfo);

                    std::thread(
                        [&](int socket)
                        {
                            handleClient(socket);
                            m_clientTracker.removeDisconnectedClients();
                        }, socketInfo.socket).detach();
                }
            }
        }).detach();
    }
}

void Server::processCommand(const std::string& input, int clientSocket)
{
    std::string command, key, value;

    std::tie(command, key, value) = m_commandParser->parse(input);

    if(command == "put")
    {
        m_inMemoryKeyValueStorage.put(key, value);
    }
    else if(command == "get")
    {
        std::string value;
        bool found = m_inMemoryKeyValueStorage.get(key, value);

        if(found)
        {
            send(clientSocket, value.data(), value.size(), 0);
        }
        else
        {
            std::string keyNotFound = "key " + key + " is not found!!!";
            send(clientSocket, keyNotFound.data(), keyNotFound.size(), 0);
        }
    }
}

void Server::handleClient(int clientSocket)
{
    std::vector<char> buffer(BUFFER_SIZE);
    ssize_t bytesRead;

    while ((bytesRead = recv(clientSocket, buffer.data(), sizeof(buffer), 0)) > 0)
    {  
        std::string receivedData(buffer.begin(), buffer.begin() + bytesRead);

        processCommand(receivedData, clientSocket);
    }
    
    //close(clientSocket);
}

void Server::keepMainThread()
{
    while (!m_stopFlag);

    


}
