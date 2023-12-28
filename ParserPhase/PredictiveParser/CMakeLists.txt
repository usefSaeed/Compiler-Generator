project(PredictiveParser)

set(HEADER_FILES
        Common.h
        Parser.h
        ParsingTree.h
        ParsingTrace.h
        ParsingResult.h
        Token.h
        ParsingTableEntry.h)
        
        
        
set(SOURCE_FILES
        Parser.cpp
        ParsingTree.cpp
        ParsingTrace.cpp
        ParsingResult.cpp
        ParsingTableEntry.cpp)


add_library(PredictiveParser_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(PredictiveParser_lib PUBLIC Util_lib)
