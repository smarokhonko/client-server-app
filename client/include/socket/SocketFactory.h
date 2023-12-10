#pragma once

#include "ISocketFactory.h"

class SocketFactory : public ISocketFactory
{
public:
    std::unique_ptr<ISocket> create(const ConnectionType&, const char* serverAddress, const int serverPort, const std::string& unixFileName, std::shared_ptr<ISocketOperations> socketOperation) override;
};