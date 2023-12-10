#pragma once

#include <unordered_map>
#include "Types.h"

#include <mutex>

class ClientTracker
{
public:

    void addClient(const SocketInfo& socketInfo);
   
    void removeDisconnectedClients();

    void closeAllClients();

private:
    bool isClientConnected(const int clientSocket);

private:
    std::unordered_map<int, SocketInfo> m_clients;
    std::mutex m_mutex;
};
