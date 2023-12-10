#pragma once

#include <ostream>
#include <string>

#include <netinet/in.h>

struct SocketInfo
{
    int socket;
    sockaddr_in address;
};

std::ostream& operator<<(std::ostream& os, const SocketInfo& socketInfo);