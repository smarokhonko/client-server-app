#include "ISocketOperations.h"

class SocketOperations : public ISocketOperations
{
public:
    int socket(int domain, int type, int protocol) override;

    int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) override;

    ssize_t send(int sockfd, const void *buf, size_t len, int flags) override;

    ssize_t recv(int sockfd, void *buf, size_t len, int flags) override;
    
    int close(int fd) override;
};
