#include <iostream>
#include <unistd.h>
#include <algorithm>
#include <sys/select.h>
#include <vector>

#include "ClientTracker.h"

void ClientTracker::addClient(const SocketInfo& socketInfo)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    m_clients[socketInfo.socket] = socketInfo;

    std::cout << "SERVER: Client connected: " << socketInfo;
}

void ClientTracker::removeDisconnectedClients()
{
    std::lock_guard<std::mutex> lock(m_mutex);

    std::vector<int> disconnectedClients;

    for (const auto& clientEntry : m_clients)
    {
        int clientSocket = clientEntry.first;

        if (!isClientConnected(clientSocket))
        {
            std::cout << "SERVER: Client disconnected: " << clientEntry.second;
            
            close(clientSocket);

            disconnectedClients.push_back(clientSocket);
        }
    }

    // Remove disconnected clients from the map
    for (int clientSocket : disconnectedClients)
    {
        m_clients.erase(clientSocket);
    }
}

void ClientTracker::closeAllClients()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    
    for (const auto& clientEntry : m_clients)
    {
        int clientSocket = clientEntry.first;

        std::cout << "SERVER: Client disconnected: " << clientEntry.second;
            
        close(clientSocket);
    }
}

bool ClientTracker::isClientConnected(int clientSocket)
{
    fd_set readSet;
    FD_ZERO(&readSet);
    FD_SET(clientSocket, &readSet);

    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 100;

    int activity = select(FD_SETSIZE, &readSet, nullptr, nullptr, &timeout);
       
    if(FD_ISSET(clientSocket, &readSet))
        return false;
    
    return true;
}
