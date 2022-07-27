cmake_minimum_required(VERSION 3.16)
project(diep-server)

set(SERVER_SRCS
    main.cc)

set(SHARED_SRCS
    ../Shared/Coder/Reader.cc
    ../Shared/Coder/Writer.cc
    ../Shared/EntityComponentSystem/Component/Camera.cc
    ../Shared/EntityComponentSystem/Component/Physics.cc
    ../Shared/EntityComponentSystem/Entity.cc
    ../Shared/Simulation.cc)

include_directories(../)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-std=c++20 -g")
add_executable(diep-server ${SERVER_SRCS} ${SHARED_SRCS})
