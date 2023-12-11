project(SymbolTableGenerator)

set(HEADER_FILES
        STGenerator.h
        STRow.h
        SyntaxError.h
        LATrace.h
        LAOutput.h)

set(SOURCE_FILES
        STGenerator.cpp
        STRow.cpp
        SyntaxError.cpp
        LAOutput.cpp
        LATrace.cpp )


add_library(SymbolTableGenerator_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(SymbolTableGenerator_lib PUBLIC Util_lib)