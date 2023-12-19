project(NFAConverter)

set(HEADER_FILES
        Transition.h
        State.h
        NFA.h
        NFACombiner.h
)

set(SOURCE_FILES
        Transition.cpp
        State.cpp
        NFA.cpp
        NFACombiner.cpp
)


add_library(NFAConverter_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(NFAConverter_lib PUBLIC Util_lib)