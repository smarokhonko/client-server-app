#pragma once

#include <string>
#include <sys/socket.h>
#include <sys/un.h>
#include <memory>

#include "ISocket.h"
#include "ISocketOperations.h"

class UnixSocket : public ISocket
{
public:
    explicit UnixSocket(const std::string& socketPath, std::shared_ptr<ISocketOperations> socketOperation);

    virtual ~UnixSocket();

    void start();

    void stop();

    bool send(const std::string& input);

    std::string receive();

 private:
    void closeSocket();   

private:
    std::string m_socketPath;
    int m_socketFD;
    struct sockaddr_un m_socketAddress;

    std::shared_ptr<ISocketOperations> m_socketOperation;
};