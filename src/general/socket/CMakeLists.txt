cmake_minimum_required(VERSION 3.20)
project(TCP_socket)

set(SOURCES socket.cpp log.cpp)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)
find_package(Boost 1.78 REQUIRED)
find_package(OpenSSL REQUIRED)

add_library(tcp_socket STATIC ${SOURCES})

if (MSYS)
    target_link_libraries(tcp_socket PUBLIC ws2_32 wsock32)
endif(MSYS)

target_link_libraries(tcp_socket PUBLIC Boost::boost Threads::Threads OpenSSL::SSL OpenSSL::Crypto)
