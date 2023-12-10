#include <iostream>
#include "InetSocket.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

InetSocket::InetSocket(const std::string& serverIP, int port)
    : m_serverIP(serverIP)
    , m_port(port)
    , m_socketFD(-1)
    , m_clientAddress({})
{
}
    
InetSocket::~InetSocket()
{
}

void InetSocket::stop()
{
    close(m_socketFD);
}

bool InetSocket::create()
{
     m_socketFD = socket(AF_INET, SOCK_STREAM, 0);

    if(m_socketFD < 0)
    {
        perror("Socket creation failed");
        return false;
    }

    return true;
}

bool InetSocket::bindAndListen()
{
    struct sockaddr_in serverAddress;
    serverAddress.sin_family= AF_INET;
    serverAddress.sin_port = htons(m_port);
    serverAddress.sin_addr.s_addr = inet_addr(m_serverIP.c_str());;

    int status = bind(m_socketFD, (sockaddr*)&serverAddress, sizeof(serverAddress));

    if (status < 0)
    {
        perror("Connection failed");
        close(m_socketFD);
        return false;
    }

    status = listen(m_socketFD, SOMAXCONN);

    if (status < 0)
    {
        perror("Listen error");
        close(m_socketFD);
        return false;
    }

    return true;
}

SocketInfo InetSocket::acceptConnection()
{
    socklen_t clientAddressSize = sizeof(m_clientAddress);

    int clientSocket = accept(m_socketFD, (sockaddr*)&m_clientAddress, &clientAddressSize); //open the session with the client

    if (clientSocket < 0)
    {
        perror("Accept error");
        close(clientSocket);
        exit(EXIT_FAILURE);
    }

    return { clientSocket, m_clientAddress};
}

void InetSocket::closeSocket()
{
    close(m_socketFD);
}