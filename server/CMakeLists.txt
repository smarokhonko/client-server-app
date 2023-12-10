cmake_minimum_required(VERSION 3.10)

project(server VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES
    src/Server.cpp
    src/ClientTracker.cpp
    src/SignalHandler.cpp
    src/InputDataHandler.cpp
    src/CommandParser.cpp
    src/InMemoryKeyValueStorage.cpp

    src/socket/InetSocket.cpp
    src/socket/UnixSocket.cpp

    types/src/Types.cpp
)

add_executable(server main.cpp ${SOURCES})

include_directories(
    include
    include/socket
    interface 
    types/include
    test
)

target_link_libraries(server PRIVATE pthread)

add_subdirectory(test)