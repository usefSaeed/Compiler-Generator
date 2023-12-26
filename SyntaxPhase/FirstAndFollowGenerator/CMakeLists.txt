project(FirstAndFollowGenerator)

set(HEADER_FILES
        FirstSet.h
        FirstSetsGenerator.h
        FollowSet.h
        FollowSetsGenerator.h
        ParserSet.h)

set(SOURCE_FILES
        FirstSet.cpp
        FirstSetsGenerator.cpp
        FollowSet.cpp
        FollowSetsGenerator.cpp
        ParserSet.cpp)


add_library(FirstAndFollowGenerator_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(FirstAndFollowGenerator_lib PUBLIC Common_lib)
target_link_libraries(FirstAndFollowGenerator_lib PUBLIC GrammarParser_lib)