cmake_minimum_required(VERSION 3.20)
project(TCP_chat)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY archive)
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SERVER src/server_side/*.cpp)
file(GLOB_RECURSE CLIENT src/client_side/*.cpp)

add_subdirectory(src/general)

add_executable(Server ${SERVER})
add_executable(Client ${CLIENT})

target_include_directories(Server PUBLIC src/general src/server_side)
target_include_directories(Server PUBLIC src/general src/client_side)

target_link_libraries(Server tcp_general)
target_link_libraries(Client tcp_general)
