cmake_minimum_required(VERSION 3.16)
project(G_AscendingSubsequence)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_ASAN "-g -fsanitize=address,undefined -fno-sanitize-recover=all"
        CACHE STRING "Compiler flags in asan build"
        FORCE)

add_executable(G_AscendingSubsequence main.cpp)
