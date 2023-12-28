project(Common)

set(HEADER_FILES
        Symbol.h
        Terminal.h
        NonTerminal.h
        )

set(SOURCE_FILES
        Symbol.cpp
        Terminal.cpp
        NonTerminal.cpp
        )

add_library(Common_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(Common_lib PUBLIC FirstAndFollowGenerator_lib)