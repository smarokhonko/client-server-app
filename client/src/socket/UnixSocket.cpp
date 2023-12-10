#include <iostream>
#include <unistd.h>
#include <cstring>
#include <stdexcept>
#include <vector>

#include "UnixSocket.h"
#include "Constants.h"

UnixSocket::UnixSocket(const std::string& socketPath, std::shared_ptr<ISocketOperations> socketOperation)
    : m_socketPath(socketPath)
    , m_socketFD(INVALID_SOCKET)
    , m_socketOperation(socketOperation)
{

}

UnixSocket::~UnixSocket()
{
    closeSocket();
}

void UnixSocket::start()
{
    m_socketFD = m_socketOperation->socket(AF_UNIX, SOCK_STREAM, 0);

    if (m_socketFD == INVALID_SOCKET)
    {
        throw std::runtime_error("Error creating socket.");
    }

    m_socketAddress.sun_family = AF_UNIX;

    std::strncpy(m_socketAddress.sun_path, m_socketPath.c_str(), sizeof(m_socketAddress.sun_path) - 1);

    if (m_socketOperation->connect(m_socketFD, (struct sockaddr*)&m_socketAddress, sizeof(m_socketAddress)) == INVALID_SOCKET)
    {
        throw std::runtime_error("Connection failed.");
    }

    std::cout << "UnixSocket: ready to communicate" << std::endl;
    std::cout << "........................................." << std::endl;
}

void UnixSocket::stop()
{   
    closeSocket();
}

bool UnixSocket::send(const std::string& input)
{
    ssize_t bytesSent = m_socketOperation->send(m_socketFD, input.c_str(), input.size(), 0);

    if (bytesSent == INVALID_SOCKET)
    {
        std::cerr << "Failed to send data: " << strerror(errno) << std::endl;

        stop();

        return false;
    }

    //std::cout << "send: " << input << std::endl;

    return true;
}

std::string UnixSocket::receive()
{
    std::vector<char> buffer(BUFFER_SIZE);

    ssize_t bytesReceived = m_socketOperation->recv(m_socketFD, buffer.data(), sizeof(buffer), 0);
    if (bytesReceived == INVALID_SOCKET)
    {
        std::cerr << "Failed to receive data: " << strerror(errno) << std::endl;

        stop();

        return "";
    }
    else if (bytesReceived == 0)
    {
        std::cout << "Connection with server terminated. Exiting..." << std::endl;

        stop();

        return "";
    }

    return std::string(buffer.begin(), buffer.end());
}

void UnixSocket::closeSocket()
{
    if (m_socketFD != INVALID_SOCKET)
    {
        m_socketOperation->close(m_socketFD);

        m_socketFD = INVALID_SOCKET;
    }
}