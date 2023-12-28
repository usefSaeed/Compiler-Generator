project(Google_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Google_Tests_run UtilsTest.cpp
        LP_RulesConverterTest.cpp
        LP_RegularDefinitionTest.cpp
        LP_NFATest.cpp
        LP_IntegrationTest.cpp
        LP_DFATest.cpp
        LP_STGeneratorTest.cpp
        SP_GrammarConverterTest.cpp
        SP_FollowSetGeneratorTest.cpp
        SP_FirstSetGeneratorTest.cpp
        SP_FollowSetGeneratorTest.cpp)

target_link_libraries(Google_Tests_run gtest gtest_main)
target_link_libraries(Google_Tests_run Util_lib)
target_link_libraries(Google_Tests_run RulesParser_lib)
target_link_libraries(Google_Tests_run NFAConverter_lib)
target_link_libraries(Google_Tests_run DFAConverter_lib)
target_link_libraries(Google_Tests_run SymbolTableGenerator_lib)
target_link_libraries(Google_Tests_run GrammarParser_lib)
target_link_libraries(Google_Tests_run FirstAndFollowGenerator_lib)

