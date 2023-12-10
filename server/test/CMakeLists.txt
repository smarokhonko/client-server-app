cmake_minimum_required(VERSION 3.10)

project(client VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable testing
enable_testing()

find_package(GTest REQUIRED)

add_executable(ServerUTests 
    InMemoryKeyValueStorage_test.cpp
    ../src/InMemoryKeyValueStorage.cpp
)

# Include directories for the test executable
target_include_directories(ServerUTests PRIVATE
    ../include
    ../include/socket
    ../interface
    ../types/include
)

target_link_libraries(ServerUTests GTest::GTest GTest::Main)

include(GoogleTest)
gtest_discover_tests(ServerUTests)

include_directories(${GTEST_INCLUDE_DIRS} ${GMOCK_INCLUDE_DIRS})
target_link_libraries(ServerUTests gtest gtest_main gmock gmock_main)





