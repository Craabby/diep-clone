cmake_minimum_required(VERSION 3.16)
project(diep-server)

set(SERVER_SRCS
    src/main.cc
    src/ServerSimulation.cc)

file(GLOB_RECURSE SHARED_SRCS ../Shared/src/*.cc)

add_subdirectory(ThirdParty/IXWebSocket)
include_directories(../Shared/include include ThirdParty/IXWebSocket/ixwebsocket)

set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS "-std=c++20 -g")
add_executable(diep-server ${SERVER_SRCS} ${SHARED_SRCS})
target_link_libraries(diep-server ixwebsocket)
