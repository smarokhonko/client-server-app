
#pragma once

#include <string>
#include <stdexcept>
#include <netinet/in.h>

class ISocketOperations
{
public:
    virtual ~ISocketOperations() = default;

    virtual int socket(int domain, int type, int protocol) = 0;

    virtual int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) = 0;

    virtual ssize_t send(int sockfd, const void *buf, size_t len, int flags) = 0;

    virtual ssize_t recv(int sockfd, void *buf, size_t len, int flags) = 0;

    virtual int close(int fd) = 0;
};