#pragma once

#include <memory>
#include "Types.h"
#include "ISocket.h"
#include "ISocketOperations.h"

class ISocketFactory
{
public:

    virtual ~ISocketFactory(){}
    
    virtual std::unique_ptr<ISocket> create(const ConnectionType&, const char* serverAddress, const int serverPort, const std::string& unixFileName, std::shared_ptr<ISocketOperations> socketOperation) = 0;
};