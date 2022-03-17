cmake_minimum_required(VERSION 3.20)
project(TCP_chat)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY archive)
set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES src/*.cpp)

include_directories(includes)

add_library(TcpChat STATIC ${SOURCES})

add_executable(Server ServerSide.cpp)
add_executable(Client ClientSide.cpp)

target_link_libraries(Server TcpChat)
target_link_libraries(Client TcpChat)
