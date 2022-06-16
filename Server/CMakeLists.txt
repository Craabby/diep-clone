cmake_minimum_required(VERSION 3.16)
project(diep-server)

set(SRCS
    src/main.cc)

file(GLOB_RECURSE SHARED_SRCS ../Shared/*.cc)

include_directories(../Shared/include)

add_executable(diep-server ${SRCS} ${SHARED_SRCS})
