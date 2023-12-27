project(PredictiveParser)

set(HEADER_FILES
        Common.h
        Parser.h
        ParsingTree.h
        Token.h
        ParsingTableEntry.h)



set(SOURCE_FILES
        Parser.cpp
        ParsingTableEntry.cpp)


add_library(PredictiveParser_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(PredictiveParser_lib PUBLIC Util_lib)
