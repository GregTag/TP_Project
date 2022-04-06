cmake_minimum_required(VERSION 3.20)
project(TCP_socket)

set(SOURCES socket.cpp log.cpp)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)
find_package(Boost 1.68 REQUIRED)

add_library(tcp_socket STATIC ${SOURCES})

target_link_libraries(tcp_socket PUBLIC Boost::boost Threads::Threads)