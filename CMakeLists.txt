cmake_minimum_required(VERSION 3.21)
project(Compiler)

set(CMAKE_CXX_STANDARD 20)

add_executable(Compiler main.cpp)

target_link_libraries(Compiler Util_lib)
target_link_libraries(Compiler RulesParser_lib)

add_subdirectory(Util)
add_subdirectory(RulesParser)
add_subdirectory(Google_tests)
