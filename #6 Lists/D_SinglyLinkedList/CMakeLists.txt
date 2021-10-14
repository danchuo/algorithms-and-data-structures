cmake_minimum_required(VERSION 3.16)
project(D_SinglyLinkedList)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_ASAN "-g -fsanitize=address,undefined -fno-sanitize-recover=all"
        CACHE STRING "Compiler flags in asan build"
        FORCE)

add_executable(D_SinglyLinkedList main.cpp)
