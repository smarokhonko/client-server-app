#pragma once

#include <cstring>
#include <memory>

#include "ISocket.h"

#include "ISocketOperations.h"

class InetSocket : public ISocket
{
public:
    explicit InetSocket(const char* serverAddress, int serverPort, std::shared_ptr<ISocketOperations> socketOperation);

    ~InetSocket();

    void start() override;

    void stop() override;

    bool send(const std::string& input) override;

    std::string receive() override;

 private:
    void closeSocket();  

private:
    const char* m_serverAddress;
    int m_serverPort;

    int m_socketFD;

    std::shared_ptr<ISocketOperations> m_socketOperation;
};
