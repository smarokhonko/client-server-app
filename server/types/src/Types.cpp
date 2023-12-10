#include "Types.h"
#include <arpa/inet.h>

std::ostream& operator<<(std::ostream& os, const SocketInfo& socketInfo)
{
    return os << "socketFD: " << socketInfo.socket                      <<                
                 ", addr: "   << inet_ntoa(socketInfo.address.sin_addr) <<
                 ":"          << ntohs(socketInfo.address.sin_port)
                              << std::endl;
}