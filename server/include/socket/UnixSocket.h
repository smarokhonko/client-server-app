#pragma once

#include "ISocket.h"

#include <functional>
#include <netinet/in.h>

class UnixSocket : public ISocket
{
public:

    UnixSocket();
        

    ~UnixSocket() override;
    
    virtual bool create() override;

    virtual bool bindAndListen() override;

    virtual SocketInfo acceptConnection() override;

    virtual void closeSocket() override;

    void stop() override;

 private:
    int m_socketFD;
    uint16_t m_port;
    sockaddr_in m_clientAddress;
    
    std::function<void(int)> m_connectionHandler;   
};