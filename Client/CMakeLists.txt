cmake_minimum_required(VERSION 3.16)
project(diep-client)

find_package(OpenGL REQUIRED)

set(SRCS
    src/main.cc
    src/Rendering/Canvas.cc)

set(GLEW_DIR ThirdParty/glew-2.1.0/)
set(GLEW_SRCS
    ${GLEW_DIR}src/glew.c)

file(GLOB_RECURSE SHARED_SRCS ../Shared/src/*.cc)

add_subdirectory(ThirdParty/IXWebSocket)
include_directories(ThirdParty/glfw-3.3.7/include ${GLEW_DIR}include ../Shared/include include ThirdParty/IXWebSocket/ixwebsocket)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(ThirdParty/glfw-3.3.7)

set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS "-std=c++20 -g")
add_executable(diep-client ${SRCS} ${SHARED_SRCS} ${GLEW_SRCS})
target_link_libraries(diep-client glfw OpenGL::GL ixwebsocket)
