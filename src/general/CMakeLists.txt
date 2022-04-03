cmake_minimum_required(VERSION 3.20)
project(TCP_chat_general)

file(GLOB_RECURSE SOURCES ./*.cpp)

add_subdirectory(../socket socket)

add_library(tcp_general STATIC ${SOURCES})
target_include_directories(tcp_general PUBLIC . ../socket)

target_link_libraries(tcp_general PUBLIC tcp_socket)