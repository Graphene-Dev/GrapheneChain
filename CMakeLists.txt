# cmake_minimum_required(VERSION <specify CMake version here>)
project(GrapheneChain)

set(CMAKE_CXX_STANDARD 14)
if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
    find_package(Boost REQUIRED COMPONENTS)
endif (UNIX)

set(BOOST_INCLUDEDIR "C:/local/boost_1_76_0")
set(BOOST_LIBRARYDIR "C:/local/boost_1_76_0/lib32-msvc-14.1")

add_executable(GrapheneChain
        src/base.cpp)
add_executable(GrapheneChain
        src/sha256.h
        src/sha256.cpp)
add_executable(GrapheneChain
        src/transaction.cpp
        src/transaction.h)
add_executable(GrapheneChain
        src/block.cpp
        src/block.h)
add_executable(GrapheneChain
        src/blockChain.cpp
        src/blockChain.h)
add_executable(GrapheneChain
        src/RSA/src/RSA.cpp
        src/RSA/src/RSA.h
        src/RSA/src/Encryptor.cpp
        src/RSA/src/Encryptor.h
        src/RSA/src/Decryptor.cpp
        src/RSA/src/Decryptor.h)