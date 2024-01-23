cmake_minimum_required(VERSION 3.21)
project(Compiler)

set(CMAKE_CXX_STANDARD 20)

add_executable(Compiler Driver.cpp
        )

target_link_libraries(Compiler Util_lib)
target_link_libraries(Compiler RulesParser_lib)
target_link_libraries(Compiler NFAConverter_lib)
target_link_libraries(Compiler DFAConverter_lib)
target_link_libraries(Compiler SymbolTableGenerator_lib)
target_link_libraries(Compiler GrammarParser_lib)


add_subdirectory(Util)
add_subdirectory(LexicalPhase)
add_subdirectory(SyntaxPhase)
add_subdirectory(Google_tests)

