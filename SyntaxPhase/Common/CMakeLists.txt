project(Common)

set(HEADER_FILES
        Symbol.h
        NonTerminal.h
        Terminal.h
)

set(SOURCE_FILES
        Symbol.cpp
        NonTerminal.cpp
        Terminal.cpp
)

add_library(Common_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})
