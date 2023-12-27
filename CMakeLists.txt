cmake_minimum_required(VERSION 3.21)
project(Compiler)

set(CMAKE_CXX_STANDARD 20)

add_executable(Compiler main.cpp)

target_link_libraries(Compiler Util_lib)
target_link_libraries(Compiler RulesParser_lib)
target_link_libraries(Compiler NFAConverter_lib)
target_link_libraries(Compiler DFAConverter_lib)
target_link_libraries(Compiler SymbolTableGenerator_lib)
target_link_libraries(Compiler GrammarParser_lib)
target_link_libraries(Compiler FirstAndFollowGenerator_lib)
target_link_libraries(Compiler PredictiveParser_lib)


add_subdirectory(Util)
add_subdirectory(LexicalPhase)
add_subdirectory(ParserPhase)
add_subdirectory(Google_tests)

