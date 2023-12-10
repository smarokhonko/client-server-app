#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>  // for fcntl
#include <stdexcept>
#include <sys/select.h>

#include "InetSocket.h"
#include "Constants.h"

InetSocket::InetSocket(const char* serverAddress, int serverPort, std::shared_ptr<ISocketOperations> socketOperation)
    : m_serverAddress(serverAddress)
    , m_serverPort(serverPort)
    , m_socketFD(INVALID_SOCKET)
    , m_socketOperation(socketOperation)
{

}

InetSocket::~InetSocket()
{
    closeSocket();
}

 void InetSocket::start()
{
    m_socketFD = socket(AF_INET, SOCK_STREAM, 0);

    if (m_socketFD == INVALID_SOCKET)
    {
        throw std::runtime_error("Error creating socket.");
    }
    
    sockaddr_in socketAddress;
    socketAddress.sin_family = AF_INET;
    socketAddress.sin_port = htons(m_serverPort);
    
    if (inet_pton(AF_INET, m_serverAddress, &socketAddress.sin_addr) <= 0)
    {
        throw std::invalid_argument("Invalid address.");
    }

    if (m_socketOperation->connect(m_socketFD, (struct sockaddr*)&socketAddress, sizeof(socketAddress)) == -1)
    {
        throw std::runtime_error("Connection failed.");
    }

    std::cout << "InetSocket:: ready to communicate" << std::endl;
    std::cout << "........................................." << std::endl;
}

void InetSocket::stop()
{
    closeSocket();
}

bool InetSocket::send(const std::string& input)
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

std::string InetSocket::receive()
{
    const size_t bufferSize = BUFFER_SIZE; // Change as needed
    char buffer[bufferSize];
    std::string data;

    fd_set readfds;
    struct timeval timeout;

    // Set the socket to non-blocking mode
    int flags = fcntl(m_socketFD, F_GETFL, 0);

    if (fcntl(m_socketFD, F_SETFL, flags | O_NONBLOCK) < 0)
    {
        throw std::runtime_error("Error setting socket to non-blocking");
    }

    while (true) 
    {
        // Clear the read set
        FD_ZERO(&readfds);

        // Add descriptor to the read set
        FD_SET(m_socketFD, &readfds);

        // Set timeout
        timeout.tv_sec = 0;
        timeout.tv_usec = 5000;

        // Use select to wait for data
        int activity = select(m_socketFD + 1, &readfds, nullptr, nullptr, &timeout);

        if (activity < 0)
        {
            throw std::runtime_error("Error in select()");
        }
        else if (activity == 0)
        {
            break;
        }

        // Clear the buffer
        std::memset(buffer, 0, bufferSize);

        // Receive data
        ssize_t bytesReceived = m_socketOperation->recv(m_socketFD, buffer, bufferSize - 1, 0);
        
        if (bytesReceived < 0)
        {
            // Since it's non-blocking, it would return EWOULDBLOCK when no more data to read
            if (errno == EWOULDBLOCK)
            {
                break; // No data received, continue
            } 
            else
            {
                throw std::runtime_error("Error in recv(): " + std::string(std::strerror(errno)));
            }
        }
        else if (bytesReceived == 0)
        {
            // Connection closed
            break;
        }
        else
        {
            // Add received data to string
            data.append(buffer, bytesReceived);
        }
    }

    return data;
}

void InetSocket::closeSocket()
{
    if (m_socketFD != INVALID_SOCKET)
    {
        m_socketOperation->close(m_socketFD);
        m_socketFD = INVALID_SOCKET;
    }
}