cmake_minimum_required(VERSION 3.20)
project(TCP_chat_general)

file(GLOB_RECURSE SOURCES *.cpp)
list(POP_BACK SOURCES)

add_subdirectory(socket)

add_library(tcp_general STATIC ${SOURCES})
target_include_directories(tcp_general PUBLIC .)

target_link_libraries(tcp_general PUBLIC tcp_socket)
