#include <gtest/gtest.h>
#include "gmock/gmock.h"

#include <memory>

#include "ISocketOperations.h"
#include "InetSocket.h"

class MockSocketOperations : public ISocketOperations {
public:
    MOCK_METHOD(int, socket, (int domain, int type, int protocol), (override));
    MOCK_METHOD(int, connect, (int sockfd, const struct sockaddr* addr, socklen_t addrlen), (override));
    MOCK_METHOD(ssize_t, send, (int sockfd, const void* buf, size_t len, int flags), (override));
    MOCK_METHOD(ssize_t, recv, (int sockfd, void* buf, size_t len, int flags), (override));
    MOCK_METHOD(int, close, (int fd), (override));
};

using ::testing::_;
using ::testing::Return;
using ::testing::SetErrnoAndReturn;
using ::testing::WithArg;
using ::testing::DoAll;
using ::testing::SetArrayArgument;

TEST(InetSocketTest, TestConnectionSuccessful)
{
    const char* serverAddress = "127.0.0.1";
    int serverPort = 8080;
    auto mockSocketOps = std::make_shared<MockSocketOperations>();
    
    EXPECT_CALL(*mockSocketOps, connect(_, _, _)).WillOnce(Return(0));
    EXPECT_CALL(*mockSocketOps, close(_)).WillOnce(Return(0));

    InetSocket socket(serverAddress, serverPort, std::move(mockSocketOps));
    EXPECT_NO_THROW(socket.start());
}

TEST(InetSocketTest, TestConnectionFailure)
{
    const char* serverAddress = "127.0.0.1";
    int serverPort = 8080;
    auto mockSocketOps = std::make_shared<MockSocketOperations>();
    
    EXPECT_CALL(*mockSocketOps, connect(_, _, _)).WillOnce(SetErrnoAndReturn(ECONNREFUSED, -1));
    EXPECT_CALL(*mockSocketOps, close(_)).WillOnce(Return(0));

    InetSocket socket(serverAddress, serverPort, std::move(mockSocketOps));
    EXPECT_THROW(socket.start(), std::runtime_error);
}

TEST(InetSocketTest, TestSendSuccess)
{
    const char* serverAddress = "127.0.0.1";
    int serverPort = 8080;
    auto mockSocketOps = std::make_shared<MockSocketOperations>();
    
    EXPECT_CALL(*mockSocketOps, connect(_, _, _)).WillOnce(Return(0));
    EXPECT_CALL(*mockSocketOps, send(_, _, _, _)).WillOnce(Return(4));
    EXPECT_CALL(*mockSocketOps, close(_)).WillOnce(Return(0));

    InetSocket socket(serverAddress, serverPort, std::move(mockSocketOps));
    socket.start(); // Assume successful start
    EXPECT_TRUE(socket.send("Test"));
}

TEST(InetSocketTest, TestSendFailure)
{
    const char* serverAddress = "127.0.0.1";
    int serverPort = 8080;
    auto mockSocketOps = std::make_shared<MockSocketOperations>();

    EXPECT_CALL(*mockSocketOps, connect(_, _, _)).WillOnce(Return(0));
    EXPECT_CALL(*mockSocketOps, send(_, _, _, _)).WillOnce(Return(-1));
    EXPECT_CALL(*mockSocketOps, close(_)).WillOnce(Return(0));

    InetSocket socket(serverAddress, serverPort, std::move(mockSocketOps));
    socket.start(); // Assume successful start
    EXPECT_FALSE(socket.send("Test"));
}


TEST(InetSocketTest, TestReceiveFailure)
{
    const char* serverAddress = "127.0.0.1";
    int serverPort = 8080;
    auto mockSocketOps = std::make_shared<MockSocketOperations>();

    EXPECT_CALL(*mockSocketOps, connect(_, _, _)).WillOnce(Return(0));
    EXPECT_CALL(*mockSocketOps, recv(_, _, _, _)).WillOnce(SetErrnoAndReturn(ECONNRESET, -1));
    EXPECT_CALL(*mockSocketOps, close(_)).WillOnce(Return(0));

    InetSocket socket(serverAddress, serverPort, std::move(mockSocketOps));
    socket.start(); // Assume successful start
    EXPECT_THROW(socket.receive(), std::runtime_error);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}