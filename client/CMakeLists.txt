cmake_minimum_required(VERSION 3.10)

project(client VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)



set(SOURCES
    src/Client.cpp
    src/InputDataHandler.cpp
    src/PrintToConsole.cpp
    src/ReadFromConsole.cpp
    src/SignalHandler.cpp
    src/CommandParser.cpp
    src/SocketOperations.cpp
    src/socket/InetSocket.cpp
    src/socket/UnixSocket.cpp
    src/socket/SocketFactory.cpp
    types/src/Types.cpp
)

add_executable(client main.cpp ${SOURCES})

target_include_directories(client PRIVATE
    include
    include/socket
    interface
    types/include
    test
)

# Add the -g flag to include debugging information
target_compile_options(client PRIVATE -g)

add_subdirectory(test)

