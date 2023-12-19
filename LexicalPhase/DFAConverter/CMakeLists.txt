project(DFAConverter)

set(HEADER_FILES
        DFA.h)

set(SOURCE_FILES
        DFA.cpp)


add_library(DFAConverter_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(DFAConverter_lib PUBLIC Util_lib)