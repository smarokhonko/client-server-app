#pragma once

#include "Types.h"

class ISocket
{
public:
    virtual ~ISocket() {};

    virtual bool create() = 0;

    virtual bool bindAndListen() = 0;

    virtual SocketInfo acceptConnection() = 0;

    virtual void closeSocket() = 0;

    virtual void stop() = 0;
};