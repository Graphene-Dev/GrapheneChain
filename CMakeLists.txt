# cmake_minimum_required(VERSION <specify CMake version here>)
project(GrapheneChain)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")


add_executable(GrapheneChain
        src/base.cpp)
add_executable(GrapheneChain
        src/sha256.h )
add_executable(GrapheneChain
        src/sha256.cpp)
