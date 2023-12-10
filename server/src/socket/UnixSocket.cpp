#include <iostream>
#include "UnixSocket.h"
#include "Constants.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/un.h>

UnixSocket::UnixSocket()
{
    remove(UNIX_SOCKET_NAME);
}
    
UnixSocket::~UnixSocket()
{
    remove(UNIX_SOCKET_NAME);
}

void UnixSocket::stop()
{
    remove(UNIX_SOCKET_NAME);
    close(m_socketFD);
}

bool UnixSocket::create()
{
    m_socketFD = socket(AF_UNIX, SOCK_STREAM, 0);

    if(m_socketFD < 0)
    {
        perror("Socket creation failed");
        return false;
    }

    return true;
}

bool UnixSocket::bindAndListen()
{
    struct sockaddr_un serverAddress;
    serverAddress.sun_family= AF_UNIX;
    strncpy(serverAddress.sun_path, UNIX_SOCKET_NAME, UNIX_SOCKET_PATH_MAX);

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

SocketInfo UnixSocket::acceptConnection()
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

void UnixSocket::closeSocket()
{
    close(m_socketFD);
}