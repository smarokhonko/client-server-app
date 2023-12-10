#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "SocketOperations.h"

int SocketOperations::socket(int domain, int type, int protocol)
{
    return ::socket(domain, type, protocol);
}

int SocketOperations::connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
    return ::connect(sockfd, addr, addrlen);
}

ssize_t SocketOperations::send(int sockfd, const void *buf, size_t len, int flags)
{
    return ::send(sockfd, buf, len, flags);
}

ssize_t SocketOperations::recv(int sockfd, void *buf, size_t len, int flags)
{
    return ::recv(sockfd, buf, len, flags);
}

int SocketOperations::close(int fd)
{
    return ::close(fd);
}