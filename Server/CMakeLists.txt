cmake_minimum_required(VERSION 3.16)
project(diep-server)

set(SERVER_SRCS
    main.cc)

file(GLOB_RECURSE SHARED_SRCS ../Shared/*.cc)

include_directories(../)

set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS "-std=c++20 -g")
add_executable(diep-server ${SERVER_SRCS} ${SHARED_SRCS})
