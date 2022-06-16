cmake_minimum_required(VERSION 3.16)
project(diep-server)

set(SRCS
    src/main.cc)

set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS "-std=c++20")

file(GLOB_RECURSE SHARED_SRCS ../Shared/*.cc)

include_directories(../Shared/include)

add_executable(diep-server ${SRCS} ${SHARED_SRCS})
