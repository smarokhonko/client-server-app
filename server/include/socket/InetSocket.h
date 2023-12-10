#pragma once

#include "ISocket.h"

#include <functional>
#include <netinet/in.h>

class InetSocket : public ISocket
{
public:

    InetSocket(const std::string& serverIP, const int port);

    ~InetSocket() override;

    
    virtual bool create() override;

    virtual bool bindAndListen() override;

    virtual SocketInfo acceptConnection() override;

    virtual void closeSocket() override;

    void stop() override;

 private:
    std::string m_serverIP;
    int m_socketFD;
    uint16_t m_port;
    sockaddr_in m_clientAddress;
};