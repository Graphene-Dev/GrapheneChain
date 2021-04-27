# cmake_minimum_required(VERSION <specify CMake version here>)
project(GrapheneChain)

set(CMAKE_CXX_STANDARD 14)
if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif (UNIX)


add_executable(GrapheneChain
        src/base.cpp)
add_executable(GrapheneChain
        src/sha256.h
        src/sha256.cpp)
add_executable(GrapheneChain
        src/Transaction.cpp
        src/Transaction.h)
