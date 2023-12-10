#pragma once

#include <netinet/in.h>
#include <memory>
#include <vector>
#include <mutex>
#include <signal.h>
#include <atomic>

#include "ISocket.h"
#include "ClientTracker.h"
#include "InMemoryKeyValueStorage.h"

class ICommandParser;

class Server
{
public:
    Server(const std::string& serverIP, const int serverPort);

    ~Server();

    void start();

    void stop();

private:
    int acceptClient();

    void handleClientConnections();

    void handleClient(int clientSocket);

    void processCommand(const std::string& input, int clientSocket);

    void keepMainThread();

private:
    std::string m_serverIP;
    int m_serverPort;

    std::unique_ptr<ICommandParser> m_commandParser; 

    std::vector<std::shared_ptr<ISocket>> m_socketProvider;

    ClientTracker m_clientTracker;
    InMemoryKeyValueStorage m_inMemoryKeyValueStorage;

    std::atomic_bool m_stopFlag = false;
};