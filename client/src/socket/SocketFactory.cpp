#include "SocketFactory.h"
#include "InetSocket.h"
#include "UnixSocket.h"

std::unique_ptr<ISocket> SocketFactory::create(const ConnectionType& type, const char* serverAddress, const int serverPort, const std::string& unixFileName, std::shared_ptr<ISocketOperations> socketOperation)
{
    switch(type)
    {
        case ConnectionType::INET:
            return std::make_unique<InetSocket>(serverAddress, serverPort, socketOperation);
        case ConnectionType::UNIX:
            return std::make_unique<UnixSocket>(unixFileName, socketOperation);    
    }

    return nullptr;
}
