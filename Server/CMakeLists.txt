cmake_minimum_required(VERSION 3.16)
project(diep-server)

find_package(Threads REQUIRED)

set(SERVER_SRCS
    Client.cc
    GameServer.cc
    main.cc
    ../ThirdParty/Polynet/polynet.cpp)

set(SHARED_SRCS
    ../Shared/Coder/Reader.cc
    ../Shared/Coder/Writer.cc
    ../Shared/EntityComponentSystem/Component/Arena.cc
    ../Shared/EntityComponentSystem/Component/Camera.cc
    ../Shared/EntityComponentSystem/Component/Physics.cc
    ../Shared/EntityComponentSystem/Entity.cc
    ../Shared/Simulation.cc
    ../Shared/Util.cc)

include_directories(../ ../ThirdParty/Polynet)
include_directories(../ ../ThirdParty/std/include)

set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS "-std=c++17 -g")
add_executable(diep-server ${SERVER_SRCS} ${SHARED_SRCS})
target_link_libraries(diep-server PRIVATE Threads::Threads)
