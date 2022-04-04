cmake_minimum_required(VERSION 3.20)
project(TCP_chat)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY archive)
# add_compile_options(-g)
set(CMAKE_CXX_STANDARD 17)

set(SERVER simple_server.cpp)
set(CLIENT simple_client.cpp)

add_subdirectory(../../src/general general)

add_executable(Server ${SERVER})
add_executable(Client ${CLIENT})

target_include_directories(Server PUBLIC ../../src/general)
target_include_directories(Server PUBLIC ../../src/general)

target_link_libraries(Server tcp_general)
target_link_libraries(Client tcp_general)
