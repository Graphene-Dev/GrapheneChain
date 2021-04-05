# cmake_minimum_required(VERSION <specify CMake version here>)
project(GrapheneChain)

set(CMAKE_CXX_STANDARD 14)

add_executable(GrapheneChain
        src/base.cpp)
add_executable(GrapheneChain
        src/sha256.h )
add_executable(GrapheneChain
        src/sha256.cpp)
