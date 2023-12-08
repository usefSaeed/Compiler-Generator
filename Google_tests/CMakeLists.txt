project(Google_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Google_Tests_run UtilsTest.cpp
        RulesConverterTest.cpp
        RegularDefinitionTest.cpp
        NFATest.cpp
        IntegrationTest.cpp
        DFATest.cpp
        STGeneratorTest.cpp
)

target_link_libraries(Google_Tests_run gtest gtest_main)
target_link_libraries(Google_Tests_run Util_lib)
target_link_libraries(Google_Tests_run RulesParser_lib)
target_link_libraries(Google_Tests_run NFAConverter_lib)
target_link_libraries(Google_Tests_run DFAConverter_lib)
target_link_libraries(Google_Tests_run SymbolTableGenerator_lib)
