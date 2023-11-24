cmake_minimum_required(VERSION 3.26)
project(Compiler)

set(CMAKE_CXX_STANDARD 20)

add_executable(Compiler main.cpp
        util.cpp
        util.h)
