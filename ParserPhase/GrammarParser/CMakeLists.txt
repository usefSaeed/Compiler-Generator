project(GrammarParser)

set(HEADER_FILES
        GrammarConverter.h)

set(SOURCE_FILES
        GrammarConverter.cpp)


add_library(GrammarParser_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(GrammarParser_lib PUBLIC Util_lib)