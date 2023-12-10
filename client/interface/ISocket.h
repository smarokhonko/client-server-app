#pragma once 

class ISocket
{
public:
    virtual ~ISocket() {}
    
    virtual void start() = 0;

    virtual void stop() = 0;

    virtual bool send(const std::string& input) = 0;

    virtual std::string receive() = 0;
};