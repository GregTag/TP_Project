cmake_minimum_required(VERSION 3.20)
project(TCP_chat)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY archive)
add_compile_options(-g)
set(CMAKE_CXX_STANDARD 17)

set(DB ../../src/server_side/database)
set(COMMON common.cpp ${DB}/accounts_database.cpp ${DB}/simple_database.cpp)

add_subdirectory(../../src/general general)

add_executable(Common ${COMMON})

target_include_directories(Common PUBLIC ${DB})
target_include_directories(Common PUBLIC ../../src/general)
target_link_libraries(Common tcp_general)